# SD Card Images for AM275X-EVM Media Boot Test

These files are pre-built signed multicore ELF (mcelf) binaries that must be
placed at the root of an SD card (FAT32 partition) for SD-based boot test
cases on AM275X.

AM275X has no A53 core. Its secondary cores are R5FSS and C75SS instances.
Boot images use the `.mcelf.hs_fs` format instead of `.appimage.hs_fs` used
on AM62DX/AM62AX.

## Required Files

| Filename | Source                                                                                          | Description                      |
|----------|-------------------------------------------------------------------------------------------------|----------------------------------|
| app_r5   | examples/drivers/ipc/ipc_rpmsg_echo/am275x-evm/r5fss0-0_freertos/ti-arm-clang/                | R5FSS0-0 single-core mcelf image |
| app_c75  | examples/drivers/ipc/ipc_rpmsg_echo/am275x-evm/c75ss0-0_freertos/ti-c7000/                    | C75SS0-0 single-core mcelf image |
| app_sys  | test/drivers/boot/sbl_test_multithread/sbl_test_custom_ipc_binary/am275x-evm/system_freertos/  | All-core multicore mcelf image   |

| app_inv  | Intentionally corrupted copy of app_r5 (flip a byte to make signature invalid)                 | Invalid image for negative tests |

## How to Generate

### 1. Build the source examples

```bash
cd <SDK_ROOT>
make ipc_rpmsg_echo BOARD=am275x-evm PROFILE=release
make -C test/drivers/boot/sbl_test_multithread/sbl_test_custom_ipc_binary/am275x-evm/system_freertos PROFILE=release
```

### 2. Copy built images to this directory

```bash
cd <SDK_ROOT>/test/drivers/boot/sbl_test_media_boot/am275x-evm/sd_images

cp <SDK_ROOT>/examples/drivers/ipc/ipc_rpmsg_echo/am275x-evm/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.release.mcelf.hs_fs  app_r5
cp <SDK_ROOT>/examples/drivers/ipc/ipc_rpmsg_echo/am275x-evm/c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo.release.mcelf.hs_fs       app_c75
cp <SDK_ROOT>/test/drivers/boot/sbl_test_multithread/sbl_test_custom_ipc_binary/am275x-evm/system_freertos/sbl_test_custom_ipc_binary_system.release.mcelf.hs_fs  app_sys
```

### 3. Generate app_inv (corrupted image for authentication-failure test)

```python
import shutil
shutil.copy('app_r5', 'app_inv')
with open('app_inv', 'r+b') as f:
    f.seek(4)
    f.write(bytes([f.read(1)[0] ^ 0xFF]))
```

---

## Formatting the SD Card (FAT32) and Flashing Images

### Step 1 — Identify the SD card device

Insert the SD card and run:

```bash
lsblk
```

Note the device node (e.g. `/dev/sdX`). Verify it is your SD card before
proceeding — the next steps will erase all data on that device.

### Step 2 — Unmount any mounted partitions

```bash
sudo umount /dev/sdX1   # repeat for each partition shown by lsblk
```

### Step 3 — Create a FAT32 partition

```bash
sudo parted /dev/sdX --script \
    mklabel msdos \
    mkpart primary fat32 1MiB 100%
```

### Step 4 — Format as FAT32

```bash
sudo mkfs.vfat -F 32 -n BOOT /dev/sdX1
```

### Step 5 — Mount and copy images

```bash
sudo mkdir -p /mnt/sdcard
sudo mount /dev/sdX1 /mnt/sdcard

sudo cp app_r5  /mnt/sdcard/
sudo cp app_c75 /mnt/sdcard/
sudo cp app_sys /mnt/sdcard/
sudo cp app_inv /mnt/sdcard/

sync
sudo umount /mnt/sdcard
```

The SD card is now ready. Insert it into the AM275X-EVM and run the media boot
test.
