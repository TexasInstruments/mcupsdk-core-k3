# Firewall Isolation - MCU Domain
## Introduction

The example demonstrates the MCU firewall isolation in the use case when the MCU domain is running a safety application.
The MCU-R5 application configures a firewall to the MAIN domain I2C by allowing access only to the MCU-R5 core and locks
this firewall configuration ownership to the MCU core. After configuring the firewall, it reads data from the main domain
I2C to check the access from MCU-R5 core. Then it will a send a ipc notify message to the Wkup-R5 core to trigger a
firewall exception.
The Wkup-R5 application waits for ipc notify message from the MCU core. Upon receiving the message, it triggers a firewall exception by accessing the I2C0 register config and it will go to data abort.
The MCU-R5 receives a interrupt for firewall exception. If the interrupt is not received the test fails.

## Supported Combinations
::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/safety/fwl_isolation |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/safety/fwl_isolation |

::::


## Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)


## Sample Output

Shown below is a sample output when the application is run,

```
################################ Wakeup R5 Log #######################################
Sciserver Testapp Built On: Nov 15 2023 10:51:56
Sciserver Version: v2023.09.0.0-REL.MCUSDK.09.00.01.01+
RM_PM_HAL Version: w09.00.01-am62p
Starting Sciserver..... PASSED
Waiting for ipc notify message to trigger firewall exception....


################################ MCU R5 Log #######################################

Configure I2C0 firewall to allow access only to MCU core... DONE !!!
Readback the firewall configuration ... DONE !!!
Retrieved Firewall data:
Fwl ID: 8
Region No: 1
Control: 0x0000000A
No of permission regs: 3
Permission[0]: 0x0060FFFF
Permission[1]: 0x0060FFFF
Permission[2]: 0x0060FFFF
Start address: 0x0000000020000000
End address: 0x0000000020000FFF

I2C read data through MCU core... !!!
Sample 0: 170
Sample 1: 85
Sample 2: 51
Sample 3: 238
Sample 4: 1
I2C read data through MCU core... DONE !!!
Waiting for firewall exception trigger from the other core...
Firewall exception occurred...
All tests have passed!!

```