/*
 * Assembly file to embed per-core signed appimage files (.hs_fs) as
 * initialized data sections at fixed DDR addresses.
 *
 * When the SBL loads the test binary, these data sections are loaded
 * to the DDR buffer addresses. The test's MEM bootloader then
 * authenticates and parses the appimage data from these addresses.
 *
 * The .incbin paths are relative to the build directory
 * (am62x-sk/r5fss0-0_freertos/ti-arm-clang/).
 */

    .section .data.appimage_buf0,"aw"
    .balign 128
    .global gAppImageBuf0
    .type gAppImageBuf0, %object
gAppImageBuf0:
    .incbin "../../../sbl_test_custom_ipc_binary/am62x-sk/m4fss0-0_nortos/ti-arm-clang/sbl_test_custom_ipc_binary.release.appimage.hs_fs"
    .size gAppImageBuf0, . - gAppImageBuf0

    .section .data.appimage_buf1,"aw"
    .balign 128
    .global gAppImageBuf1
    .type gAppImageBuf1, %object
gAppImageBuf1:
    .incbin "../../../sbl_test_custom_ipc_binary/am62x-sk/a53ss0-0_freertos/gcc-aarch64/sbl_test_custom_ipc_binary.release.appimage.hs_fs"
    .size gAppImageBuf1, . - gAppImageBuf1
