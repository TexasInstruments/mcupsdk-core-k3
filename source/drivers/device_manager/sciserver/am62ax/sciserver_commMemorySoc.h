/*
 * System Firmware Source File
 *
 * Memory instances for communication paths in AM62A device.
 *
 * Data version: 220316_180112
 *
 * Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_AM62A_COMM_MEMORY_H
#define SOC_AM62A_COMM_MEMORY_H

/** Number of unique memories on the SoC */
#define COMM_MEMORY_INSTANCE_COUNT (2U)

/**
 * dmss_ipc_sram: dmss_ipc_sram
 */
#define AM62A_SPROXY_MEM_IDX_DMSS_IPC_SRAM (0U)
/**
 * dmss_hsm_ipc_sram: dmss_hsm_ipc_sram
 */
#define AM62A_SPROXY_MEM_IDX_DMSS_HSM_IPC_SRAM (1U)


#endif /* SOC_AM62A_COMM_MEMORY_H */
