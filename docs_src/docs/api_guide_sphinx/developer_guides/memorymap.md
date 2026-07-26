# Memory Map Layout
## Introduction

This section explains the default DDR memory layout for {{ VAR_SOC_NAME }}.


## DDR

Below picture shows the memory layout details of DDR.


:::{only} SOC_AM62X
           0x80000000 +--------------------------------------+
                   |               TF-A                   |
        0x80200000 +--------------------------------------+
                   |            Used by Linux             |
        0x80400000 +--------------------------------------+
                   |          Temporarily used by         |
                   |       SBL for authentication of      |
                   |       images. Will be used by Linux  |
                   |       after Linux is booted          |
        0x80590000 +--------------------------------------+
                   |            Used by Linux             |
        0x9C800000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |   between MCU M4F and WKUP R5F       |
        0x9CB00000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |     between Linux and MCU M4F        |
        0x9CC00000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |     between Linux and MCU M4F        |
        0x9CC01000 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |     between Linux and MCU M4F        |
        0x9D9F0000 +--------------------------------------+
                   |     Code/Data for MCU M4F            |
        0x9DA00000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |     between Linux and WKUP R5F       |
        0x9DB00000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |     between Linux and WKUP R5F       |
        0x9DB01000 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |     between Linux and WKUP R5F       |
        0x9DC00000 +--------------------------------------+
                   |     Code/Data for WKUP R5F           |
        0x9E700000 +--------------------------------------+
                   |            Used by Linux             |
        0x9E780000 +--------------------------------------+
                   |           TF-A during R5 SPL         |
                   |  (TF_A is relocated to 0x80000000    |
                   |             after R5F SPL)           |
        0x9E800000 +--------------------------------------+
                   |                OP-TEE                |
        0xA0000000 +--------------------------------------+
                   |            Used by Linux             |
                   +--------------------------------------+
   :::


:::{only} SOC_AM62AX
           0x80000000 +--------------------------------------+
                   |      TF-A                            |
        0x80200000 +--------------------------------------+
                   |            Used by Linux             |
        0x80400000 +--------------------------------------+
                   |          Temporarily used by         |
                   |       SBL for authentication of      |
                   |       images. Will be used by Linux  |
                   |       after Linux is booted          |
        0x80590000 +--------------------------------------+
                   |            Used by Linux             |
        0x99800000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |        between Linux and C7x         |
        0x99900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |        between Linux and C7x         |
        0x99900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |        between Linux and C7x         |
        0x99A00000 +--------------------------------------+
                   |           C7x Boot section           |
        0x99A00400 +--------------------------------------+
                   |                Unused                |
        0x99C00000 +--------------------------------------+
                   |              C7x Vectors             |
        0x99C04000 +--------------------------------------+
                   |                Unused                |
        0x99C10000 +--------------------------------------+
                   |           Code/Data for C7x          |
        0x9B800000 +--------------------------------------+
                   |         IPC VRING Used for IPC       |
                   |       between Linux and MCU R5F      |
        0x9B900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |       between Linux and MCU R5F      |
        0x9B900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |       between Linux and MCU R5F      |
        0x9BA00000 +--------------------------------------+
                   |           Code/Data for MCU R5F      |
        0x9C800000 +--------------------------------------+
                   |         IPC VRING Used for IPC       |
                   |       between Linux and WKUP R5F     |
        0x9C900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |       between Linux and WKUP R5F     |
        0x9C900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |       between Linux and WKUP R5F     |
        0x9CA00000 +--------------------------------------+
                   |        Code/Data for WKUP R5F        |
        0x9E700000 +--------------------------------------+
                   |       TIFS LPM context save memory   |
        0x9E780000 +--------------------------------------+
                   |           TF-A during R5 SPL         |
                   |  (TF_A is relocated to 0x80000000    |
                   |             after R5F SPL)           |
        0x9E800000 +--------------------------------------+
                   |                OPTEE                 |
        0xA0000000 +--------------------------------------+
                   |         IPC VRING Used for IPC       |
                   |     between MCU R5F, C7x, WKUP R5F   |
        0xA1000000 +--------------------------------------+
                   |           Remore core logging        |
        0xA1040000 +--------------------------------------+
                   |         TI OpenVX shared memory      |
        0xA2000000 +--------------------------------------+
                   |       Remote core file operations    |
        0xA2400000 +--------------------------------------+
                   |     TI OpenVX shared memory for      |
                   |            Run-time logging          |
        0xA3000000 +--------------------------------------+
                   |            Shared buffers            |
        0xAE000000 +--------------------------------------+
                   |         Local Heap for MCU R5F       |
        0xAF000000 +--------------------------------------+
                   |         Local Heap for WKUP R5F      |
        0xB0000000 +--------------------------------------+
                   |  Non-cacheable local Heap for C7x    |
        0xB1000000 +--------------------------------------+
                   | Non-cacheable scratch memory for C7x |
        0xB2000000 +--------------------------------------+
                   |         Local Heap for C7x           |
        0xB9000000 +--------------------------------------+
                   |         Local scratch for C7x        |
        0xC0000000 +--------------------------------------+
                   |              Used by Linux           |
                   +--------------------------------------+
   :::


:::{only} SOC_AM62PX
           0x80000000 +--------------------------------------+
                   |              TF-A                    |
        0x80200000 +--------------------------------------+
                   |            Used by Linux             |
        0x80400000 +--------------------------------------+
                   |          Temporarily used by         |
                   |       SBL for authentication of      |
                   |       images. Will be used by Linux  |
                   |       after Linux is booted          |
        0x80590000 +--------------------------------------+
                   |            Used by Linux             |
        0x93500000 +--------------------------------------+
                   |       DSS Framebuffer used in        |
                   |       display sharing usecase        |
        0x9B500000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |   between MCU R5F and WKUP R5F       |
        0x9B800000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |     between Linux and MCU R5F        |
        0x9B900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |     between Linux and MCU R5F        |
        0x9B900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |     between Linux and MCU R5F        |
        0x9BA00000 +--------------------------------------+
                   |     Code/Data for MCU R5F            |
        0x9C800000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |     between Linux and WKUP R5F       |
        0x9C900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |     between Linux and WKUP R5F       |
        0x9C900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |     between Linux and WKUP R5F       |
        0x9CA00000 +--------------------------------------+
                   |     Code/Data for WKUP R5F           |
        0x9E700000 +--------------------------------------+
                   |            Used by Linux             |
        0x9E780000 +--------------------------------------+
                   |           TF-A during R5 SPL         |
                   |  (TF_A is relocated to 0x80000000    |
                   |             after R5F SPL)           |
        0x9E800000 +--------------------------------------+
                   |                OP-TEE                |
        0xA0000000 +--------------------------------------+
                   |            Used by Linux             |
                   +--------------------------------------+
   :::


:::{only} SOC_AM62DX
           0x80000000 +--------------------------------------+
                   |                TF-A                  |
        0x80200000 +--------------------------------------+
                   |            Used by Linux             |
        0x80400000 +--------------------------------------+
                   |          Temporarily used by         |
                   |       SBL for authentication of      |
                   |       images. Will be used by Linux  |
                   |       after Linux is booted          |
        0x80590000 +--------------------------------------+
                   |            Used by Linux             |
        0x99800000 +--------------------------------------+
                   |       IPC VRING Used for IPC         |
                   |        between Linux and C7x         |
        0x99900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |        between Linux and C7x         |
        0x99900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |        between Linux and C7x         |
        0x99A00000 +--------------------------------------+
                   |           C7x Boot section           |
        0x99A00400 +--------------------------------------+
                   |                Unused                |
        0x99C00000 +--------------------------------------+
                   |              C7x Vectors             |
        0x99C04000 +--------------------------------------+
                   |                Unused                |
        0x99C10000 +--------------------------------------+
                   |           Code/Data for C7x          |
        0x9B800000 +--------------------------------------+
                   |         IPC VRING Used for IPC       |
                   |       between Linux and MCU R5F      |
        0x9B900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |       between Linux and MCU R5F      |
        0x9B900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |       between Linux and MCU R5F      |
        0x9BA00000 +--------------------------------------+
                   |           Code/Data for MCU R5F      |
        0x9C800000 +--------------------------------------+
                   |         IPC VRING Used for IPC       |
                   |       between Linux and WKUP R5F     |
        0x9C900000 +--------------------------------------+
                   |    IPC Resource table Used for IPC   |
                   |       between Linux and WKUP R5F     |
        0x9C900400 +--------------------------------------+
                   |     IPC trace buffer used for IPC    |
                   |       between Linux and WKUP R5F     |
        0x9CA00000 +--------------------------------------+
                   |        Code/Data for WKUP R5F        |
        0x9E700000 +--------------------------------------+
                   |       TIFS LPM context save memory   |
        0x9E780000 +--------------------------------------+
                   |           TF-A during R5 SPL         |
                   |  (TF_A is relocated to 0x80000000    |
                   |             after R5F SPL)           |
        0x9E800000 +--------------------------------------+
                   |                OPTEE                 |
        0xA0000000 +--------------------------------------+
                   |         IPC VRING Used for IPC       |
                   |     between MCU R5F, C7x, WKUP R5F   |
        0xA1000000 +--------------------------------------+
                   |              Used by Linux           |
                   +--------------------------------------+
   :::
