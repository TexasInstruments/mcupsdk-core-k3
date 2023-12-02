#ifndef SOC_AM62X_SELF_RESET_CONFIG_H
#define SOC_AM62X_SELF_RESET_CONFIG_H

#ifndef MCU_PLUS_SDK

#include <ti/drv/sciclient/sciclient.h>
#include <ti/drv/sciclient/soc/sysfw/include/am62x/tisci_hosts.h>

#else

#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_hosts.h>

#endif

// This file contains the soc specific flags for dm r5 self reset

#define SELF_RESET_PROCESSOR_ID         SCICLIENT_DEV_MCU_R5FSS0_CORE0_PROCID
#define SELF_RESET_DEVICE_ID            TISCI_DEV_R5FSS0_CORE0
#define SELF_RESET_BOOT_ADDRESS_LOW     0x00000000
#define SELF_RESET_SET_CONFIG_FLAGS     TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN | TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_MEM_INIT_DIS
#define SELF_RESET_CLEAR_CONFIGD_FLAGS  TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE
#define SELF_RESET_TCM_ADDRESS_OFFSET   0x41010000


#endif
