# ECAP EPWM Loopback
## Introduction

This example demonstrates ePWM to eCAP loopback test.
The ecap module is configured in the capture mode and the ecap device pin is
configured as input pin. A square wave needs to be fed to the ecap pin
externally. Based on the internal counter the count values for each of the
edge is latched in register. 4th edge will generate the interrupt. Based on
the latched counter values, calculates the input signal frequency and the
duty cycle based on the epwm input to the ecap module.
ePWM is configured to generate a square wave with 25% duty cycle.
Connect the ePWM output to eCAP input externally on the board.
Below is the setup details.

::::{only} SOC_AM64X
   - This example needs IO breakout board for testing on AM64X-EVM.
   - Short Pin 2 and 3 of J11 on IO break out board.
   - Connect the EPWM output to ECAP input on the board by connecting
     Pin 7 on J6 Header in IO IO break out board to Pin 1 on J12 Header on base board.
::::


::::{only} SOC_AM243X

   **AM243X-EVM**
   - This example needs IO breakout board for testing on AM243X-EVM.
   - Short Pin 2 and 3 of J11 on IO break out board.
   - Connect the EPWM output to ECAP input on the board by connecting
     Pin 7 on J6 Header in IO IO break out board to Pin 1 on J12 Header on base board.

   **AM243X-LP**
   - Connect the EPWM output to ECAP input on the AM243X-LP board by connecting
     Pin 1 on J4(BP 40) Header to Pin 1 on J21 Header on the board.

::::


::::{only} SOC_AM273X

   **AM273X-EVM**
   - Connect the EPWM output to ECAP input on the AM273X board.
   - Remove the R144 resistor which is connected to MSS_SPIA_CLK on BallNo. G19
   - On the board connect external wire from resistor R81 to MSS_SPIA_CLK connected on BallNo G19(where R144 resistor is removed).

::::


::::{only} SOC_AM62AX

   **AM62AX-SK**
   - Connect the EPWM output to ECAP input on the board by connecting Pin 24 to Pin 7 on J3 Header.
   - EPWM O/P: D16/GPIO1_15 (Pin_24)
   - ECAP I/P: B16/GPIO1_30 (Pin_7)

::::


::::{only} SOC_AM62DX

   **AM62DX-EVM**
   This example uses the Debug Header(J3) on Audio expansion card 1 for testing on AM62DX-EVM.

   - Connect the EPWM output to ECAP input by connecting Pin 4 to Pin 6 on J3 Header of Audio expansion card 1.
   - EPWM O/P: B18/MCASP0_AXR1 (Pin_4)
   - ECAP I/P: B19/MCASP0_AXR2 (Pin_6)

::::


::::{only} SOC_AM62PX

   **AM62PX-SK**
   - Connect the EPWM output to ECAP input
   - Connect Pin 24 to Pin 7 of User Expansion Connector (J4) on the board.
   - EPWM O/P: D20/GPIO1_15 (Pin_24)
   - ECAP I/P: C25/GPIO1_30 (Pin_7)

::::


::::{only} SOC_AM62X

   **AM62X-SK**
   - Connect the EPWM output to ECAP input
   - Connect Pin 24 to Pin 7 of User Expansion Connector (J3) on the board.
   - EPWM O/P: A13/GPIO1_15 (Pin_24)
   - ECAP I/P: A18/GPIO1_30 (Pin_7)

   **AM62X-SIP-SK**
   - Connect the EPWM output to ECAP input
   - Connect Pin 24 to Pin 7 of User Expansion Connector (J3) on the board.
   - EPWM O/P: A13/GPIO1_15 (Pin_24)
   - ECAP I/P: A18/GPIO1_30 (Pin_7)

   **AM62X-SK-LP**
   - Connect the EPWM output to ECAP input
   - Connect Pin 24 to Pin 7 of User Expansion Connector (J3) on the board.
   - EPWM O/P: C11/GPIO1_15 (Pin_24)
   - ECAP I/P: C14/GPIO1_30 (Pin_7)

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

   | S2 | S1 | S0 | IP(nA)/OP(nB1 (Or) nB2) |
   |---|---|---|---|
   | H | H | L | nA=nB1  ->  SOC - HDMI |
   | H | H | H | nA=nB2  ->  SOC - GPIO EXP CONN |

   **For AM62L EVM PROC181E1**:
   - The pin FET_SEL0 (S0) is connected to the TCA6424 IO expander, hence it requires the user to write to the IO expander through software to give it a high signal for GPIO Expansion Connector (J2) to work. By default, this has been done through sysconfig for this example.

   **For AM62L EVM PROC181E1-1**:
   - The pin FET_SEL0 (S0) is connected to the J29 Expansion connector, hence it requires the user to connect the Pin 1 and Pin 2 of J29 to give pin S0 a high signal for GPIO Expansion Connector (J2) to work. This needs to be done by the user to receive signals on the GPIO Expansion Connector (J2).

   Connect the EPWM output to ECAP input
   - Connect Pin 24 to Pin 18 of User Expansion Connector (J2) on the board.
   - EPWM O/P: G22/V0UT0_DATA13 (Pin_18)
   - ECAP I/P: L22/V0UT0_DATA0 (Pin_24)

::::


::::{only} SOC_AM275X
   **AM275X-EVM**
   This example uses  Audio expansion Connector1 (AEC1) for testing

   - Connect the EPWM output to ECAP input by connecting Pin 3 to Pin 9 on AEC1.
   - EPWM O/P: T2 (Pin_3)
   - ECAP I/P: P2 (Pin_9)

::::


## Supported Combinations
::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

::::


::::{only} SOC_AM273X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c66ss0 nortos |
| Toolchain | ti-arm-clang, ti-c6000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

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
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

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
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ecap/ecap_epwm_loopback/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::

- Please connect the ePWM output to eCAP input externally as mentioned above in Introduction section

## See Also

[ECAP](../../components/drivers/ecap.md)

## Sample Output

Shown below is a sample output when the application is run,

```
EPWM to ECAP loopback application started...
Please refer EXAMPLES_DRIVERS_ECAP_EPWM_LOOPBACK example user guide for the test setup details.
Count1 = 93751, Count2 = 31247, Count3 = 93751, Count4 = 31247
Hight time is 250 us, Low time is 750 us
Expected DutyCycle 25%, Actual DutyCycle 25%
Expected Output Frequency 1KHz, Actual Output Frequency 1KHz
All tests have passed.
```