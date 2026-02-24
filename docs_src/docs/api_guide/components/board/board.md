# Board Peripheral Drivers {#BOARD_DRIVERS_PAGE}

[TOC]

This module has information related to the different board level peripherals that are supported

It consists of below sub-modules

\cond SOC_AM64X || SOC_AM243X || SOC_AM263X
- \subpage BOARD_ETHPHY_PAGE
\endcond
- \subpage BOARD_FLASH_PAGE
\cond !SOC_AM62X && !SOC_AM62LX
- \subpage BOARD_EEPROM_PAGE
\endcond
- \subpage BOARD_LED_PAGE
\cond SOC_AM62PX
- \subpage BOARD_PANEL_PAGE
- \subpage BOARD_PMIC_PAGE
\endcond
\cond SOC_AM62DX
- \subpage BOARD_PMIC_PAGE
\endcond
\cond SOC_AM62X || SOC_AM62LX
- \subpage BOARD_PANEL_PAGE
\endcond
\cond SOC_AM275X
- \subpage BOARD_HYPERRAM_PAGE
\endcond