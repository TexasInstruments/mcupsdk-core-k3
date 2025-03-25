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

"""
AASRC Visualization Tool
=========================
Script for Reading and Visualizing UART Data with Zero-Crossing Analysis

This tool reads input and output samples of AASRC transaction from a UART interface, processes the data
to identify zero crossings, calculates cycle lengths, and visualizes the results using matplotlib.
It is tailored to work with a specific data format transmitted over UART, including metadata such as
sampling frequency and data format.

Features:
---------
- Convert hexadecimal data to signed integers using two's complement representation.
- Identify zero crossings in the data to analyze signal cycles.
- Calculate cycle lengths based on zero-crossing indices.
- Visualize input and output samples with annotated cycles and sampling frequency information.

Usage:
------
Run this script directly to read data from a UART interface, process it, and visualize the results.
Ensure the UART port and baud rate are correctly configured in the `main` function.
"""

import serial
import matplotlib.pyplot as plt
import numpy as np
import time

def hex_to_signed(hex_str, bits):
    # Convert hex string to integer
    value = int(hex_str, 16)
    # Strip down to the specified number of bits
    value = value & ((1 << bits) - 1)
    # Convert to signed integer (two's complement)
    if value & (1 << (bits - 1)):
        value -= (1 << bits)
    return value

def read_samples_from_uart(ser, end_marker, buffer_type, bits):
    samples = []
    count = 0
    while True:
        line = ser.readline().strip()
        if line == end_marker:
            break
        converted_value = hex_to_signed(line.decode('utf-8', errors='ignore'), bits)
        count += 1
        samples.append(converted_value)
    return samples

def find_zero_crossings(samples):
    zero_crossings = []
    for i in range(1, len(samples)):
        if (samples[i-1] < 0 and samples[i] >= 0) or (samples[i-1] >= 0 and samples[i] < 0):
            zero_crossings.append(i)
    return zero_crossings

def calculate_cycle_lengths(zero_crossings):
    cycle_lengths = []
    for i in range(1, len(zero_crossings)):
        cycle_lengths.append(zero_crossings[i] - zero_crossings[i-1])
    return cycle_lengths

def plot_samples(input_samples, output_samples, input_zero_crossings, output_zero_crossings, buffer_index, headline, sampling_frequency, unit):
    input_cycle_lengths = calculate_cycle_lengths(input_zero_crossings)
    output_cycle_lengths = calculate_cycle_lengths(output_zero_crossings)

    if input_cycle_lengths:
        max_input_cycle_length = max(input_cycle_lengths)
    else:
        max_input_cycle_length = None

    if output_cycle_lengths:
        max_output_cycle_length = max(output_cycle_lengths)
    else:
        max_output_cycle_length = None

    # Calculate sampling frequency
    if max_input_cycle_length is not None:
        input_sampling_frequency = sampling_frequency * max_input_cycle_length * 2
    else:
        input_sampling_frequency = None

    if max_output_cycle_length is not None:
        output_sampling_frequency = sampling_frequency * max_output_cycle_length * 2
    else:
        output_sampling_frequency = None

    # Plot the samples
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 6))
    fig.suptitle(f'{headline}')

    ax1.plot(input_samples, 'bo', label='Input Samples', markersize=3)  # Blue dots for input samples with reduced size
    ax1.set_title('Input Samples')
    ax1.set_xlabel('Sample Index')
    ax1.set_ylabel('Amplitude')
    ax1.legend()
    ax1.set_facecolor('white')  # Set background color to white

    # Annotate the full cycle of the input data set
    if len(input_zero_crossings) > 2:  # Ensure there are at least 3 zero crossings for a full cycle
        middle_index = len(input_samples) // 2
        # Find the full cycle that contains the middle index
        for i in range(2, len(input_zero_crossings)):
            start = input_zero_crossings[i - 2]
            middle = input_zero_crossings[i - 1]
            end = input_zero_crossings[i]
            if start <= middle_index <= end:
                cycle_length = end - start + 1
                # Add red dotted lines for the zero crossings of the full cycle
                ax1.axvline(x=start, color='r', linestyle='--')  # Red dashed line at the start of the cycle
                ax1.axvline(x=end, color='r', linestyle='--')    # Red dashed line at the end of the cycle
                break

    if input_sampling_frequency is not None:
        ax1.legend([f'Input Samples\nSampling Frequency: {input_sampling_frequency:.2f} {unit}'])

    ax2.plot(output_samples, 'o', color='orange', label='Output Samples', markersize=3)  # Orange dots for output samples with reduced size
    ax2.set_title('Output Samples')
    ax2.set_xlabel('Sample Index')
    ax2.set_ylabel('Amplitude')
    ax2.legend()
    ax2.set_facecolor('white')  # Set background color to white


    # Annotate the full cycle of the output data set
    if len(output_zero_crossings) > 2:  # Ensure there are at least 3 zero crossings for a full cycle
        middle_index = len(output_samples) // 2
        # Find the full cycle that contains the middle index
        for i in range(2, len(output_zero_crossings)):
            start = output_zero_crossings[i - 2]
            middle = output_zero_crossings[i - 1]
            end = output_zero_crossings[i]
            if start <= middle_index <= end:
                cycle_length = end - start + 1
                # Add red dotted lines for the zero crossings of the full cycle
                ax2.axvline(x=start, color='r', linestyle='--')  # Red dashed line at the start of the cycle
                ax2.axvline(x=end, color='r', linestyle='--')    # Red dashed line at the end of the cycle
                break

    if output_sampling_frequency is not None:
        ax2.legend([f'Output Samples\nSampling Frequency: {output_sampling_frequency:.2f} {unit}'])

    plt.tight_layout()
    plt.show()

def main():
    port = '/dev/ttyUSB4'  # Replace with your UART port
    baudrate = 115200

    ser = serial.Serial(port, baudrate)

    buffer_index = 0
    data_sets = []

    while True:
        line = ser.readline().strip().decode('utf-8', errors='ignore')
        print(f"{line}")  # Debug log
        if line == 'Data Start':
            # Read metadata
            headline = ser.readline().strip().decode('utf-8', errors='ignore')
            sampling_frequency_line = ser.readline().strip().decode('utf-8', errors='ignore')
            data_format_line = ser.readline().strip().decode('utf-8', errors='ignore')

            sampling_frequency_str = sampling_frequency_line.split(':')[1].strip()
            sampling_frequency, unit = sampling_frequency_str.split()
            sampling_frequency = float(sampling_frequency)
            data_format = int(data_format_line.split(':')[1].strip().split()[0])

            print(f"{headline}, Sampling Frequency: {sampling_frequency} {unit}, Data Format: {data_format} Bits")

            input_samples = []
            output_samples = []
            input_zero_crossings = []
            output_zero_crossings = []

            while True:
                line = ser.readline().strip().decode('utf-8', errors='ignore')
                print(f"{line}")  # Debug log
                if line == 'Input Buffer Sending':
                    input_samples = read_samples_from_uart(ser, b'Input Buffer Over', 'Input', data_format)
                    input_zero_crossings = find_zero_crossings(input_samples)
                elif line == 'Output Buffer Sending':
                    output_samples = read_samples_from_uart(ser, b'Output Buffer Over', 'Output', data_format)
                    output_zero_crossings = find_zero_crossings(output_samples)
                elif line == 'Data End':
                    buffer_index += 1
                    data_sets.append((input_samples, output_samples, input_zero_crossings, output_zero_crossings, buffer_index, headline, sampling_frequency, unit))
                    break
        elif line == 'All Over':
            break

    ser.close()

    # Plot all data sets
    for data_set in data_sets:
        plot_samples(*data_set)

if __name__ == "__main__":
    main()
