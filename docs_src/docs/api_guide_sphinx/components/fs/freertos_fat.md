# FreeRTOS+FAT File System
## Introduction

FreeRTOS+FAT is an open source, thread aware and scalable FAT12/FAT16/FAT32 DOS/Windows compatible embedded FAT file system for use with and without the RTOS.

In this SDK, FreeRTOS+FAT is integrated to work with the MMCSD driver. The porting layer supports any device (SD/eMMC) connected to the MMCSD ports 0 or 1. There is SysConfig support for the FreeRTOS+FAT integrated module. So, to use the FreeRTOS+FAT in your application, just add the FreeRTOS+FAT module under `FILE SYSTEMS` in the SysConfig. It will automatically add an MMCSD instance. The underlying media can be selected in the FreeRTOS+FAT SysConfig config. Currently "SD" and "EMMC" can be selected.

FreeRTOS+FAT is also used in the Secondary Bootloader application which uses SD card as boot media.
You can refer to these examples here for API usage. Most of the initialization is done by the Sysconfig itself.


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X
   - [SBL SD](../../examples/drivers/sbl_sd.md)
:::

- [MMCSD FILE IO](../../examples/drivers/mmcsd_file_io.md)

For the full FreeRTOS+FAT API reference, please refer to the below table.

## Additional References
<table>
<tr>
    <th>Website Link
    <th>Description
</tr>
<tr>
    <td><a href="https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/index.html">FreeRTOS+FAT File System</a>
    <td>Complete documentation of the FreeRTOS+FAT file system and API references
</tr>
</table>
