/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for AM62X device.
 *
 * Data version: 220527_134115
 *
 * Copyright (C) 2021-2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_AM62X_DEVGRPS_H
#define SOC_AM62X_DEVGRPS_H

#include <types/devgrps.h>

/**
 * Set of MCU domain peripherals to initialize at boot and use during runtime.
 */
#define SOC_DEVGRP_AM62X_MCU_WAKEUP DEVGRP_01

/**
 * Set of Main domain peripherals to initialize at boot and use during
 * runtime.
 */
#define SOC_DEVGRP_AM62X_MAIN DEVGRP_00

/**
 * Set of peripherals to initialize for System Firmware internal usage
 */
#define SOC_DEVGRP_AM62X_TIFS_INTERNAL DEVGRP_DMSC


#endif /* SOC_AM62X_DEVGRPS_H */
