# ECAP APWM mode
## Introduction

This example uses the ECAP in APWM mode to generate a PWM signal.

The example does the below
- Configures ECAP in APWM mode and configures values in period and compare registers
- Waits for the specified time using the ECAP ISR.

## External Connections

::::{only} SOC_AM263X

   Connect OUTPUTXBAR1 output to oscilloscope

   **AM263X-CC**

   When using AM263x-CC with TMDSHSECDOCK (HSEC180 controlCARD Baseboard Docking Station)
   - Connect HSEC Pin 81 to oscilloscope

   **AM263X-LP**
   When using AM263x-LP
   - Connect boosterpack header J6/J8 Pin 58 to oscilloscope

::::


::::{only} SOC_AM62AX
   **AM62AX-SK**
   - The signal can be probed on Pin 7 of the J3 header on the base board (B16/GPIO1_30).
::::


::::{only} SOC_AM62DX
   **AM62DX-EVM**
   - The signal can be probed from Pin 4 of the Debug Header-J3 on Audio expansion card 1 (B18/MCASP0_AXR1).
::::


::::{only} SOC_AM62LX
   **AM62LX-EVM**
   - This example uses the user expansion connector (J2) in the  board for testing on AM62LX-EVM.
   - All pin numbers are on the expansion connector in the board.
   - The pins configured for the example is enabled on user expansion connector based on the FET selection switch(FET_SEL0).
   - The SOC_VOUT0_DATAn are the input to FET switches. The pins that are configured for the example are pinmuxed with the FET switches.
   - The S0 select pin decides if the configured pins (which is pinmuxed with SOC_VOUT0_DATAn) map to HDMI or USER EXP connector.
   - The S0 pin is triggered to a high value in the software. When the S0 is high, the pin that is configured for the example (which is pinmuxed with SOC_VOUT0_DATAn) will be available on the user expansion connector.

   The below diagram depicts the selection:

   | S2 | S1 | S0 |        IP(nA)/OP(nB1 (Or) nB2) |
|---|---|
| H | H |
| H | H |

   **For AM62L EVM PROC181E1**:
   - The pin FET_SEL0 (S0) is connected to the TCA6424 IO expander, hence it requires the user to write to the IO expander through software to give it a high signal for GPIO Expansion Connector (J2) to work. By default, this has been done through sysconfig for this example.

   **For AM62L EVM PROC181E1-1**:
   - The pin FET_SEL0 (S0) is connected to the J29 Expansion connector, hence it requires the user to connect the Pin 1 and Pin 2 of J29 to give pin S0 a high signal for GPIO Expansion Connector (J2) to work. This needs to be done by the user to receive signals on the GPIO Expansion Connector (J2).

   Below is the connection details.
   - The signal can be probed from Pin 24 of the User Expansion Connector (J2) on the base board.

::::


::::{only} SOC_AM275X
   **AM275X-EVM**
   - The signal can be probed from Pin 9(P2)  on Audio Expansion Connector1(AEC1).
::::


::::{only} SOC_AM62PX
   **AM62PX-SK**
   - The signal can be probed on Pin 7 (C25/GPIO1_30) of the User Expansion Connector (J4) on the base board.
::::


::::{only} SOC_AM62X
   **AM62X-SK**
   - The signal can be probed on Pin 7 (A18/GPIO1_30) of the User Expansion Connector (J3) on the base board.
   **AM62X-SIP-SK**
   - The signal can be probed on Pin 7 (A18/GPIO1_30) of the User Expansion Connector (J3) on the base board.
   **AM62X-SK-LP**
   - The signal can be probed on Pin 7 (C14/GPIO1_30) of the User Expansion Connector (J3) on the base board.
::::


## Supported Combinations
::::{only} SOC_AM263X

   | Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_apwm_mode/ |

::::


::::{only} SOC_AM62AX

   | Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_apwm_mode/ |

::::


::::{only} SOC_AM62X

   | Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_apwm_mode/ |

::::


::::{only} SOC_AM62DX

   | Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_apwm_mode/ |

::::


::::{only} SOC_AM62PX

   | Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_apwm_mode/ |

::::


::::{only} SOC_AM275X

   | Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/epwm/epwm_duty_cycle_sync/ |

::::


::::{only} SOC_AM62LX

   | Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_apwm_mode/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Establish connections as mentioned in External Connections section

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


## See Also

[ECAP](../../components/drivers/ecap.md)

## Sample Output

Shown below is a sample output when the application is run,

```
ECAP APWM Mode Test Started ...
ECAP APWM Test Passed!!
All tests have passed!!
```