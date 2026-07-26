
# Debug
## Features Supported

- APIs to log strings to the selected console
- APIs to assert if a expression evaluates to 0
  - Before asserting, it will log the file and line number to console
- Ability to disable assert's and logging via a pre-processor define
- The following console options are supported
  - Log to CCS IDE console via JTAG
  - Log to UART terminal

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- Log to shared memory, can be viewed via the CPU on which log reader is enabled
- Log to CPU local memory, can be viewed via ROV in CCS or when Linux is enabled via Linux kernel debugfs
- Ability to read logs from shared memory and output to selected console.

::::

- SysCfg support for below,
  - SysCfg can be used to select the log console
  - When UART log is selected, SysCfg allows to select the UART instance and its properties (baud rate etc) to use.
  - SysCfg option to select UART for remote core trace when uart log is enabled. This enables the UART instance to be not closed as part of closing all drivers. Essentially used for Device Mangaer applications to enable Device Mangaer trace logs over UART.
  - SysCfg option to enable SysFw trace. When SysFw UART trace option is selected, SysCfg allows to select UART instance and its pinmuxing.
  - SysCfg option to enable shared memory reader task.
- APIs to read line as string and/or format input in scanf style from UART console.

## Features NOT Supported

- Log APIs should not be called from ISR context. When called in ISR the APIs have no effect.

## Important Usage Guidelines

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

### Shared memory logging
- The core on which the shared memory reader is enabled needs to run FreeRTOS since it needs task support.
- The core on which the shared memory reader is enabled, the option to use shared memory writer is ignored.
- When shared memory writer/reader is enabled, a shared memory section is used to write and read the strings for all the cores,
  - When SysCfg is used, the array representing this shared memory is generated in the file `ti_dpl_config.c`.
  - Place the section attributed to this array in the linker command file for each core such that all cores point to
    the same memory address for this section.
  - And this memory section should be marked as non-cache in the [MPU](MpuP_arm_v7.md)/[MMU](MmuP_arm_v8.md) entry for each core.
- It is recommended to enable UART logging and shared memory reader on one "main" core and other core's
  should enable the shared memory writer.
- The memory used for logging is limited per core. If the writer is faster than reader, then the writer drops the
  characters to be printed.
- To change the size of the log buffer, change the value of [DebugP_SHM_LOG_SIZE](../../../../../_api/group/group__KERNEL__DPL__DEBUG.html) in `source/kernel/dpl/DebugP.h`.

::::


### UART logging
- Make sure the selected UART driver is opened for the logs to be output to UART.
  - When enabled via SysCfg, calling the function `Drivers_open` opens and initializes the UART for logging.


:::{only} not SOC_AM62X and not SOC_AM62AX and not SOC_AM62DX and not SOC_AM62LX
   ### Memory logging
   - When log to memory is enabled, the log can be viewed via ROV (see [Using SDK with Runtime Object View (ROV)](../../../../../developer_guides/ccs_rov.md)) in CCS
   - The memory used for logging is limited. The writer is typically faster than the ROV reader, so here the writer will overwrite
     the older data, i.e the log will have the latest logs up to log buffer size.
   - To change the size of the log buffer, change the value of [DebugP_MEM_LOG_SIZE](../../../../../_api/group/group__KERNEL__DPL__DEBUG.html) in `source/kernel/dpl/DebugP.h`.
:::


### Other guidelines
- Log and assert APIs should not be called from ISR context.
- The assert and logging APIs are task or thread safe, i.e they can be called from multiple tasks without the
  output getting mixed.

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- The cores on which CCS or UART or shared memory writer is enabled can use either NORTOS or FreeRTOS.

::::


:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
   - The cores on which CCS or UART console logging is enabled can use either NORTOS or FreeRTOS.
   - If the UART console is used for remote core trace and needs to be opened forever in a FreeRtos application, then
   the " Remote Core Trace (UART) " option in the sysconfig can be enabled. So, the uart driver will not get closed when
   common Drivers_close function is called.
:::

## Example Usage

Include the below file to access the APIs,

**Example usage for assert:**

**Example usage for logs:**

Example usage for scanf,


:::{only} not SOC_AM62X and not SOC_AM62AX and not SOC_AM62DX
   Example snippet to show linker command file placement of the shared memory log section generated via SysCfg,

      SECTIONS
   {
       /* this is used when Debug log's to shared memory are enabled, else this is not used */
       .bss.log_shared_mem  (NOLOAD) : {} > LOG_SHM_MEM
   }

   MEMORY
   {
       /* shared memories that are used by all cores */
       /* On M4F,
        * - By default MSMC RAM is not accessible to M4F, a RAT entry is needed to make it
        *   accessible on M4F
        * - So make sure there is a RAT entry which has a 1:1 mapping from 0x70000000 to 0x70200000
        */
       /* On R5F,
        * - make sure there is a MPU entry which maps below regions as non-cache
        */
       LOG_SHM_MEM  : ORIGIN = 0x701D4000, LENGTH = 0x00004000
   }
   :::



## API Reference

```{doxygenfile} DebugP.h
```
