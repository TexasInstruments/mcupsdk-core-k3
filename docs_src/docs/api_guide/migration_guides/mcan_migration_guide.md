# MCAN Migration Guide {#MCAN_MIGRATION_GUIDE}

This section describes the differences between MCAN APIs of MCU+ SDK and Processor SDK RTOS (PDK).
This can be used as a migration aid when moving from Processor SDK RTOS (PDK) to MCU+ SDK.

There is no difference in the driver APIs provided by MCAN module in PDK and MCU+SDK. Refer \ref DRIVERS_MCAN_PAGE for more details.

## API changes

There are no changes in the functions names, structure names or macro names. The MCAN APIs are listed below.

<table>
    <tr>
        <th> PDK
        <th> MCU+ SDK
        <th> Change Description / Remarks
    </tr>
    <tr>
        <td>MCAN_reset
        <td>\ref MCAN_reset
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_isInReset
        <td>\ref MCAN_isInReset
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_isFDOpEnable
        <td>\ref MCAN_isFDOpEnable
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_isMemInitDone
        <td>\ref MCAN_isMemInitDone
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_setOpMode
        <td>\ref MCAN_setOpMode
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getOpMode
        <td>\ref MCAN_getOpMode
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_init
        <td>\ref MCAN_init
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_config
        <td>\ref MCAN_config
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccConfig
        <td>\ref MCAN_eccConfig
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_setBitTime
        <td>\ref MCAN_setBitTime
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_msgRAMConfig
        <td>\ref MCAN_msgRAMConfig
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_setExtIDAndMask
        <td>\ref MCAN_setExtIDAndMask
        <td>NO CHANGE
    </tr>
        <tr>
        <td>MCAN_writeMsgRam
        <td>\ref MCAN_writeMsgRam
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_writeMsgRamNoCpy
        <td>\ref MCAN_writeMsgRamNoCpy
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_txBufAddReq
        <td>\ref MCAN_txBufAddReq
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getNewDataStatus
        <td>\ref MCAN_getNewDataStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_clearNewDataStatus
        <td>\ref MCAN_clearNewDataStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_readMsgRam
        <td>\ref MCAN_readMsgRam
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_readMsgRamNoCpy
        <td>\ref MCAN_readMsgRamNoCpy
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_readTxEventFIFO
        <td>\ref MCAN_readTxEventFIFO
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_addStdMsgIDFilter
        <td>\ref MCAN_addStdMsgIDFilter
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_addExtMsgIDFilter
        <td>\ref MCAN_addExtMsgIDFilter
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_lpbkModeEnable
        <td>\ref MCAN_lpbkModeEnable
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getErrCounters
        <td>\ref MCAN_getErrCounters
        <td>NO CHANGE
    </tr>
        <tr>
        <td>MCAN_getProtocolStatus
        <td>\ref MCAN_getProtocolStatus
        <td>NO CHANGE
    </tr>
        <tr>
        <td>MCAN_enableIntr
        <td>\ref MCAN_enableIntr
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_selectIntrLine
        <td>\ref MCAN_selectIntrLine
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getIntrLineSelectStatus
        <td>\ref MCAN_getIntrLineSelectStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_enableIntrLine
        <td>\ref MCAN_enableIntrLine
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getIntrStatus
        <td>\ref MCAN_getIntrStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_clearIntrStatus
        <td>\ref MCAN_clearIntrStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getHighPriorityMsgStatus
        <td>\ref MCAN_getHighPriorityMsgStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getRxFIFOStatus
        <td>\ref MCAN_getRxFIFOStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_writeRxFIFOAck
        <td>\ref MCAN_writeRxFIFOAck
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getTxFIFOQueStatus
        <td>\ref MCAN_getTxFIFOQueStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getTxBufReqPend
        <td>\ref MCAN_getTxBufReqPend
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_txBufCancellationReq
        <td>\ref MCAN_txBufCancellationReq
        <td>NO CHANGE
    </tr>
        <tr>
        <td>MCAN_getTxBufTransmissionStatus
        <td>\ref MCAN_getTxBufTransmissionStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_txBufCancellationStatus
        <td>\ref MCAN_txBufCancellationStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_txBufTransIntrEnable
        <td>\ref MCAN_txBufTransIntrEnable
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getTxBufCancellationIntrEnable
        <td>\ref MCAN_txBufCancellationIntrEnable
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_addClockStopRequest
        <td>\ref MCAN_addClockStopRequest
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_getTxEventFIFOStatus
        <td>\ref MCAN_getTxEventFIFOStatus
        <td>NO CHANGE
    </tr>
        <tr>
        <td>MCAN_writeTxEventFIFOAck
        <td>\ref MCAN_writeTxEventFIFOAck
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccForceError
        <td>\ref MCAN_eccForceError
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccGetErrorStatus
        <td>\ref MCAN_eccGetErrorStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccClearErrorStatus
        <td>\ref MCAN_eccClearErrorStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccWriteEOI
        <td>\ref MCAN_eccWriteEOI
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccEnableIntr
        <td>\ref MCAN_eccEnableIntr
        <td>NO CHANGE
    </tr>
        <tr>
        <td>MCAN_eccGetIntrStatus
        <td>\ref MCAN_eccGetIntrStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_eccClearIntrStatus
        <td>\ref MCAN_eccClearIntrStatus
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_extTSCounterConfig
        <td>\ref MCAN_extTSCounterConfig
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_extTSCounterEnable
        <td>\ref MCAN_extTSCounterEnable
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_extTSEnableIntr
        <td>\ref MCAN_extTSEnableIntr
        <td>NO CHANGE
    </tr>
    <tr>
        <td>MCAN_extTSWriteEOI
        <td>\ref MCAN_extTSWriteEOI
        <td>NO CHANGE
    </tr>
      <tr>
        <td>MCAN_extTSGetUnservicedIntrCount
        <td>\ref MCAN_extTSGetUnservicedIntrCount
        <td>NO CHANGE
    </tr>
</table>

## Important Notes

- In MCU+ SDK, Users are recommended to use SysConfig to configure driver parameters as this will greatly simplify the task of driver configuration.

## See Also

 - \ref DRIVERS_MCAN_PAGE
 - \ref EXAMPLES_DRIVERS_MCAN_LOOPBACK_INTERRUPT
 - \ref EXAMPLES_DRIVERS_MCAN_LOOPBACK_POLLING
