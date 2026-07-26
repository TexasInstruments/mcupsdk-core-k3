# Enet TSN AVTP AES3 AAF Example

## Introduction

::::{only} SOC_AM62DX
:::{note}
This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
:::
::::

This Ethernet TSN example demonstrates transmission of non-PCM Audio Data data using Dolby EC3&trade; Format Data using AES3 AAF AVB listener instance. Here, the listerner waits for talker to send the audio stream, when the audio stream is received, it is decoded into SMPTE337 frames and copied into the memory shared with Remote Core(C7x core). The Remote Core periodically reads from the shared memory and copies into its local memory for further processing.

The below image shows the program flow for the AES3 AAF listener application.

:::{figure} ../../images/examples/dolbyec3_listener.png
:width: 90%
AES3 AAF Listener Program Flow
:::

The `get_frame337()` call returns a pointer to the SMPTE337 Frame which is copied to shared memory. The C7x can read from this shared memory to get frames in SMPTE337 format which contains Dolby EC3&trade; frames.

## Supported Combinations

::::{only} SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos, c75ss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/tsn/aes3_aaf_app/aes3_aaftalker_app, aes3_aaflistener_app

::::

::::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos, c75ss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/tsn/aes3_aaf_app/aes3_aaftalker_app, aes3_aaflistener_app

::::

## Steps to Run the Example

### Prerequisites
- EVM Board
- CAT6 Ethernet cable
- AES3 AAF Talker device.

### Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu.
- When using makefiles to build, note the required combination and build using
  make command.

### HW Setup

- Connect the One end of the CAT6 cable to the EVM and the other end of the CAT6 cable to the talker.

### Run the example

:::{attention}
If you need to reload and run again, a CPU power-cycle is MUST.
:::

:::{note}
mcu-r5 program has to be started before running c7x program.
:::

- Load both mcu-r5 and c7x binaries to the evm and click on run.
- Start AVB Talker if not started already.
- You will see logs in the UART terminal as shown in the next section.
- The print `INF:avtp:[RX] frame337 wlen=6144 bits` confirms the reception of Dolby EC3&trade; payload in SMPTE337 Format.

### Sample output

```
==========================
       TSN CPSW App
==========================
Enabling clocks!
start to open driver.
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:0 From 4 To 2

Init all configs
----------------------------------------------
sitara-cpsw: init config
Mdio_open: MDIO Manual_Mode enabled
sitara-cpsw: Open port 1
EnetPhy_bindDriver: PHY 15: OUI:080028 Model:23 Ver:01 <-> 'dp83867' : OK
sitara-cpsw: Open port 2
PHY 15 is alive
sitara-cpsw: Create RX task for regular traffic
initQs() txFreePktInfoQ initialized with 4 pkts
MAC port addr: 70:ff:76:1d:ec:f2
Start: uniconf_task
sitara-cpsw: default RX flow started
EnetApp_uniconfTask: dbname: NULL
EnetApp_gptpYangConfig:domain=0
Start: gptp2d_task
Start: aaf_dolby_task
EnetApp_initTsn:TSN app start done!
Waiting for GPTP ready!!

GPTP ready!!

INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
```

## See Also

[Networking Examples](../examples_networking.rst)
