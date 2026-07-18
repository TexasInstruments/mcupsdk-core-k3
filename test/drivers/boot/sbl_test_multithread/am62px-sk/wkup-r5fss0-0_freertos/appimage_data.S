/*
 * Assembly file to embed the per-core signed appimage file (.hs_fs) as an
 * initialized data section at a fixed DDR address.
 *
 * When the SBL loads the test binary, this data section is loaded to the
 * DDR buffer address. The test's MEM bootloader then authenticates and
 * parses the appimage data from this address.
 *
 * Unlike am62ax-sk/am62dx-evm (which embed MCU-R5F, A53, and C75 appimages
 * at 0x86000000 / 0x86800000 / 0x87000000), this board/checkout has no A53
 * or C75 example appimage available for am62px-sk (see
 * sbl_test_custom_ipc_binary/am62px-sk — only mcu-r5fss0-0_freertos,
 * wkup-r5fss0-0_freertos and system_freertos_nortos exist). Only the
 * MCU-R5F core's appimage (gAppImageBuf0) is embedded here.
 *
 * The .incbin path is relative to the build directory
 * (am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/).
 */

    .section .data.appimage_buf0,"aw"
    .balign 128
    .global gAppImageBuf0
    .type gAppImageBuf0, %object
gAppImageBuf0:
    .incbin "../../../sbl_test_custom_ipc_binary/am62px-sk/mcu-r5fss0-0_freertos/ti-arm-clang/sbl_test_custom_ipc_binary.release.appimage.hs_fs"
    .size gAppImageBuf0, . - gAppImageBuf0
