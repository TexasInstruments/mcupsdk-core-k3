# SCICLIENT Migration Guide {#SCICLIENT_MIGRATION_GUIDE}

This section describes the differences between SCICLIENT APIs of MCU+SDK and Processor SDK RTOS (PDK).
This can be used as a migration aid when moving from Processor SDK RTOS (PDK) to MCU+SDK.


## API changes

None

## Changes in Directory structure

- The location of Sciclient service for DM core is changed in MCU+SDK.
<table>
    <tr>
        <th>
        <th> DM Core
        <th> Non-DM Cores
        <th> Remarks
    </tr>
    <tr>
        <td> PDK
        <td> Sciclient services available in the PDK repository under <(PDK_PATH)/ti/drv/sciclient> directory.
        <td> Sciclient services available in the PDK repository under <(PDK_PATH)/ti/drv/sciclient> directory.
        <td> All cores have same location for Sciclient services.
    </tr>
    <tr>
        <td> MCU+SDK
        <td> Sciclient services available in the Device_Manager repository under <(MCU_PLUS_SDK_PATH)/source/drivers/device_manager/sciclient_direct> directory.
        <td> Sciclient services available in the MCU+SDK repository under <(MCU_PLUS_SDK_PATH)/source/drivers/sciclient> directory.
        <td> Different locations for Sciclient services.
    </tr>
</table>

Refer \ref DRIVERS_SCICLIENT_PAGE for more details.

