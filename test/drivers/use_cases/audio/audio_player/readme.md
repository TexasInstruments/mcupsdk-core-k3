# Audio Player Example for AM62Ax EVM

This README provides step-by-step instructions to set up, build, flash, and run the audio player example on the Texas Instruments AM62Ax EVM. It covers SD card preparation, flashing, peripheral allocation, and program control via UART and GPIO.

This demo implements an audio player on AM62A EVM. The features of the player are as follows
 - Mode 0 : Play voice from mic on the speaker
 - Mode 1 : Play raw audio files from SD card (Only 16bit and 32 bit 48khz files supported)
 - Mode 2: Mix and play the voice from SD card and mic together

The player can be controlled using commands from MCU UART 0 and also using the GPIO push button SW5

This example makes use of following peripherals
 - McASP : For the audio recording and playback
 - I2C   : For controlling the TLV320AIC31 codec
 - UDMA  : For tranfer of data between McASP and CPU
 - GPIO  : To control the modes of the player
 - UART  : To control the properties of player like mix ratio

---

## 1. Prerequisites
- **AM62Ax EVM** (Evaluation Module)
- **SD Card** (FAT32 formatted, 4GB or larger recommended)
- **Headphones** (3.5mm jack)
- **Micro USB cable** (for UART console)
- **Linux Host PC** (for building/flashing)
- **TI MCU+ SDK** (this repository)
- **CCS or makefile build environment**

---

## 2. SD Card Preparation
1. **Format SD Card**
   - Use <SDK_PATH>/examples/drivers/mmcsd/mmcsd_file_io to create FAT partition.
2. **Copy WAV Files**
   - Place 16-bit/32-bit, 48kHz stereo `.wav` files in the root directory of the SD card.
   - Sample audio files (16 bit and 32 bit are available in audio_files folder)
3. **Eject SD Card** safely from your PC.

---

## 3. Building the Audio Player Example
1. **Build the example**
   - Navigate to the example directory:
     ```sh
     cd <SDK_PATH>/test/drivers/use_cases/audio/audio_player
     make all
     ```
   - Output binary (e.g., `audio_player_am62ax_evm_release.appimage`) will be in the output folder.

---

## 4. Flashing the Binary
1. **Copy the binary to SD card** (if booting from SD):
   - Place the `.appimage` in the SD card root.
2. **Or, flash to EVM using UART/XDS110/JTAG**:
   - Use UniFlash or CCS to flash the binary to the appropriate memory (refer to SDK documentation for details).

---

## 5. Peripheral Allocation
- **SD Card Slot**: Insert SD card into the EVM's SD slot (usually marked as "MMC/SD").
- **Headphone Jack**: Plug headphones into the 3.5mm audio out jack.
- **UART**: Connect micro USB cable from EVM to host PC (for serial console, Use UART0 & MCU_USART0).
- **GPIO/Interrupt Pin**: `GPIO_PUSH_BUTTON - SW5` is used as interrupt button

---

## 6. Running the Example
1. **Power on the EVM**
2. **Open UART Terminal**
   - Use `minicom`, `screen`, or `PuTTY` on your PC.
   - Typical settings: `115200 8N1`, no flow control.
   - `minicom -D /dev/ttyUSB0 -b 115200` - for debug logs
   - `minicom -D /dev/ttyUSB3 -b 115200` - for debug logs

3. **Monitor Boot and Logs**
   - You should see logs from the audio player application.

---

## 7. Program Control
### UART Commands
- The program accepts commands via UART (ttyUSB3). Typical controls:
  - `n` : Next track
  - `m<mix value>` : To control audio mix ratio. Pass value from 0-9

### GPIO Control
- If enabled, a button connected to the assigned GPIO pin can:
  - change different modes of the player
- GPIO pin assignment is defined in `audio_player.c` (e.g., `GPIO_USER_BUTTON`).

---

