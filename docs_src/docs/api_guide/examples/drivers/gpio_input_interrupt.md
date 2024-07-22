# GPIO Input Interrupt {#EXAMPLES_DRIVERS_GPIO_INPUT_INTERRUPT}

[TOC]

# Introduction

This example configures a GPIO pin in input mode and configures it to generate interrupt on rising edge.
The application waits for 5 key presses, prints the number of times the keys are pressed and exits.
\cond SOC_AM62X
SK-AM62 or SK-AM62-LP-SK-EVM does not contain any push button connected to MCU GPIOs.
M4F example using MCU_GPIO0_15 pin in the MCU_HEADER(J9) for generating GPIO interrupt.
Key presses can be done by connecting followed by disconnecting MCU_GPIO0_15(Pin 10 of J9) to ground (Pin 27 of J9) in the SK-AM62 or SK-AM62-LP.

A53 example is using GPIO0_14 pin in the User Expansion Connector(J3) for generating GPIO interrupt.
Key presses can be done by connecting followed by disconnecting GPIO0_14(Pin 22 of J3) to ground (Pin 6 of J3) in the @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER.

Please note that number of key presses will be higher than actual as we are manualy connecting the ground using jumpers.

\attention
A GPIO bank interrupt can be routed to only one core at a time. For example if a gpio interrupt is routed to Linux A53 core, the same cannot be routed to other cores (M4/R5).

\attention
Before running the GPIO Input interrupt example on a processor with Linux cores, disable any overlapping entries in the Linux devicetree board file. The GPIO can be excluded from the linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am625-sk.dts)
\attention
\code
&mcu_gpio0 {
        status = "reserved";
};
&mcu_gpio_intr {
        status = "reserved";
};
\endcode
\attention
A new linux devicetree blob (dtb) should be generated with this change and placed in the Linux filesystem in the boot folder. For more information, reference the AM62x Linux SDK docs, section Foundational Components > Kernel > Users Guide. The kernel and kernel modules do not need to be rebuilt and reinstalled.

A new linux image to be generated with this change and SoC initialization to done following \ref EVM_SOC_INIT_SPL . Without this change in the linux image, this example will not work.

\endcond

\cond SOC_AM64X || SOC_AM243X

\attention
A GPIO bank interrupt can be routed to only one core at a time. For example if a gpio interrupt is routed to Linux A53 core, the same cannot be routed to other cores (M4/R5).

\attention
Before running the GPIO Input interrupt example on a processor with Linux cores, disable any overlapping entries in the Linux devicetree board file. The GPIO can be excluded from the linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am642-evm.dts)
\attention
\code
&mcu_gpio0 {
        status = "reserved";
};
&mcu_gpio_intr {
        status = "reserved";
};
\endcode
\attention
A new linux devicetree blob (dtb) should be generated with this change and placed in the Linux filesystem in the boot folder. For more information, reference the AM64x Linux SDK docs, section Foundational Components > Kernel > Users Guide. The kernel and kernel modules do not need to be rebuilt and reinstalled.

\note
The RM board config need to have an entry for the interrupt router for the core if the gpio interrupt is routed to the core through the interrupt router.
\endcond

\cond SOC_AM62AX || SOC_AM62DX
@VAR_BOARD_NAME does not contain any push button connected to MCU GPIOs.

MCU-R5 example is using MCU_GPIO0_15 pin in the MCU_HEADER(J9) for generating GPIO interrupt.
Key presses can be done by connecting followed by disconnecting MCU_GPIO0_15(Pin 10 of J9) to ground (Pin 27 of J9) in the @VAR_BOARD_NAME. Please note that number of key presses will be higher than actual as we are manualy connecting the ground using jumpers.

C75 example is using GPIO1_22 pin in the user expansion connector(J3) for generating GPIO interrupt. For this, the interrupt has to be routed thorugh MAIN_GPIOMUX_INTROUTER0 instance 15.
But it is allocated to TISCI_HOST_ID_A53_2 in source/drivers/sciclient/sciclient_default_boardcfg/am62ax/sciclient_defaultBoardcfg_rm.c file as,
\code
{
    .num_resource = 16,
    .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
    .start_resource = 0,
    .host_id = TISCI_HOST_ID_A53_2,
},
\endcode

So replace the above code with the following lines in source/drivers/sciclient/sciclient_default_boardcfg/am62ax/sciclient_defaultBoardcfg_rm.c file. This will allocate the 15th instance of MAIN_GPIOMUX_INTROUTER0 to c75 core.
\code
{
    .num_resource = 15,
    .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
    .start_resource = 0,
    .host_id = TISCI_HOST_ID_A53_2,
},
{
    .num_resource = 1,
    .type = TISCI_RESASG_UTYPE (TISCI_DEV_MAIN_GPIOMUX_INTROUTER0, TISCI_RESASG_SUBTYPE_IR_OUTPUT),
    .start_resource = 15,
    .host_id = TISCI_HOST_ID_C7X_0_0,
},
\endcode
\cond SOC_AM62AX
Then rebuild the boardconfig and SBL using the steps mentioned in \ref BOARCFG_GEN .
Key presses can be done by connecting followed by disconnecting GPIO1_22(Pin 15 of J3) to ground (Pin 27 of MCU_HEADER(J9)) in the @VAR_BOARD_NAME. Please note that number of key presses will be higher than actual as we are manualy connecting the ground using jumpers.

\attention MCU GPIO and MAIN GPIO interrupt is used by Linux running on A53.

\attention
A GPIO bank interrupt can be routed to only one core at a time. For example if a gpio interrupt is routed to Linux A53 core, the same cannot be routed to other cores (C75/R5).

\attention To run this example, mcu_gpio0, mcu_gpio_intr entries, main_gpio1 and main_gpio_intr has to be removed from /arch/arm64/boot/dts/ti/k3-am62a7-sk.dtsi file of linux kernal source. A new linux image to be generated with this change and SoC initialization to done following \ref EVM_SOC_INIT_SPL . Without this change in the linux image, this example will not work.
\endcond

\cond SOC_AM62AX
\attention
A GPIO bank interrupt can be routed to only one core at a time. For example if a gpio interrupt is routed to A53 core, the same cannot be routed to other cores (C75/R5).
\endcond

\endcond

\cond SOC_AM62PX
@VAR_BOARD_NAME does not contain any push button connected to MCU GPIOs. This example is using MCU_GPIO0_15 pin in the MCU_HEADER(J14) for generating GPIO interrupt.
Key presses can be done by connecting followed by disconnecting MCU_GPIO0_15(Pin 10 of J14) to ground (Pin 27 of J14) in the @VAR_BOARD_NAME. Please note that number of key presses will be higher than actual as we are manualy connecting the ground using jumpers.

\attention MCU GPIO interrupt is used by Linux running on A53. To run this example, mcu_gpio0 and mcu_gpio_intr entries to be removed from /arch/arm64/boot/dts/ti/k3-am62p-mcu.dtsi file of linux kernal source. A new linux image to be generated with this change and SoC initialization to done following \ref EVM_SOC_INIT_SPL . Without this change in the linux image, this example will not work.

\endcond
# Supported Combinations {#EXAMPLES_DRIVERS_GPIO_INPUT_INTERRUPT_COMBOS}

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 nortos
 ^              | mcu-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 ^              | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond


\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond
\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

\cond SOC_AM273X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | c66ss0 nortos
 Toolchain      | ti-arm-clang, ti-c6000
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

\cond SOC_AWR294X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

\cond SOC_AM263X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpio/gpio_input_interrupt/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\cond SOC_AM62PX
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond
\cond SOC_AM64X
- Press and release SW5 button on the EVM to generate the trigger GPIO interrupt. This button is connected to GPIO1_43.
\endcond

\cond SOC_AM243X

## AM243X-EVM
- Press and release SW5 button on the EVM to generate the trigger GPIO interrupt. This button is connected to GPIO1_43.

## AM243X-LP
- Press and release SW5 button on the EVM to generate the trigger GPIO interrupt. This button is connected to GPIO1_54.

\endcond

\cond SOC_AM273X

## AM273X-EVM
- Press and release SW2 button on the EVM to generate the trigger GPIO interrupt. This button is connected to MSS_GPIO_28.

\endcond

\cond SOC_AWR294X

## AWR294X-EVM
- Press and release SW2 button on the EVM to generate the trigger GPIO interrupt. This button is connected to GPIO28.

\endcond

\cond SOC_AM263X

## AM263X-CC
- Press and release SW1 button on the EVM to generate the trigger GPIO interrupt. This button is connected to GPIO21.

## AM263X-LP
- Press and release SW4 button on the EVM to generate the trigger GPIO interrupt. This button is connected to GPIO123.

\endcond

# See Also

\ref DRIVERS_GPIO_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
GPIO Input Interrupt Test Started ...
GPIO Interrupt Configured for Rising Edge ...
Connect the MCU_GPIO0_15 pin on EVM to ground and release to trigger GPIO interrupt ...
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 0 times
Key is pressed 1 times
Key is pressed 2 times
Key is pressed 5 times
GPIO Input Interrupt Test Passed!!
All tests have passed!!
\endcode
