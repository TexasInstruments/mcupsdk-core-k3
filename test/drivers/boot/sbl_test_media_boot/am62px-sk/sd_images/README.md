# SD Card Images for AM62PX-SK Media Boot Test

These files are pre-built signed appimage binaries that must be placed at the
root of an SD card (FAT32 partition) for the sbl_test_media_boot test to run
the SD boot test cases on am62px-sk.

## Reduced file set

AM62Px has no A53 or C75/DSP core in silicon, and this SDK checkout has no
A53 (or C75) example board support for am62px-sk (e.g. no
`a53ss0-0_*`/`c75ss0-0_*` example directories exist under
`examples/drivers/ipc/ipc_rpmsg_echo/am62px-sk/`). As a result the
`app_a53`, `app_smp`, and any C75-containing multicore image that the
am62ax-sk/am62dx-evm version of this test uses are **not** included here.

On am62px-sk the generic SD-boot sub-tests (`TestSbl_singleCoreImageSdBoot`,
`TestSbl_validateSingleCorePresent`, `TestSbl_runInvalidCore`,
`TestSbl_runSelfCpuSdBoot`, `TestSbl_powerOffAfterLoadSuccess`, etc.) run
against the MCU-R5F image `app_r5` instead of `app_a53` — see the
`TEST_SBL_SD_BOOT_*` macros in `test_sbl_media_boot.c`. Only the A53 SMP
boot tests (`TestSbl_sdSmpBoot`, `TestSbl_emmcSmpBoot`, `TestSbl_ospiSmpBoot`)
remain excluded (see the `#if !defined(SOC_AM62PX)` guard in `test_main()`),
because they need a 4-core A53 SMP appimage that cannot be built from this
SDK checkout.

Only three files are needed for am62px-sk:

## Required Files

| Filename | Source                                                                    | Description                        |
|----------|----------------------------------------------------------------------------|-------------------------------------|
| app_r5   | `examples/drivers/ipc/ipc_rpmsg_echo/am62px-sk/mcu-r5fss0-0_freertos/`    | MCU-R5F single-core appimage        |
| app_sys  | `test/drivers/ipc_rpmsg/am62px-sk/system_freertos/`                       | Multicore (MCU-R5F + WKUP-R5F) system appimage |
| app_inv  | Intentionally corrupted copy of app_r5 (flip a byte to make signature invalid) | Invalid appimage for negative test |

Notes:
- `app_sys` on am62px-sk contains only the two R5F cores (`wkup-r5fss0-0`
  and `mcu-r5fss0-0`) — there is no A53 or C75 core in the image, since no
  such example board exists for am62px-sk. It is still a valid multicore
  appimage and is used by `TestSbl_loadTimeBenchmark`'s SD-read benchmark
  (via `TEST_SBL_SD_MULTICORE_IMG` / `ff_fopen`), which already treats a
  missing/absent file as a soft skip rather than a failure.
- There is no `app_a53` or `app_smp` file for am62px-sk. Any sub-test that
  would need one is excluded from the am62px-sk test registration (see
  above), so its absence has no effect on the tests that actually run.

`app_r5`, `app_sys`, and `app_inv` are already present in this directory,
built from this SDK checkout. To regenerate them from scratch:

## How to Generate

1. Build the source examples:
   ```
   cd <SDK_ROOT>
   make ipc_rpmsg_echo BOARD=am62px-sk CORE=mcu-r5fss0-0 PROFILE=release
   make -C test/drivers/ipc_rpmsg/am62px-sk/system_freertos PROFILE=release
   ```

2. Copy the built `.appimage.hs_fs` files to this directory with the
   corresponding filenames listed above:
   ```
   cp examples/drivers/ipc/ipc_rpmsg_echo/am62px-sk/mcu-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.release.appimage.hs_fs app_r5
   cp test/drivers/ipc_rpmsg/am62px-sk/system_freertos/test_ipc_rpmsg_system.release.appimage.hs_fs app_sys
   ```

3. For `app_inv`, copy `app_r5` and corrupt a byte in the signature region:
   ```python
   import shutil
   shutil.copy('app_r5', 'app_inv')
   with open('app_inv', 'r+b') as f:
       f.seek(4)
       f.write(bytes([f.read(1)[0] ^ 0xFF]))
   ```

4. Copy all three files (`app_r5`, `app_sys`, `app_inv`) to the root of a
   FAT32-formatted SD card.

## Not included (no am62px-sk board support in this SDK checkout)

- `app_a53` — would require an `a53ss0-0_*` example build; none exists for
  am62px-sk in this SDK.
- `app_smp` — would require a 4-core A53 SMP example build; none exists for
  am62px-sk in this SDK.
