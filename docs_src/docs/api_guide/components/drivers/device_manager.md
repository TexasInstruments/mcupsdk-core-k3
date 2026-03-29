# DEVICE MANAGER {#DRIVERS_DEVICE_MANAGER_PAGE}

[TOC]

AM62 devices fall under the K3 SoC family and employ the concept of centralized management for Power, Resources, and Security, to mitigate the challenges of traditional system control approaches. System Firmware (hereafter referred to as SYSFW) is the collective name for the TI Foundational Security (TIFS) and Device Management firmware (DM firmware). In this concept, a processing unit (an M4F for example) can request the DM firmware to control power, grant resources, or provide secure services. This is done via a special messaging channel called **secure proxy**, where all messages follow a proprietary protocol called TISCI (TI System Controller Interface). For more information on the TISCI protocol, refer to the \htmllink{https://software-dl.ti.com/tisci/esd/latest/index.html, **TISCI Public Documentation**}.

The Wake-Up (WKUP) R5 core or the DM R5 core is responsible for running the DM firmware, which is responsible for resource management and power management.

DM firmware is a culmination of the following components:
  - "rm_pm_hal_src" processes resource and power management calls.
  - "sciserver" processes TISCI messages from other cores.
  - "sciclient_direct" calls rm_pm_hal or forwards messages to TIFS depending on the TISCI request.
  - "self_reset" contains the entry point for the DM firmware application. It resets the DM R5 and enables the TCMA.
  - "dm_stub" enables low power mode features.

\attention
- Since WKUP R5 is the Device Manager, it cannot be loaded via CCS because it needs to be started by the Secondary Bootloader (SBL).
- During DM firmware's initialization, the self_reset library swaps the TCM configuration to place ATCM to 0x41010000 and BTCM to 0x0.

## Features Supported

- Process Power Management (PM) and Resource Management (RM) messages and forwards to TIFS if required.
- Enters and exits Low Power Modes (LPM).

## SysConfig Features

- There are no user programmable features for Device Manager SysConfig

## Enabling Interrupt Mode {#ENABLE_INTERRUPT_MODE}

DM, specifically Sciclient Direct, can be run in Polling Mode (Default) as well as Interrupt Mode. For each PM or RM messages that DM processes, it checks whether further processing by TIFS is required. If it is required then DM forwards such messages to TIFS and keep polling for the response from TIFS. Instead of polling, DM can check for the response using interrupts. To switch the mode to Interrupt Mode, follow the steps below -

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62DX
  - Add the line '-DCONFIG_DM2TIFS_INTERRUPT_MODE \' to 'DEFINES_common' in source/drivers/device_manager/sciserver/makefile.`@VAR_SOC_NAME_LOWER`.r5f.ti-arm-clang.
\endcond
\cond SOC_AM62PX || SOC_J722S
  - Add the line '-DCONFIG_DM2TIFS_INTERRUPT_MODE \' to 'DEFINES_common' in source/drivers/device_manager/sciserver/makefile.`@VAR_SOC_NAME_LOWER`.wkup-r5f.ti-arm-clang.
\endcond
  - Rebuild the libraries and application.

## Registering Suspend and Resume Hook for Low Power Mode {#REGISTER_SUSPEND_RESUME_HOOK_LPM}

During low power mode, the DM R5 will suspend its sciclient services, stop the scheduler, turn off the main domain and go to WFI for power saving. If the application that is running along with DM requires something to be saved before going to low power mode and needs to be restored during resume, it can use the *Sciclient_initLPMSusResHook* function to register suspend and resume hooks. One suspend hook and one resume hook can be passed to this function. These hooks will get invoked during low power mode entry and exit.

## Disabling Low Power Mode {#DISABLE_LPM}

During low power mode, DDR is kept in self refresh, which means DM R5 cannot run from DDR. As a result, DM R5 run from the TCM memory instead. However, if users want to use the TCM memory for a user application, low power mode can be disabled, and then the TCM memory will be available for the user application. To do so, follow the steps below:

  - Update the  line '-CONFIG_LPM_DM=y' in  source/drivers/device_manager/rm_pm_hal/BuildConfiguration`@VAR_SOC_NAME`.mk to '-CONFIG_LPM_DM=n'.
\cond SOC_AM62X || SOC_AM62AX || SOC_AM62DX || SOC_AM275X
  - Remove the  line '-DCONFIG_LPM_DM \' from  source/drivers/device_manager/sciclient_direct/makefile.`@VAR_SOC_NAME_LOWER`.r5f.ti-arm-clang'.
  - Remove the  line '-DCONFIG_LPM_DM \' from  source/drivers/device_manager/sciserver/makefile.`@VAR_SOC_NAME_LOWER`.r5f.ti-arm-clang.
  - Remove the  line '-DCONFIG_LPM_DM \' from  source/drivers/device_manager/self_reset/makefile.`@VAR_SOC_NAME_LOWER`.r5f.ti-arm-clang.
\endcond
\cond SOC_AM62PX
  - Remove the  line '-DCONFIG_LPM_DM \' from  source/drivers/device_manager/sciclient_direct/makefile.`@VAR_SOC_NAME_LOWER`.wkup-r5f.ti-arm-clang'.
  - Remove the  line '-DCONFIG_LPM_DM \' from  source/drivers/device_manager/sciserver/makefile.`@VAR_SOC_NAME_LOWER`.wkup-r5f.ti-arm-clang.
  - Remove the  line '-DCONFIG_LPM_DM \' from  source/drivers/device_manager/self_reset/makefile.`@VAR_SOC_NAME_LOWER`.wkup-r5f.ti-arm-clang.
\endcond
  - Remove the following lines from the linker file of the application that you are building.

          GROUP{
                .dm_stub_text : {
                    _privileged_code_begin = .;
                    _text_secure_start = .;
                    dm_stub*(.text)
                }  palign(8)

                .dm_stub_data : {
                    _privileged_data_begin = .;
                    dm_stub*(.data)
                    _privileged_data_end = .;
                }  palign(8)

                .dm_stub_bss : {
                    _start_bss = .;
                    dm_stub*(.bss)
                    _end_bss = .;
                }  palign(8)

                .dm_stub_rodata : {
                    _start_rodata = .;
                    dm_stub*(.rodata)
                    _end_rodata = .;
                }  palign(8)

            .dm_stub_stack : {
                    _start_stack = .;
                    . += __DM_STUB_STACK_SIZE;
                    _end_stack = .;
                }  palign(8)
            }  load = R5F_TCMB, run = R5F_TCMA
  - Rebuild the application.

\cond SOC_AM62AX
## Migration Guide 11.01 to 11.02 - AM62A {#SCISERVER_11_2_MIGRATION}

\note This section highlights API changes from 11.01 to 11.02 SDK for AM62A.

### Task stack allocation moved to application layer

- `sciServer_init` parameter changed from `void` to `Sciserver_TirtosCfgPrms_t *sciserverCfg`.
- `Sciserver_TirtosCfgPrms_t` gained three new required fields: `hiTaskStack`, `loTaskStack`, and `taskStackSize`.
- Allocate task stack buffers in the application as **global arrays** and populate these fields before calling `sciServer_init`.
- \attention Stack buffers must be declared as global variables. Declaring them on the stack (as local variables) will result in undefined behavior once the declaring function returns.

Old usage:
\code{.c}
sciServer_init();
\endcode

New usage:
\code{.c}
#define SCISERVER_TASK_STACK_SIZE      (2U * 1024U)
#define SCISERVER_TASK_STACK_ALIGNMENT (32)

uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserHiTaskStack[SCISERVER_TASK_STACK_SIZE];
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserLoTaskStack[SCISERVER_TASK_STACK_SIZE];

/* In your init function */
Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
sciserverCfg.hiTaskStack   = gUserHiTaskStack;
sciserverCfg.loTaskStack   = gUserLoTaskStack;
sciserverCfg.taskStackSize = SCISERVER_TASK_STACK_SIZE;
sciServer_init(&sciserverCfg);
\endcode
\endcond

\cond SOC_AM62X || SOC_AM62DX || SOC_AM62PX || SOC_AM275X
## Migration Guide 11.02 to 12.00 {#SCISERVER_12_0_MIGRATION}

\note This section highlights API changes from 11.02 to 12.00 SDK.

### Task stack allocation moved to application layer

- `sciServer_init` parameter changed from `void` to `Sciserver_TirtosCfgPrms_t *sciserverCfg`.
- `Sciserver_TirtosCfgPrms_t` gained three new required fields: `hiTaskStack`, `loTaskStack`, and `taskStackSize`.
- Allocate task stack buffers in the application as **global arrays** and populate these fields before calling `sciServer_init`.
- \attention Stack buffers must be declared as global variables. Declaring them on the stack (as local variables) will result in undefined behavior once the declaring function returns.

Old usage:
\code{.c}
sciServer_init();
\endcode

New usage:
\code{.c}
#define SCISERVER_TASK_STACK_SIZE      (2U * 1024U)
#define SCISERVER_TASK_STACK_ALIGNMENT (32)

uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserHiTaskStack[SCISERVER_TASK_STACK_SIZE];
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserLoTaskStack[SCISERVER_TASK_STACK_SIZE];

/* In your init function */
Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
sciserverCfg.hiTaskStack   = gUserHiTaskStack;
sciserverCfg.loTaskStack   = gUserLoTaskStack;
sciserverCfg.taskStackSize = SCISERVER_TASK_STACK_SIZE;
sciServer_init(&sciserverCfg);
\endcode
\endcond
