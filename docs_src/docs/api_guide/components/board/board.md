# Board Peripheral Drivers {#BOARD_DRIVERS_PAGE}

[TOC]

This module has information related to the different board level peripherals that are supported

It consists of below sub-modules

\cond SOC_AM64X || SOC_AM243X || SOC_AM263X
- \subpage BOARD_ETHPHY_PAGE
\endcond
- \subpage BOARD_FLASH_PAGE
\cond !SOC_AM62X
- \subpage BOARD_EEPROM_PAGE
\endcond
- \subpage BOARD_LED_PAGE
\cond SOC_AM62PX
- \subpage BOARD_PMIC_PAGE
\endcond