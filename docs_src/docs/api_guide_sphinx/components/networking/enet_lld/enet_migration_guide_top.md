# Enet Migration Guide

```{contents}
:depth: 2
:local:
```

## Introduction

Enet LLD Migration guide explains the rationale for syscfg integration and the associated changes needed in application.

## Need for Sysconfig

Enet LLD enables syscfg based module configuration. This impacts applications using the enet driver that are migrating from previous releases. The rationale for deep syscfg integration with enet driver is:

- The Enet LLD driver contains core specific, board specific code. However in MCU+SDK all module libraries can only be SOC+ISA specific. There is no option to have core specific or board specific options when building a library. This required users of enet library to modify enet source code that is not built for the default core/board combo and recompile the enet library. This issue has been addressed by ensuring portions that are core or board specific are part of syscfg template that are compiled as part of application.
- Migrating open params of a module from C based to Sysconfig generated has other advantages:
  - Range check for all values at config time instead of runtime parameter checks.
  - Validation checks based on external module configuration like Clock config.
  - Avoid uninitialized members in open params structure.
  - Allows creation of external module instances needed by enet lld without requiring application integrator to understand enet module external dependency (UDMA, I2C, PRU instances).
  - Allows sizing of data structures in enet driver based on application config - tx/rx dma channels, phy instances, resource manager configuration, packet buffers, etc.
  - Enet LLD Driver library is built with close to zero r/w memory footprint.

## Enet Driver Initialization Sequence Change

**Impact**: The init sequence change impacts both ICSSG and CPSW peripherals on all SoCs.

| Old Init Sequence | New Init Sequence |
|---|---|
| 1. `Enet_initOsalCfg()` | 1. Implement `EnetApp_updateCpswOpenParams()` or `EnetApp_updateIcssgOpenParams()` |
| 2. `Enet_initUtilsCfg()` | 2. Implement `EnetApp_initLinkArgs()` to set mac and phy params for each macPort |
| 3. `Enet_init(osalCfg, utilsCfg)` | 3. Invoke `EnetApp_driverOpen(enetType, instId)` |
| 4. `Enet_initCfg()` | 4. Get handle via `EnetApp_acquirehandleInfo()` |
| 5. Update Enet open params | |
| 6. `hEnet = Enet_open(..openParams)` | |
| 7. For each macPort: init mac/phy link params, open macPort | |
| 8. Create PHY state machine task | |

## Enet DMA Channel Open Changes

**Impact**: The DMA channel open change impacts both ICSSG and CPSW peripherals on all SoCs. Only applications that directly invoke Enet driver packet transmit and receive APIs are impacted (LwIP based applications are not impacted).

The `EnetDma_openRxCh()` and `EnetDma_openTxCh()` DMA channel open was previously application callable APIs. Supporting application invocable APIs for Tx and Rx DMA channel open required enet driver to support worst case number for Tx and Rx channels irrespective of actual number used.

To ensure the DMA channel and associated rings are sized to correct value based on application usecase, DMA channel configuration is now supported via syscfg.

The syscfg generated `EnetApp_driverOpen` function internally opens all configured DMA channels. Application can no longer open DMA channels directly.

Application gets handle to DMA channel by passing the DMA channel instance identifier used in `example.syscfg`:
- `enet_cpsw1.txDmaChannel[0].$name = "ENET_DMA_TX_CH0"`
- `enet_cpsw1.rxDmaChannel[0].$name = "ENET_DMA_RX_CH0"`

To get DMA channel handle application invokes:
- `EnetApp_getTxDmaHandle(ENET_DMA_TX_CH0, &txInArgs, &txChInfo);`
- `EnetApp_getRxDmaHandle(ENET_DMA_RX_CH0, &rxInArgs, &rxChInfo);`

## Runtime Control API (Enet_ioctl) Change

**Impact**: The init sequence change impacts both ICSSG and CPSW peripherals on all SoCs.

| Old Method | New Method |
|---|---|
| `status = Enet_ioctl(hEnet, coreId, IOCTL_CMD, &ioctlPrms);` | `ENET_IOCTL(hEnet, coreId, IOCTL_CMD, &prms, ioctlReturnStatus);` |

`ENET_IOCTL` is a macro that first registers the handler function for the IOCTL cmd and then invokes the actual `Enet_ioctl` API. This allows the linker to link in only IOCTLs used by application.

**Note:** Do not invoke `Enet_ioctl` API directly from application. The `IOCTL_CMD` must be an `ENET_IOCTL` cmd enum and cannot be a variable.

## Packet Transmit/Receive API Related Changes

### Scatter Gather List Related Change

**Impact**: Impacts CPSW peripherals on AM263x/AM273x/AWR294x. Only applications that directly invoke `EnetDma_submitTxPktQ()` are impacted.

`EnetDma_Pkt` is modified to support scatter gather. Application should invoke `EnetDma_initPktInfo` API to initialize `EnetDma_Pkt` to default values. If not using scatter gather, set:
- `EnetDma_Pkt.bufPtrFilledLen = EnetDma_Pkt.txTotalPktLen = length of tx packet`

### DisableCacheOps Related Change

**Impact**: Impacts CPSW peripherals on AM263x/AM273x/AWR294x.

By default, Enet driver will perform cache coherency operation on packet before submitting to enet DMA engine. If application does not want to use this feature, invoke `EnetDma_initPktInfo()` API to initialize `EnetDma_Pkt` structure to default values where `EnetDma_Pkt.disableCacheOps` is set to FALSE.

### Checksum Offload Related Change

**Impact**: Impacts CPSW peripheral based applications on AM263x.

`EnetDma_Pkt` is modified to support checksum offload by adding `chkSumInfo`. For applications that directly invoke Enet driver packet transmit APIs, set `EnetDma_Pkt.chkSumInfo = 0`.

## Custom Board Support

The MCU+SDK enet driver supports a set of boards for each SoC out of the box. The board specific portion of the enet code is auto generated in `ti_board_config.c` for supported boards.

For porting enet based applications to a custom board:

1. Enable "Custom Board" syscfg option.
2. Write a board-specific C file containing:
   - `const EnetPhy_DrvInfoTbl gEnetPhyDrvTbl` - table of ENET PHY drivers supported on the board.
   - `EnetBoard_setupPorts()` - setup board level muxes and SoC level RGMII/RMII configuration.
   - `EnetBoard_getPhyCfg()` - return ETHPHY specific configuration for a given port.
   - `EnetBoard_getMacAddrList()` - populate board specific MAC addresses from board EEPROM.
   - `EnetBoard_getId()` - return the board id.

### Ethernet MAC Address Management

There are two ways to set a custom MAC address:

**1. Using Syscfg GUI tool:** Go to "TI" -> "ENET(CPSW)" -> "System integration config". Change "MAC Address Assignment Method" to "Manual Entry" and fill the MAC address in "MAC Address List" option.

**2. Using Custom Board Option:** In the board specific `.c` file, implement `EnetBoard_getMacAddrList()`:

```c
void EnetBoard_getMacAddrList(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                             uint32_t maxMacEntries,
                             uint32_t *pAvailMacEntries)
{
    uint32_t macAddrCnt;
    uint32_t i;
    uint8_t macAddrBuf[ENET_BOARD_NUM_MACADDR_MAX * ENET_MAC_ADDR_LEN];
    uint8_t numMacMax = 0;

    macAddrBuf[ENET_MAC_ADDR_LEN*0] = {0xF4, 0x84, 0x4C, 0xFB, 0xC0, 0x5C};
    macAddrBuf[ENET_MAC_ADDR_LEN*1] = {0xF4, 0x84, 0x4C, 0xFB, 0xC0, 0x5D};
    numMacMax = 2;
    macAddrCnt = EnetUtils_min(numMacMax, maxMacEntries);
    EnetAppUtils_assert(pAvailMacEntries != NULL);
    for (i = 0U; i < macAddrCnt; i++)
    {
        memcpy(macAddr[i], &macAddrBuf[i * ENET_MAC_ADDR_LEN], ENET_MAC_ADDR_LEN);
    }
    *pAvailMacEntries = macAddrCnt;
}
```

## External PHY Management

External PHY management allows application plugging in its own PHY state machine and managing PHY drivers outside of Enet LLD.

- PHY control and PHY statemachine handling is disabled in Ethernet driver.
- MDIO is still owned by Ethernet Driver and MDIO IOCTLs should be used to access the PHYs.
- Enable via syscfg "External PHY Management" option.
- Application should register for MDIO link event interrupt if MDIO manual mode is not enabled.
- Application should invoke below IOCTLs to inform Enet driver of link up/down events:
  - `ENET_PER_IOCTL_HANDLE_EXTPHY_LINKUP_EVENT`
  - `ENET_PER_IOCTL_HANDLE_EXTPHY_LINKDOWN_EVENT`

## Tuning Memory Usage for Non-LwIP Apps

Key params that are useful for tuning the rw data memory:
- Maximum number of packets for Tx and Rx DMA channel (configurable via syscfg).
- For non-lwip application, the enet library packet pool allocation can be enabled via syscfg to configure the size of large, medium and small pools and the number of packets in each pool.

## Tuning Memory Usage for LwIP Apps

- Set maximum number of packets for Tx and Rx DMA channel (configurable via syscfg).
- Update `mcu_plus_sdk/source/networking/lwip/lwip-config/<soc>/lwippools.h` as per application requirement.
- Update `mcu_plus_sdk/source/networking/lwip/lwip-config/<soc>/lwipopts.h`:
  - `PBUF_POOL_SIZE` - determines number of Rx packets. The Rx DMA channel max number of packets should be updated if this value is modified.
- **Changes to lwipopts.h and lwippools require recompilation of library.**
