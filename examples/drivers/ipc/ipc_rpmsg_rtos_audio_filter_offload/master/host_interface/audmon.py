"""
Copyright (C) 2025 Texas Instruments Incorporated

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the
    distribution.

    Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""
# audmon.py – Animated Audio monitoring and Debug Console

import threading
import tkinter as tk
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import re
import os
import sys
import math
from tkinter.scrolledtext import ScrolledText
from tkinter import ttk
import datetime
import socket
from collections import deque
import numpy as np
import matplotlib.ticker as ticker
from threading import Lock
from scipy.signal import get_window
import serial

# Parse mode and address/port
if len(sys.argv) < 3:
    print("Usage: python GUI-V2.py <mode: uart|ip> <COM port|IP address>")
    sys.exit(1)

MODE = sys.argv[1].lower()
ADDR = sys.argv[2]
# --- CONFIGURATION ---
SAMPLE_RATE = 48000
FFT_SIZE = 1024
SERVER_IP = ADDR
SERIAL_PORT = ADDR
SERVER_PORT = 8888
CMD_PORT = 8889
IN_DATA_PORT = 8890
OUT_DATA_PORT = 8891
BAUD_RATE = 115200
TIMEOUT = 1
MAX_FRAMES = 2048
RETRY_INTERVAL = 3  # seconds
MAX_SAMPLES = 2048

# --- GLOBAL STATE ---
sock = None
sock_cmd = None
sock_input_data = None
sock_output_data = None
connected = False
connected_input_data = False
frame_numbers = deque(maxlen=MAX_FRAMES)
avg_amps = deque(maxlen=MAX_FRAMES)
latencies = deque(maxlen=MAX_FRAMES)
modes = []
summaries = []
cpu_loads = deque(maxlen=MAX_FRAMES)
dsp_loads = deque(maxlen=MAX_FRAMES)
waveform_lock = Lock()
waveform_insamples=deque(maxlen=MAX_SAMPLES)
waveform_outsamples=deque(maxlen=MAX_SAMPLES)
current_mode = "BOTH"
ser = None
is_running = False
log_console = None
node_label = None


def compute_spectrum(samples):
    """Compute FFT magnitude spectrum of a sample buffer."""
    if len(samples) < FFT_SIZE:
        return [], []

    # Convert to numpy and clip to int16 range just in case
    sample_array = np.clip(np.array(list(samples)[-FFT_SIZE:], dtype=np.float32), -32768, 32767)
    sample_array = np.clip(sample_array, -32768, 32767)
    # Apply window
    #window = np.hanning(FFT_SIZE);
    window = np.hamming(FFT_SIZE);
    windowed = window * sample_array

    # FFT
    spectrum = np.fft.rfft(windowed)
    freqs = np.fft.rfftfreq(FFT_SIZE, d=1.0 / SAMPLE_RATE)

    # Full-scale reference
    ref = 32768.0 # max absolute value for int16
    ref = 10000.0 # max absolute value for int16

    #magnitude = 20 * np.log10(np.abs(spectrum) / ref + 1e-12)
    magnitude = 20 * np.log10(np.abs(spectrum) / ref)

    return freqs, magnitude, spectrum

if MODE not in ["uart", "ip"]:
    print("Mode must be 'uart' or 'ip'")
    sys.exit(1)

# Global variables to hold live summary values
live_summary = {
    "frames": 0,
    "latency_min": 0.0,
    "latency_max": 0.0,
    "latency_avg": 0.0,
    "amp_min": 0.0,
    "amp_max": 0.0,
    "amp_avg": 0.0,
    "cpu_min": 0.0,
    "cpu_max": 0.0,
    "cpu_avg": 0.0,
    "dsp_min": 0.0,
    "dsp_max": 0.0,
    "dsp_avg": 0.0,
}

log_pattern = re.compile(
    r"Frame\s+(\d+):\s+AvgAmp=([\d.]+),\s+Latency=([\d.]+)ms,\s+Mode=([A-Z]+)\s+CPULoad=([\d.]+)%\s+DSPLoad=([\d.]+)%"
)

def wait_for_connection():
    """Establish main data socket connection."""
    global connected, sock
    connected = False;
    while not connected:
        log_debug("Waiting for device data connection...")
        try:
            if sock:
                sock.close()
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((SERVER_IP, SERVER_PORT))
            connected = True
            clear_data()
            log_debug("Connected to device (data)")
        except Exception as e:
            log_debug(f"Retrying in {RETRY_INTERVAL}s... ({e})")
            time.sleep(RETRY_INTERVAL)

def wait_for_cmd():
    """Establish command socket connection."""
    global sock_cmd, connected_cmd
    connected_cmd = False
    while not connected_cmd:
        try:
            if sock_cmd:
                sock_cmd.close()
            sock_cmd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock_cmd.connect((SERVER_IP, CMD_PORT))
            connected_cmd = True
            log_debug("Connected to device (command)")
        except Exception as e:
            log_debug(f"Waiting for CMD port... retrying in {RETRY_INTERVAL}s ({e})")
            time.sleep(RETRY_INTERVAL)

def wait_for_indata():
    """Connect to device's input audio data stream."""
    global sock_input_data, connected_input_data
    connected_input_data = False
    while not connected_input_data:
        try:
            if sock_input_data:
                sock_input_data.close()
            sock_input_data = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock_input_data.connect((SERVER_IP, IN_DATA_PORT))
            connected_input_data = True
            threading.Thread(target=read_input_audio_samples, daemon=True).start()
            log_debug("Connected to device (input data)")
        except Exception as e:
            log_debug(f"Waiting for IN DATA port... retrying in {RETRY_INTERVAL}s ({e})")
            time.sleep(RETRY_INTERVAL)

def wait_for_outdata():
    """Connect to device's output audio data stream."""
    global sock_output_data, connected_output_data
    connected_output_data = False
    while not connected_output_data:
        try:
            if sock_output_data:
                sock_output_data.close()
            sock_output_data = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock_output_data.connect((SERVER_IP, OUT_DATA_PORT))
            connected_output_data = True
            threading.Thread(target=read_output_audio_samples, daemon=True).start()
            log_debug("Connected to device (out data)")
        except Exception as e:
            log_debug(f"Waiting for OUT DATA port... retrying in {RETRY_INTERVAL}s ({e})")
            time.sleep(RETRY_INTERVAL)

def amplitude_to_dbfs(amp, peak=32767.0):
    """Convert linear amplitude to decibels full scale (dBFS)."""
    if amp <= 0:
        return -100.0
    return 20 * math.log10(amp / peak)

def log_debug(msg):
    """Log message to console and UI."""
    print("DEBUG:", msg)
    if log_console:
        log_console.insert(tk.END, msg + "\n")
        log_console.see(tk.END)

def save_data_and_logs(event=None):
    """
    Save the current graphs (input/output spectra, amplitude, latency, load)
    and the live summary values + raw logs to timestamped folder.
    """

    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    save_dir = f"logs_{timestamp}"
    os.makedirs(save_dir, exist_ok=True)

    # Force redraw of canvas to ensure latest data is rendered
    canvas.draw()

    # Generate timestamp
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")

    # 1) Save full figure (all subplots)
    fig_path = os.path.join(save_dir, f"audmon_graphs_{timestamp}.png")
    fig.savefig(fig_path)
    log_debug(f"Graphs saved to {fig_path}")

    # 2) Save summary to text
    summary_file = os.path.join(save_dir, f"audmon_summary_{timestamp}.txt")
    with open(summary_file, "w") as f:
        f.write(f"Summary Data - {timestamp}")
        f.write("="*40 + "")
        f.write(f"Frames processed: {live_summary['frames']}")
        f.write(f"Latency (ms): Min={live_summary['latency_min']:.2f}, Max={live_summary['latency_max']:.2f}, Avg={live_summary['latency_avg']:.2f}")
        f.write(f"Amplitude (dBFS): Min={live_summary['amp_min']:.2f}, Max={live_summary['amp_max']:.2f}, Avg={live_summary['amp_avg']:.2f}")
        f.write(f"CPU Load (%): Min={live_summary['cpu_min']:.1f}, Max={live_summary['cpu_max']:.1f}, Avg={live_summary['cpu_avg']:.1f}")
        f.write(f"DSP Load (%): Min={live_summary['dsp_min']:.1f}, Max={live_summary['dsp_max']:.1f}, Avg={live_summary['dsp_avg']:.1f}")
        f.write("Log Console Output:")
    log_debug(f"Summary saved to {summary_file}")

    # 3) Save raw sample buffers
    input_csv = os.path.join(save_dir, f"input_samples_{timestamp}.csv")
    output_csv = os.path.join(save_dir, f"output_samples_{timestamp}.csv")
    np.savetxt(input_csv, list(waveform_insamples)[-FFT_SIZE:], delimiter=',', header='InputSamples', comments='')
    np.savetxt(output_csv, list(waveform_outsamples)[-FFT_SIZE:], delimiter=',', header='OutputSamples', comments='')
    log_debug(f"Raw buffers saved to {input_csv} and {output_csv}")

def clear_data():
    """Reset UI Screen."""
    frame_numbers.clear()
    avg_amps.clear()
    latencies.clear()
    modes.clear()
    summaries.clear()
    cpu_loads.clear()
    dsp_loads.clear()
    # Reset live summary values
    live_summary["frames"] = 0
    live_summary["latency_min"] = 0.0
    live_summary["latency_max"] = 0.0
    live_summary["latency_avg"] = 0.0
    live_summary["amp_min"] = 0.0
    live_summary["amp_max"] = 0.0
    live_summary["amp_avg"] = 0.0
    live_summary["cpu_min"] = 0.0
    live_summary["cpu_max"] = 0.0
    live_summary["cpu_avg"] = 0.0
    live_summary["dsp_min"] = 0.0
    live_summary["dsp_max"] = 0.0
    live_summary["dsp_avg"] = 0.0

    # Update static live summary labels to reflect the reset values
    frames_label.config(text="Frames: 0")
    latency_label.config(text="Latency (ms): Min: 0.00, Max: 0.00, Avg: 0.00")
    amp_label.config(text="Amplitude: Min: 0.00, Max: 0.00, Avg: 0.00")
    cpu_label.config(text="CPU Load (%): Min: 0.0, Max: 0.0, Avg: 0.0")
    dsp_label.config(text="DSP Load (%): Min: 0.0, Max: 0.0, Avg: 0.0")

    summary_label.config(text="Summary Info")
    if log_console:
        log_console.delete("1.0", tk.END)

    global waveform_insamples, waveform_outsamples, fft_index, modeDisplay
    with waveform_lock:
        waveform_insamples.clear()
        waveform_outsamples.clear()
    fft_index = 0
    toggle_filter.state = True;
    filter_btn.config(text=f"Filter On", bg='green')
    modeDisplay = "false"
    log_debug("[Cleared] Graph and logs reset")

def send_command(cmd):
    global sock_cmd

    if MODE == "ip":
        sock_cmd.sendall((cmd + '\n').encode())
    if MODE == "uart":
        if ser and ser.is_open:
            ser.write((cmd + '\n').encode())

def send_param_command(gtype, val):
    global connected

    if connected:
        send_command(f"SET {gtype.upper()} {val}\n")
        canvas.draw_idle()

def set_mode(mode):
    global current_mode

    if mode != current_mode:
        if current_mode == "ARM":
            val = 0
        else:
            val = 1
        current_mode = mode.upper()
        send_command(f"SET MODE  {val}")
        highlight_buttons()

def toggle_test():
    global is_running
    if is_running:
        send_command("STOP")
        is_running = False
    else:
        clear_data()
        send_command("START")
        is_running = True

def highlight_buttons():
    if current_mode == "ARM":
        arm_button.config(bg="blue")
    elif current_mode == "DSP":
        dsp_button.config(bg="green")

def update_live_summary(line):
    """Refresh UI """
    global live_summary
    try:
        if line.startswith("[Live Summary] Frames:"):
            # Example: "[Live Summary] Frames: 120"
            parts = line.split(":")
            live_summary["frames"] = int(parts[1].strip())
        elif line.startswith("[Live Summary] Latency"):
            m = re.search(r"Min:\s*([\d.]+),\s*Max:\s*([\d.]+),\s*Avg:\s*([\d.]+)", line)
            if m:
                live_summary["latency_min"] = float(m.group(1))
                live_summary["latency_max"] = float(m.group(2))
                live_summary["latency_avg"] = float(m.group(3))
        elif line.startswith("[Live Summary] Amp"):
            m = re.search(r"Min:\s*([\d.]+),\s*Max:\s*([\d.]+),\s*Avg:\s*([\d.]+)", line)
            if m:
                # Convert raw amplitude to dBFS using the conversion function
                raw_min = float(m.group(1))
                raw_max = float(m.group(2))
                raw_avg = float(m.group(3))
                live_summary["amp_min"] = amplitude_to_dbfs(raw_min)
                live_summary["amp_max"] = amplitude_to_dbfs(raw_max)
                live_summary["amp_avg"] = amplitude_to_dbfs(raw_avg)
        elif line.startswith("[Live Summary] CPU"):
            m = re.search(r"Min:\s*([\d.]+),\s*Max:\s*([\d.]+),\s*Avg:\s*([\d.]+)", line)
            if m:
                live_summary["cpu_min"] = float(m.group(1))
                live_summary["cpu_max"] = float(m.group(2))
                live_summary["cpu_avg"] = float(m.group(3))
        elif line.startswith("[Live Summary] DSP"):
            m = re.search(r"Min:\s*([\d.]+),\s*Max:\s*([\d.]+),\s*Avg:\s*([\d.]+)", line)
            if m:
                live_summary["dsp_min"] = float(m.group(1))
                live_summary["dsp_max"] = float(m.group(2))
                live_summary["dsp_avg"] = float(m.group(3))
    except Exception as e:
        log_debug("Live summary parse error: " + str(e))

def inrecv_exact(size):
    global sock_input_data
    buf = b''
    while len(buf) < size:
        chunk = sock_input_data.recv(size - len(buf))
        if not chunk:
            return None
        buf += chunk
    return buf

def outrecv_exact(size):
    global sock_output_data
    buf = b''
    while len(buf) < size:
        chunk = sock_output_data.recv(size - len(buf))
        if not chunk:
            return None
        buf += chunk
    return buf

def read_input_audio_samples():
    """Read input audio samples from socket and add to global buffer."""
    while True:
        if connected_input_data:
            header = inrecv_exact(4)
            if not header:
                break
            if header != b'INPT':
                print(f"[INPUT WARN] Unknown tag: {header}")
                continue
            data = inrecv_exact(512)
            if not data:
                break
            samples = np.frombuffer(data, dtype=np.int16)
            ch0_samples = samples.tolist()

            # Add to waveform_insamples
            with waveform_lock:
                waveform_insamples.extend(ch0_samples)

def read_output_audio_samples():
    """Read output audio samples from socket and add to global buffer."""
    while True:
        if connected_output_data:
            header = outrecv_exact(4)
            if not header:
                break
            if header != b'OUTP':
                print(f"[OUTPUT WARN] Unknown tag: {header}")
                continue
            data = outrecv_exact(512)
            if not data:
                break
            samples = np.frombuffer(data, dtype=np.int16)
            ch0_samples = samples.tolist()

            # Add to waveform_insamples
            with waveform_lock:
                waveform_outsamples.extend(ch0_samples)

def read_data():
    """Read logs from socket and add to global buffers."""
    global sock
    global waveform_insamples, waveform_outsamples, connected, connected_input_data

    recv_buffer = ""

    while True:
        if MODE == "ip":
            if not connected:
                wait_for_connection()
                wait_for_cmd()
                wait_for_indata()
                wait_for_outdata()
                log_debug("Connected via IP")
        try:
            if MODE == "ip":
                data = sock.recv(1024).decode()
                if not data:
                    raise ConnectionError("Connection lost")
            elif MODE == "uart":
                if ser is not None:
                    data = ser.read(1024).decode()
                    connected = True
                else:
                    continue

            recv_buffer += data
            test = len(recv_buffer)
            while "\n" in recv_buffer:
                line, recv_buffer = recv_buffer.split("\n", 1)
                line = line.strip().replace('\r', '')
                if not line:
                    continue

                # Live Summary handling
                if "[Live Summary]" in line:
                    update_live_summary(line)

                # General summary or frame log lines
                if ("[Summary]" in line or "Frames Processed" in line or "Latency:" in line or line.startswith("Frame")):
                    parse_log_line(line)

        except Exception as e:
            if connected:
                log_debug(f"Connection lost: {e}")
            connected = False
            connected_input_data = False
            time.sleep(RETRY_INTERVAL)

modeDisplay = "false"

def parse_log_line(line):
    try:
        match = log_pattern.search(line)
        if not match:
            log_debug("U PARSE Error")
            return
        frame = int(match.group(1))
        avg_amp = float(match.group(2))
        latency = float(match.group(3))
        mode = match.group(4)
        cpu = float(match.group(5))
        dsp = float(match.group(6))

        mapped_mode = "CPU" if current_mode == "ARM" else "DSP" if current_mode == "DSP" else "BOTH"
        if mapped_mode != "BOTH" and mode != mapped_mode:
            log_debug("U PARSE Error1 ")
            return

        avg_db = amplitude_to_dbfs(avg_amp)

        frame_numbers.append(frame)
        avg_amps.append(avg_db)
        latencies.append(latency)
        modes.append(mode)
        cpu_loads.append(cpu)
        dsp_loads.append(dsp)

    except Exception as e:
        log_debug("Parse error: " + str(e))

def animate(i):
    ax1.clear()
    ax2.clear()
    ax3.clear()
    if (MODE == "ip"):
        ax4.clear()
        ax5.clear()
    if not frame_numbers:
        return

    ax1.plot(frame_numbers, avg_amps, label="Avg Amplitude")
    ax1.set_ylabel("Amplitude")
    ax1.set_title("Average Amplitude")
    ax1.legend()


    min_len = min(len(frame_numbers), len(latencies), len(modes))
    global modeDisplay

    cpu_x, cpu_y = [], []
    dsp_x, dsp_y = [], []

    for j in range(min_len):
        if modes[j] == "CPU":
            cpu_x.append(frame_numbers[j])
            cpu_y.append(latencies[j])
            current_mode = "ARM"
        elif modes[j] == "DSP":
            dsp_x.append(frame_numbers[j])
            dsp_y.append(latencies[j])
            current_mode = "DSP"

    try:
        if current_mode == "ARM":
            ax2.plot(cpu_x, cpu_y, label="CPU Latency", color='blue')
            if modeDisplay == "false":
                mode_label.config(text="Running on A53 (Linux)")
                modeDisplay = "true"
        if current_mode == "DSP":
            ax2.plot(dsp_x, dsp_y, label="DSP Latency", color='green')
            if modeDisplay == "false":
                mode_label.config(text="Running on C7x")
                modeDisplay = "true"
    except Exception as e:
        print(f"Animate error {e}")

    ax2.set_xlabel("Frame")
    ax2.set_ylabel("Latency (ms)")
    ax2.set_title("Frame Latency")
    ax2.legend()

    ax3.plot(frame_numbers, cpu_loads, label="CPU Load (%)", color='blue')
    ax3.plot(frame_numbers, dsp_loads, label="DSP Load (%)", color='red')
    ax3.set_xlabel("Frame")
    ax3.set_ylabel("Load (%)")
    ax3.set_title("System Load")
    ax3.legend()

    # Update the static summary labels:
    frames_label.config(text=f"Frames: {live_summary['frames']}")
    latency_label.config(text=f"Latency (ms): Min: {live_summary['latency_min']:.2f}, Max: {live_summary['latency_max']:.2f}, Avg: {live_summary['latency_avg']:.2f}")
    amp_label.config(text=f"Amplitude: Min: {live_summary['amp_min']:.2f}, Max: {live_summary['amp_max']:.2f}, Avg: {live_summary['amp_avg']:.2f}")
    cpu_label.config(text=f"CPU Load (%): Min: {live_summary['cpu_min']:.1f}, Max: {live_summary['cpu_max']:.1f}, Avg: {live_summary['cpu_avg']:.1f}")
    dsp_label.config(text=f"DSP Load (%): Min: {live_summary['dsp_min']:.1f}, Max: {live_summary['dsp_max']:.1f}, Avg: {live_summary['dsp_avg']:.1f}")

    # Define custom frequency band markers (Hz)
    audio_band_ticks = [ 1000, 2000, 4000, 8000, 12000, 16000]
    audio_band_labels = [f"{int(f/1000)}k" if f >= 1000 else str(f) for f in audio_band_ticks]

    # Input Spectrum
    if ((len(waveform_insamples) >= FFT_SIZE) and (MODE == "ip")):

        freqs, mag, spectrum = compute_spectrum(waveform_insamples)
        ax4.plot(freqs, mag, color='green')
        ax4.set_title("Input Audio Spectrum")
        ax4.set_ylabel("Amplitude (dBFS)")
        ax4.set_xlabel("Frequency (Hz)")
        ax4.set_ylim(-100, 15)
        ax4.set_xlim(0, 16000)
        for lvl in (-25, -50, -75):
            ax4.axhline(lvl, linestyle='--', linewidth=0.8, label=f"{lvl} dB")
        # Add kHz ticks
        ax4.set_xticks(audio_band_ticks)
        ax4.set_xticklabels(audio_band_labels)
        ax4.grid(True, axis='x', linestyle='--', alpha=0.5)

    # Output Spectrum
    if ((len(waveform_outsamples) >= FFT_SIZE) and (MODE == "ip")):
        freqs, mag, spectrum = compute_spectrum(waveform_outsamples)
        ax5.plot(freqs, mag, color='blue')
        ax5.set_title("Output Audio Spectrum")
        ax5.set_ylabel("Amplitude (dBFS)")
        ax5.set_xlabel("Frequency (Hz)")
        ax5.set_ylim(-100, 15)
        ax5.set_xlim(0, 16000)
        for lvl in (-25, -50, -75):
            ax5.axhline(lvl, linestyle='--', linewidth=0.8, label=f"{lvl} dB")
        # Add kHz ticks
        ax5.set_xticks(audio_band_ticks)
        ax5.set_xticklabels(audio_band_labels)
        ax5.grid(True, axis='x', linestyle='--', alpha=0.5)

if MODE == "uart":
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=TIMEOUT)

def toggle_filter():
    """Toggle audio filter state and send command to device."""
    toggle_filter.state = not toggle_filter.state
    value = 1 if toggle_filter.state else 0
    filter_btn.config(text=f"Filter {'On' if value else 'Off'}",
            bg='green' if value else 'lightgray')
    send_param_command("FFT FILTER", value)

toggle_filter.state = True  # Initial state: ON

# GUI Setup
root = tk.Tk()
root.title("Audio DSP OFFLOAD GUI")
root.attributes("-fullscreen", True)
left_frame = tk.Frame(root,width=370, bg="#f0f0f0")
left_frame.pack(side=tk.LEFT, fill=tk.Y)
left_frame.pack_propagate(False)

tk.Label(left_frame, text="Channel 1 Data Display", font=("Helvetica", 14, "bold"), bg = "#f0f0f0", fg = "black").pack(pady=20)

tk.Label(left_frame, text="Filter Control", font=("Helvetica", 14, "bold"), bg="#f0f0f0", fg="black").pack(pady=20)
filter_btn = tk.Button(left_frame, text="Filter ON", width=15, height=2, font=("Helvetica", 12, "bold"),
                       command=toggle_filter, bg="green")
filter_btn.pack(pady=5)

mode_label = tk.Label(left_frame, text="Mode: --", font=("Helvetica", 14, "bold"), bg="#f0f0f0", fg="black")
mode_label.pack(pady=40)

middle_frame = tk.Frame(left_frame, bg="#f0f0f0")
middle_frame.place(relx=0.5, rely=0.5, anchor="center")

lable_font = ("Helvetica", 12, "bold")

summary_label = tk.Label(middle_frame, text="Live Summary", font=("Helvetica", 14, "bold"), bg = "#f0f0f0", fg = "black")
summary_label.pack(pady=20)

if (MODE == "ip"):
    fig, (ax4, ax5, ax1, ax2, ax3) = plt.subplots(5, 1, figsize=(10, 11), constrained_layout=True)
else:
    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 11), constrained_layout=True)

# Create a frame for the live summary
live_summary_frame = tk.Frame(left_frame, bd=2, relief=tk.GROOVE)
live_summary_frame.pack(pady=10, fill=tk.X)

# Create static labels for each summary field
frames_label = tk.Label(middle_frame, text="Frames: 0", anchor="w", width=40, fg="blue", font=lable_font, bg="#f0f0f0")
frames_label.pack(pady=5)

latency_label = tk.Label(middle_frame, text="Latency (ms): Min: 0.00, Max: 0.00, Avg: 0.00", anchor="w", width=40, fg="darkgreen", font=lable_font, bg="#f0f0f0")
latency_label.pack(pady=5)

amp_label = tk.Label(middle_frame, text="Amplitude: Min: 0.00, Max: 0.00, Avg: 0.00", anchor="w", width=40, fg="purple", font=lable_font, bg="#f0f0f0")
amp_label.pack(pady=5)

cpu_label = tk.Label(middle_frame, text="CPU Load (%): Min: 0.0, Max: 0.0, Avg: 0.0", anchor="w", width=40, fg="maroon", font=lable_font, bg="#f0f0f0")
cpu_label.pack(pady=5)

dsp_label = tk.Label(middle_frame, text="DSP Load (%): Min: 0.0, Max: 0.0, Avg: 0.0", anchor="w", width=40, fg="darkorange", font=lable_font, bg="#f0f0f0")
dsp_label.pack(pady=5)

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)
ani = animation.FuncAnimation(fig, animate, interval=500)
threading.Thread(target=read_data, daemon=True).start()
root.bind('<Control-s>', save_data_and_logs)
root.mainloop()
