Low Power Mode Wakeup
=======================

.. toctree::
   :maxdepth: 1
   :hidden:
   :titlesonly:

   lpm/lpm_mcu_mcan_wakeup
   lpm/lpm_mcu_uart_wakeup
   lpm/lpm_mcu_dmtimer_wakeup
   lpm/lpm_io_retention_uart_wakeup
   lpm/lpm_io_retention_mcan_wakeup

.. only:: SOC_AM62PX or SOC_AM62X or SOC_AM62AX

   This page lists all the examples related to usage of MCU IPs for waking up the SoC from MCU Only Low Power Mode.

   **MCAN**
      - :doc:`LPM MCU MCAN Wakeup <lpm/lpm_mcu_mcan_wakeup>`

   **UART**
      - :doc:`LPM UART Wakeup <lpm/lpm_mcu_uart_wakeup>`

   **DM-Timer**
      - :doc:`LPM DMTimer Wakeup <lpm/lpm_mcu_dmtimer_wakeup>`

.. only:: SOC_AM275X

   This page lists the example on how to enter IO Retention / Partial IO low power mode on console key press and then wakeup on pin activity on MCAN pins.

   **MCAN**
      - :doc:`LPM Suspend to IO Retention mode and Wakeup on CAN pin activity <lpm/lpm_io_retention_mcan_wakeup>`

.. only:: SOC_AM62DX

   This page lists the example on how to enter IO Retention / Partial IO low power mode on console key press and then wakeup on pin activity on MCU UART pins.

   **MCU UART**
      - :doc:`LPM Suspend to IO Retention mode and Wakeup on UART pin activity <lpm/lpm_io_retention_uart_wakeup>`
