/*
 * System Firmware Source File
 *
 * PM subsystem board configuration data
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This software is licensed under the standard terms and conditions in the
 * Texas Instruments Incorporated Technology and Software Publicly
 * Available Software License Agreement, a copy of which is included in
 * the software download.
 */


#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_hosts.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_boardcfg_constraints.h>

struct tisci_boardcfg_pm {
    struct tisci_boardcfg_abi_rev    rev;
} __attribute__((__packed__));

const struct tisci_boardcfg_pm gBoardConfigLow_pm = {
    /* boardcfg_abi_rev */
    .rev =
    {
        .tisci_boardcfg_abi_maj          = TISCI_BOARDCFG_RM_ABI_MAJ_VALUE,
        .tisci_boardcfg_abi_min          = TISCI_BOARDCFG_RM_ABI_MIN_VALUE
    }
};