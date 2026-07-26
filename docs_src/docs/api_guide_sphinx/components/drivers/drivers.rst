SOC Peripheral Drivers
=========================

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   AASRC <aasrc>
   adc
   BOOTLOADER <bootloader>
   DDR <ddr>
   DEVICE MANAGER <device_manager>
   DSS <dss>
   ECAP <ecap>
   EPWM <epwm>
   eqep
   FVID2 <fvid2>
   GPIO <gpio>
   GPMC <gpmc>
   gtc
   hyperbus
   I2C <i2c>
   IPC Notify <ipc_notify>
   IPC RPMessage <ipc_rpmsg>
   MCAN <mcan>
   MCASP <mcasp_v1>
   MCSPI <mcspi>
   MMCSD <mmcsd>
   OSPI <ospi>
   PINMUX <pinmux>
   PMU <pmu>
   QoS <qos>
   RTC <rtc>
   SCICLIENT <sciclient>
   spinlock
   UART <uart>
   UDMA <udma>
   WATCHDOG <watchdog>

This module contains APIs for different device drivers for peripherals on the SOC that are supported on |VAR_SOC_NAME|.

It consists of below sub-modules

.. only:: SOC_AM62X

   - :doc:`BOOTLOADER <bootloader>`
   - :doc:`DDR <ddr>`
   - :doc:`DEVICE MANAGER <device_manager>`
   - :doc:`DSS <dss>`
   - :doc:`ECAP <ecap>`
   - :doc:`EPWM <epwm>`
   - :doc:`EQEP <eqep>`
   - :doc:`FVID2 <fvid2>`
   - :doc:`GPIO <gpio>`
   - :doc:`GPMC <gpmc>`
   - :doc:`I2C <i2c>`
   - :doc:`IPC Notify <ipc_notify>`
   - :doc:`IPC RPMessage <ipc_rpmsg>`
   - :doc:`MCAN <mcan>`
   - :doc:`MCASP <mcasp_v1>`
   - :doc:`MCSPI <mcspi>`
   - :doc:`MMCSD <mmcsd>`
   - :doc:`OSPI <ospi>`
   - :doc:`PINMUX <pinmux>`
   - :doc:`PMU <pmu>`
   - :doc:`QoS <qos>`
   - :doc:`RTC <rtc>`
   - :doc:`SCICLIENT <sciclient>`
   - :doc:`UART <uart>`
   - :doc:`UDMA <udma>`
   - :doc:`WATCHDOG <watchdog>`

.. only:: SOC_AM62AX

   - :doc:`BOOTLOADER <bootloader>`
   - :doc:`DDR <ddr>`
   - :doc:`DEVICE MANAGER <device_manager>`
   - :doc:`ECAP <ecap>`
   - :doc:`EPWM <epwm>`
   - :doc:`EQEP <eqep>`
   - :doc:`GPIO <gpio>`
   - :doc:`GTC <gtc>`
   - :doc:`I2C <i2c>`
   - :doc:`IPC Notify <ipc_notify>`
   - :doc:`IPC RPMessage <ipc_rpmsg>`
   - :doc:`MCAN <mcan>`
   - :doc:`MCASP <mcasp_v1>`
   - :doc:`MCSPI <mcspi>`
   - :doc:`MMCSD <mmcsd>`
   - :doc:`OSPI <ospi>`
   - :doc:`PINMUX <pinmux>`
   - :doc:`PMU <pmu>`
   - :doc:`QoS <qos>`
   - :doc:`RTC <rtc>`
   - :doc:`SCICLIENT <sciclient>`
   - :doc:`UART <uart>`
   - :doc:`UDMA <udma>`
   - :doc:`WATCHDOG <watchdog>`

.. only:: SOC_AM62DX

   - :doc:`BOOTLOADER <bootloader>`
   - :doc:`DDR <ddr>`
   - :doc:`DEVICE MANAGER <device_manager>`
   - :doc:`ECAP <ecap>`
   - :doc:`EPWM <epwm>`
   - :doc:`EQEP <eqep>`
   - :doc:`GPIO <gpio>`
   - :doc:`GTC <gtc>`
   - :doc:`I2C <i2c>`
   - :doc:`IPC Notify <ipc_notify>`
   - :doc:`IPC RPMessage <ipc_rpmsg>`
   - :doc:`MCAN <mcan>`
   - :doc:`MCASP <mcasp_v1>`
   - :doc:`MCSPI <mcspi>`
   - :doc:`MMCSD <mmcsd>`
   - :doc:`OSPI <ospi>`
   - :doc:`PMU <pmu>`
   - :doc:`RTC <rtc>`
   - :doc:`SCICLIENT <sciclient>`
   - :doc:`SOC <../../device/am62dx/soc>`
   - :doc:`UART <uart>`
   - :doc:`UDMA <udma>`
   - :doc:`WATCHDOG <watchdog>`

.. only:: SOC_AM62PX

   - :doc:`BOOTLOADER <bootloader>`
   - :doc:`DDR <ddr>`
   - :doc:`DSS <dss>`
   - :doc:`DEVICE MANAGER <device_manager>`
   - :doc:`ECAP <ecap>`
   - :doc:`EPWM <epwm>`
   - :doc:`FVID2 <fvid2>`
   - :doc:`GPIO <gpio>`
   - :doc:`I2C <i2c>`
   - :doc:`IPC Notify <ipc_notify>`
   - :doc:`IPC RPMessage <ipc_rpmsg>`
   - :doc:`MCAN <mcan>`
   - :doc:`MCASP <mcasp_v1>`
   - :doc:`MCSPI <mcspi>`
   - :doc:`MMCSD <mmcsd>`
   - :doc:`OSPI <ospi>`
   - :doc:`PINMUX <pinmux>`
   - :doc:`PMU <pmu>`
   - :doc:`QoS <qos>`
   - :doc:`RTC <rtc>`
   - :doc:`SCICLIENT <sciclient>`
   - :doc:`SOC <../../device/am62px/soc>`
   - :doc:`UART <uart>`
   - :doc:`UDMA <udma>`
   - :doc:`WATCHDOG <watchdog>`

.. only:: SOC_AM275X

   - :doc:`AASRC <aasrc>`
   - :doc:`ADC <adc>`
   - :doc:`BOOTLOADER <bootloader>`
   - :doc:`DEVICE MANAGER <device_manager>`
   - :doc:`ECAP <ecap>`
   - :doc:`EPWM <epwm>`
   - :doc:`GPIO <gpio>`
   - :doc:`GTC <gtc>`
   - :doc:`HYPERBUS <hyperbus>`
   - :doc:`I2C <i2c>`
   - :doc:`IPC Notify <ipc_notify>`
   - :doc:`IPC RPMessage <ipc_rpmsg>`
   - :doc:`MCAN <mcan>`
   - :doc:`MCASP <mcasp_v1>`
   - :doc:`MCSPI <mcspi>`
   - :doc:`MMCSD <mmcsd>`
   - :doc:`OSPI <ospi>`
   - :doc:`PINMUX <pinmux>`
   - :doc:`PMU <pmu>`
   - :doc:`QoS <qos>`
   - :doc:`RTC <rtc>`
   - :doc:`SCICLIENT <sciclient>`
   - :doc:`SPINLOCK <spinlock>`
   - :doc:`UART <uart>`
   - :doc:`UDMA <udma>`
   - :doc:`WATCHDOG <watchdog>`

.. only:: SOC_AM62LX

   - :doc:`ADC <adc>`
   - :doc:`DSS <dss>`
   - :doc:`ECAP <ecap>`
   - :doc:`EPWM <epwm>`
   - :doc:`EQEP <eqep>`
   - :doc:`FVID2 <fvid2>`
   - :doc:`GPIO <gpio>`
   - :doc:`I2C <i2c>`
   - :doc:`MCAN <mcan>`
   - :doc:`MCASP <mcasp_v1>`
   - :doc:`MCSPI <mcspi>`
   - :doc:`MMCSD <mmcsd>`
   - :doc:`OSPI <ospi>`
   - :doc:`PINMUX <pinmux>`
   - :doc:`UART <uart>`
   - :doc:`UDMA <udma>`
   - :doc:`WATCHDOG <watchdog>`
