
# HW Interrupts
:::{admonition} Attention
See also [FreeRTOS](../os/freertos.md), [NO RTOS](../os/nortos.md) for list of CPU specific supported and unsupported features.
:::


## Features Supported

- Register a interrupt callback to a specific CPU number
- Ability to pass user specific argument to the interrupt callback
- Enable, disable, restore and clear specific CPU interrupts
- Enable, disable, restore global CPU interrupt

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM64X or SOC_AM243X or SOC_AM275X or SOC_AM62PX or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S

- For ARM R5,
  - Ability to specify interrupt as FIQ or IRQ, level or pulse
  - Ability to specify interrupt priority

::::

::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- For ARM M4,
  - Ability to specify interrupt priority
  - Ability to specify systick ISR and NVIC external interrupt ISR

::::


::::{only} SOC_AM64X

- For ARM A53,
  - Ability to specify interrupt priority
  - Nested Interrupts
  - Ability to specify interrupt as level or pulse

::::


## Features NOT Supported

See also [FreeRTOS](../os/freertos.md), [NO RTOS](../os/nortos.md) for list of unsupported features.

## Important Usage Guidelines

- For ARM R5,
  - TI VIM is the interrupt controller that is supported.
  - `HwiP_disable`, `HwiP_restore`, `HwiP_enable` only affect state of IRQ. FIQ state is not changed
  - Refer ARMv7-R Architecture reference manual and SOC TRM for more details.

::::{only} SOC_AM62X or SOC_AM64X or SOC_AM243X or SOC_AM62PX or SOC_AM62LX or SOC_AM263X or SOC_AM273X or SOC_AWR294X

- For ARM M4,
  - ARM NVIC is the interrupt controller that is supported.
  - Interrupt numbers 0 to 15 are for internal interrupts,
       like reset (1), NMI (2), fault handlers (3-6), SVC (11), PendSV (14), SysTick (15)
     - Interrupt numbers 16 to 80 are used as external NVIC interrupts.
       The TRM will document M4F interrupt numbers as xxx_M4FSSx_COREx_NVIC_IN_n.
       This corresponds to interrupt number (16 + n) at NVIC and (16 + n) is used as input to the HwiP APIs
     - Refer ARMv7-M Architecture reference manual and SOC TRM for more details.
:::


::::{only} SOC_AM64X or SOC_AM62DX

- For ARM A53,
  - GIC V3 is the interrupt controller that is supported.
  - Interrupt numbers 0-15 are for SGI, 16-31 for PPI and 32-255 for SPI.
  - Refer ARMv8-A Architecture reference manual and SOC TRM for more details.

::::

::::{only} SOC_AM243X

- On {{ VAR_SOC_NAME }},
    CPU type  | Valid interrupt numbers  | Valid interrupt priorities
    ----------|--------------------------|---------------------------
    R5F       | 0  .. 511                | 0 (highest) .. 15 (lowest)
    M4F       | 15 ..  79                | 0 (highest) ..  7 (lowest)

::::

::::{only} SOC_AM64X

- On {{ VAR_SOC_NAME }},
    CPU type  | Valid interrupt numbers  | Valid interrupt priorities
    ----------|--------------------------|---------------------------
    R5F       | 0  .. 511                | 0 (highest) .. 15 (lowest)
    M4F       | 15 ..  79                | 0 (highest) ..  7 (lowest)
    A53       | 0 ..  255                | 0 (highest) .. 14 (lowest)

::::

::::{only} SOC_AM62X

- On {{ VAR_SOC_NAME }},
    CPU type  | Valid interrupt numbers  | Valid interrupt priorities
    ----------|--------------------------|---------------------------
    R5F       | 0  .. 511                | 0 (highest) .. 15 (lowest)
    M4F       | 15 ..  79                | 0 (highest) ..  7 (lowest)
    A53       | 0 ..  255                | 0 (highest) .. 14 (lowest)

::::

::::{only} SOC_AM62AX or SOC_AM62DX

- On {{ VAR_SOC_NAME }},
    CPU type  | Valid interrupt numbers  | Valid interrupt priorities
    ----------|--------------------------|---------------------------
    R5F       | 0  .. 511                | 0 (highest) .. 15 (lowest)
    A53       | 0 ..  255                | 0 (highest) .. 14 (lowest)

- On C75,
  - The C75 CPU supports 64 interrupts.
  - The CLEC event ID can be mapped to any of C75 interrupts.
  - If you are configuring software interrupt, then set eventId to HWIP_INVALID_EVENT_ID.
  - While mapping CLEC event ID to interrupt number, refer the below table and avoid overlapping interrupts.
    Module    | Interrupt number used    |
    ----------|--------------------------|
    EQEP      | 5   .. 7                 |
    TIMER     | 8  .. 15                 |
    I2C       | 16  .. 20                |
    GPIO      | 21                       |
    UART      | 22  .. 30                |
    ECAP      | 25  .. 27                |
    UDMA      | 32  .. 48                |
    EPWM      | 49  .. 51                |
    MCASP     | 53  .. 58                |
    IPC       | 59  .. 62                |
    MCSPI     | 1, 2, 31, 52, 63        |

::::

::::{only} SOC_AM62AX or SOC_AM62DX

- On {{ VAR_SOC_NAME }},
    CPU type  | Valid interrupt numbers  | Valid interrupt priorities
    ----------|--------------------------|---------------------------
    R5F       | 0  .. 511                | 0 (highest) .. 15 (lowest)

- On C75,
  - The C75 CPU supports 64 interrupts.
  - The CLEC event ID can be mapped to any of C75 interrupts.
  - If you are configuring software interrupt, then set eventId to HWIP_INVALID_EVENT_ID.
  - While mapping CLEC event ID to interrupt number, refer the below table and avoid overlapping interrupts.
    Module    | Interrupt number used    |
    ----------|--------------------------|
    TIMER     | 2 .. 6                   |
    IPC       | 7 .. 11                  |
    OSPI      | 13                       |
    MMCSD     | 14                       |
    I2C       | 15 .. 19                 |
    MCSPI     | 20 .. 24                 |
    ECAP      | 25 .. 30                 |
    UART      | 22, 32 .. 38             |
    MCASP     | 39 .. 48                 |
    EPWM      | 49 .. 51                 |
    UDMA      | 52 .. 61                 |
    WDT       | 62 .. 63                 |
    ASRC      | 20 .. 29                 |
    Not Used  | 12, 31                   |

::::

::::{only} SOC_AM62PX

- On {{ VAR_SOC_NAME }},
    CPU type  | Valid interrupt numbers  | Valid interrupt priorities
    ----------|--------------------------|---------------------------
    R5F       | 0  .. 511                | 0 (highest) .. 15 (lowest)

::::


## Example Usage

Include the below file to access the APIs,

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/HwiP_sample.c
:language: c
:lines: 1-10
```

**Example ISR:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/HwiP_sample.c
:language: c
:lines: 12-25
```

**Example to register a ISR for CPU interrupt 10:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/HwiP_sample.c
:language: c
:lines: 27-35
```

::::{only} SOC_AM62X

**Example to register a ISR for CPU interrupt 10 on M4F:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/HwiP_m4_sample.c
:language: c
:lines: 27-35
```

::::

**Example to disable and restore interrupts across a critical section:**

```{literalinclude} ../../../../../docs/api_guide/doxy_samples/kernel/dpl/HwiP_sample.c
:language: c
:lines: 37-50
```


## API Reference

```{doxygenfile} HwiP.h
```
