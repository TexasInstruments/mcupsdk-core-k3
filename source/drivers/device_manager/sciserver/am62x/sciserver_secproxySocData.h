/*
 * System Firmware Source File
 *
 * SoC defines for secure proxy instances for AM62X device
 *
 * Data version: 220527_134115
 *
 * Copyright (C) 2021-2022 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_AM62X_SPROXY_SOC_DATA_H
#define SOC_AM62X_SPROXY_SOC_DATA_H


/** Number of Secure Proxy instances */
#define SOC_MAX_SEC_PROXY_INSTANCES (0x02U)
/*
 * AM62X_SPROXY_IDX_DMASS0_SEC_PROXY_0: Secure proxy instance:
 * DMASS0_SEC_PROXY_0 linked to RA inst: DMASS0_RINGACC_0
 */
#define AM62X_SPROXY_IDX_DMASS0_SEC_PROXY_0 (0x00U)
/*
 * AM62X_SPROXY_IDX_SA3_SS0_SEC_PROXY_0: Secure proxy instance:
 * SA3_SS0_SEC_PROXY_0 linked to RA inst: SA3_SS0_RINGACC_0
 */
#define AM62X_SPROXY_IDX_SA3_SS0_SEC_PROXY_0 (0x01U)

/** Secure Proxy instance used by ROM */
#define ROM_SEC_PROXY_IDX AM62X_SPROXY_IDX_SA3_SS0_SEC_PROXY_0

#endif /* SOC_AM62X_SPROXY_SOC_DATA_H */
