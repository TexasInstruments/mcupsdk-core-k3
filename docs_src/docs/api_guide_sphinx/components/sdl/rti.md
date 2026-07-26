# RTI
The Windowed Watchdog Timer (WWDT) generates reset after a programmable period, if not serviced within that period. This time-out boundary is configurable, and the windowed feature allows the start time boundary to be configurable.
The WWDT can generate an Interrupt, if not serviced within window (Open Window) defined by start time and time-out boundary. Also the WWDT can generate an Interrupt if serviced outside Open Window (within Closed Window).
Generation of Interrupt depends on the WWDT Reaction configuration. SDL supports configuration of the watchdog timers. It also supports notification of the error via ESM interrupt. Additionally, APIs for checking the status of the watchdog timer is provided.

## Features Supported

The module provides the following functionality
- Ability to to initialize the RTI -DWWD module
- Ability to configure RTI -DWWD module
- Ability to service an RTI instance
- Ability to read Status of the configuration
- Ability to read back static register


:::{only} SOC_AM62X or SOC_AM62PX
   There are 7 RTI Modules in the device – 1 in the MCU domain and 5 in the Main domain and 1 in wkup domain.

   Instances in MCU domain:
   1)	MCU_RTI0

   Instances in Main domain:
   1)	RTI0
   2)	RTI1
   3)	RTI2
   4)	RTI3
   5)	RTI15

   Instances in WKUP domain:
   1)	WKUP_RTI0
:::


:::{only} SOC_AM62AX or SOC_AM62DX
   There are 7 RTI Modules in the device – 1 in the MCU domain and 5 in the Main domain and 1 in wakup domain.

   Instances in MCU domain:
   1)	MCU_RTI0

   Instances in Main domain:
   1)	RTI0
   2)	RTI1
   3)	RTI2
   4)	RTI3
   5)	RTI4

   Instances in WKUP domain:
   1)	WKUP_RTI0
:::


:::{only} SOC_AM275X
   There are 7 RTI Modules in the device – 6 in the Main domain and 1 in wkup domain.

   Instances in Main domain:
   1)	RTI0
   2)	RTI1
   3)	RTI2
   4)	RTI3
   5)	RTI4
   6)  RTI5

   Instances in WKUP domain:
   1)	WKUP_RTI0
:::


## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage
The following shows an example of SDL RTI API.

Include the below file to access the APIs

```
#include <sdl/sdl_rti.h>
```
:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   Config an RTI Instance
      SDL_RTI_configParms pConfig;

   /* Configure RTI parameters for preload, window and reaction*/
   pConfig.SDL_RTI_dwwdPreloadVal = RTIGetPreloadValue(RTI_CLOCK_SOURCE_200KHZ, RTI_WDT_TIMEOUT);
   pConfig.SDL_RTI_dwwdWindowSize = RTI_DWWD_WINDOWSIZE_100_PERCENT;
   pConfig.SDL_RTI_dwwdReaction   = RTI_DWWD_REACTION_GENERATE_NMI;

   #if defined (M4F_CORE)
   retVal = SDL_RTI_config(SDL_INSTANCE_MCU_RTI0_CFG, &pConfig);
   #endif
   #if defined (R5F_CORE)
   retVal = SDL_RTI_config(SDL_INSTANCE_WKUP_RTI0, &pConfig);
   #endif

   if (retVal == SDL_EFAIL)
   {
       UART_printf("Error during Window configuration.\n");
   }
   
   Verify the config
      /* Verify the config */
   #if defined (M4F_CORE)
   retVal = SDL_RTI_verifyConfig(SDL_INSTANCE_MCU_RTI0_CFG, &pConfig);
   #endif
   #if defined (R5F_CORE)
   retVal = SDL_RTI_verifyConfig(SDL_INSTANCE_WKUP_RTI0, &pConfig);
   #endif

   if (retVal == SDL_EFAIL)
   {
       UART_printf("Error during Window Verify configuration.\n");
   }
   
   Read the static registers
      SDL_RTI_staticRegs pStaticRegs;

   #if defined (M4F_CORE)
   retVal = SDL_RTI_readStaticRegs(SDL_INSTANCE_MCU_RTI0_CFG, &pStaticRegs);
   #endif
   #if defined (R5F_CORE)
   retVal = SDL_RTI_readStaticRegs(SDL_INSTANCE_WKUP_RTI0, &pStaticRegs);
   #endif
   
   Start an RTI Instance
      #if defined (M4F_CORE)
   SDL_RTI_start(SDL_INSTANCE_MCU_RTI0_CFG);
   #endif
   #if defined (R5F_CORE)
   SDL_RTI_start(SDL_INSTANCE_WKUP_RTI0);
   #endif
   
   Start an RTI Instance
      /* Servicing of the watchdog is done by the core that is being monitored with the watchdg */
   #if defined (M4F_CORE)
   SDL_RTI_service(SDL_INSTANCE_MCU_RTI0_CFG);
   #endif
   #if defined (R5F_CORE)
   SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
   #endif
   
:::


:::{only} SOC_AM275X
   Config an RTI Instance
      SDL_RTI_configParms pConfig;

   /* Configure RTI parameters for preload, window and reaction*/
   pConfig.SDL_RTI_dwwdPreloadVal = RTIGetPreloadValue(RTI_CLOCK_SOURCE_200KHZ, RTI_WDT_TIMEOUT);
   pConfig.SDL_RTI_dwwdWindowSize = RTI_DWWD_WINDOWSIZE_100_PERCENT;
   pConfig.SDL_RTI_dwwdReaction   = RTI_DWWD_REACTION_GENERATE_NMI;

   retVal = SDL_RTI_config(SDL_INSTANCE_WKUP_RTI0, &pConfig);

   if (retVal == SDL_EFAIL)
   {
       UART_printf("Error during Window configuration.\n");
   }
   
   Verify the config
      /* Verify the config */
   retVal = SDL_RTI_verifyConfig(SDL_INSTANCE_WKUP_RTI0, &pConfig);

   if (retVal == SDL_EFAIL)
   {
       UART_printf("Error during Window Verify configuration.\n");
   }
   
   Read the static registers
      SDL_RTI_staticRegs pStaticRegs;

   retVal = SDL_RTI_readStaticRegs(SDL_INSTANCE_WKUP_RTI0, &pStaticRegs);
   
   Start an RTI Instance
      SDL_RTI_start(SDL_INSTANCE_WKUP_RTI0);
   
   Start an RTI Instance
      /* Servicing of the watchdog is done by the core that is being monitored with the watchdg */
   SDL_RTI_service(SDL_INSTANCE_WKUP_RTI0);
   
:::




## API Reference

```{doxygenfile} sdl/rti/v0/sdl_rti.h
```
