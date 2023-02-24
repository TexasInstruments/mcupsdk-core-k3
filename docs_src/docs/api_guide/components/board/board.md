# Board Peripheral Drivers {#BOARD_DRIVERS_PAGE}

[TOC]

This module has information related to the different board level peripherals that are supported

It consists of below sub-modules

\cond SOC_AM64X || SOC_AM243X || SOC_AM263X
- \subpage BOARD_ETHPHY_PAGE
\endcond
- \subpage BOARD_FLASH_PAGE
\cond !SOC_AM62X && !SOC_AM62AX
- \subpage BOARD_EEPROM_PAGE
\endcond
- \subpage BOARD_LED_PAGE