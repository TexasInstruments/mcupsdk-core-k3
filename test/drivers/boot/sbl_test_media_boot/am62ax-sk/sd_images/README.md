# SD Card Images for AM62AX-SK Media Boot Test

These files are pre-built signed appimage binaries that must be placed at the
root of an SD card (FAT32 partition) for the sbl_test_media_boot test to run
the SD boot test cases.

## Required Files

| Filename  | Source                                                                          | Description                  |
|-----------|---------------------------------------------------------------------------------|------------------------------|
| app_a53   | examples/drivers/ipc/ipc_rpmsg_echo/am62ax-sk/a53ss0-0_nortos/gcc-aarch64/     | A53 single-core appimage     |
| app_smp   | test/drivers/mmcsd/test_mmcsd_fs_io/am62ax-sk/a53ss0-0_freertos-smp/gcc-aarch64 | A53 SMP appimage             |
| app_sys   | test/drivers/ipc_rpmsg/am62ax-sk/system_freertos/                               | Multicore system appimage    |
| app_inv   | Intentionally corrupted copy of app_a53 (flip a byte to make signature invalid) | Invalid appimage for neg test |

## How to Generate

1. Build the source examples:
   ```
   cd <SDK_ROOT>
   make ipc_rpmsg_echo BOARD=am62ax-sk PROFILE=release
   make test_mmcsd_fs_io BOARD=am62ax-sk PROFILE=release
   make test_ipc_rpmsg_system BOARD=am62ax-sk PROFILE=release
   ```

2. Copy the built `.appimage.hs_fs` files to this directory with the
   corresponding filenames listed above.

3. For `app_inv`, copy `app_a53` and corrupt a byte in the signature region:
   ```python
   import shutil
   shutil.copy('app_a53', 'app_inv')
   with open('app_inv', 'r+b') as f:
       f.seek(4)
       f.write(bytes([f.read(1)[0] ^ 0xFF]))
   ```

4. Copy all four files to the root of a FAT32-formatted SD card.
