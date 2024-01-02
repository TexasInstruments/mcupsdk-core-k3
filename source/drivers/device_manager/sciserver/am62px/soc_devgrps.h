/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for AM62PX device.
 *
 * Data version: 230227_171532
 *
 * Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_AM62PX_DEVGRPS_H
#define SOC_AM62PX_DEVGRPS_H

#include <types/devgrps.h>

/**
 * Set of MCU domain peripherals to initialize at boot and use during runtime.
 */
#define SOC_DEVGRP_AM62PX_MCU_WAKEUP DEVGRP_01

/**
 * Set of Main domain peripherals to initialize at boot and use during
 * runtime.
 */
#define SOC_DEVGRP_AM62PX_MAIN DEVGRP_00

/**
 * Set of peripherals to initialize for System Firmware internal usage
 */
#define SOC_DEVGRP_AM62PX_TIFS_INTERNAL DEVGRP_DMSC

/**
 * Set of peripherals to initialize for TIFS HSM internal usage
 */
#define SOC_DEVGRP_AM62PX_HSM_INTERNAL DEVGRP_HSM


#endif /* SOC_AM62PX_DEVGRPS_H */
