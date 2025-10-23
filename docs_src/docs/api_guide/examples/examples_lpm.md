# Low Power Mode Wakeup  {#EXAMPLES_LPM}

\cond  SOC_AM62X || SOC_AM62AX || SOC_AM62PX

This page lists all the examples related to usage of MCU IPs for
waking up the SoC from MCU Only Low Power Mode.

-# MCAN
   -# \subpage EXAMPLES_LPM_MCU_MCAN_WAKEUP
-# UART
   -# \subpage EXAMPLES_LPM_MCU_UART_WAKEUP
-# DM-Timer
   -# \subpage EXAMPLES_LPM_MCU_DMTIMER_WAKEUP
\endcond

\cond  SOC_AM275X

This page lists the example on how to enter IO Retention / Partial
IO low power mode on console key press and then wakeup on pin
activity on MCAN pins.
-# MCAN
   -# \subpage EXAMPLES_LPM_IO_RETENTION_MCAN_WAKEUP
\endcond