# Ethernet AVB Audio Playback Demo {#EXAMPLES_ENET_CPSW_AVB_AUDIO_DEMO}

[TOC]

# Introduction
This example demonstrates audio playback over Ethernet AVB (Audio Video Bridging) using the eAVB stack. The setup involves two devices: a Central Compute and an Auto Amplifier. Audio captured from each device is transmitted over the network using eAVB protocol, allowing both devices to play back audio recorded from the other. The eAVB stack ensures synchronized, low-latency audio streaming in both directions, showcasing real-time audio transport and playback between the Central and Amplifier units.

This demo also implements Media Clock Recovery to ensure synchronized playback. When using the DP83TG721 Add-on PHY, the algorithm described in \ref EXAMPLES_ENET_AVB_MULTISTREAM_MCR is used for Media Clock Recovery. With the DP83867 Add-on PHY, CDCE-based Media Clock Recovery is performed. Note that phase synchronization is not supported with CDCE-based Media Clock Recovery, while both phase and frequency synchronization are supported with DP83TG721-based Media Clock Recovery. For the purposes of this demo, which primarily demonstrates the latency performance of audio over eAVB, both types of Media Clock Recovery provide similar performance.

See also :\ref ENET_CPSW_AVTP

# Supported Combinations

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER-dp83tg721, @VAR_BOARD_NAME_LOWER-dp83867
 Example folder | source/networking/enet/core/examples/tsn/aafpcm_audio_demo/central_compute, auto_amplifier

\endcond

# Prerequisites
- 2 x EVM boards with DP83TG721 Add-on PHY or DP83867 Add-on PHY.
- CAT6 or Automotive Ethernet Cable.
- Earphones with 3.5mm Jack.
- 3.5mm Aux Cable
- An Audio Source, can be a PC/Laptop or a Mobile Phone with 3.5mm Jack.

## HW Setup

\imageStyle{am275_b2b_setup.png,width:40%}
\image html am275_b2b_setup.png Audio Playback Demo Setup

- Connect Audio Input to J1 Top, Connect Earphone Jack to J4 Top on the other EVM.

# Overview

\imageStyle{demo1_overview.png,width:85%}
\image html demo1_overview.png Audio Playback Demo Overview

# Demo Configuration Parameters

| Parameter                     | Description         |
|-------------------------------|---------------------|
| Number of Channels            | 8                   |
| Sample Rate (Media Clock Freq)| 48 kHz              |
| Bit Depth                     | 32 bits             |
| McASP Transaction Size        | 16 Samples          |
| Samples Per AVTPDU            | 6 Samples           |
| AVB Transaction Frequency     | 8000 Hz (125 µs)    |
| McASP Transaction Frequency   | 3000 Hz (333 µs)    |
| AVTP Packet Length            | 243 Bytes           |

# Performance

For the Performance of this Demo, Refer to the \ref EAVB_PERFORMANCE.

# Steps to Run the Example

## Build the example
- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Run the example

\attention If you need to reload and run the demo again, a CPU power cycle is REQUIRED.

- Load both the Central Compute and Auto Amplifier applications onto the EVMs, starting each application one after the other. On the Central Compute EVM, make sure to load both the C7x and R5 binaries.
- Wait about 15 seconds. Audio playback will start after this message and should be audible if the audio input is properly connected.

\note Channel #3 periodically transmits a magic number to trigger the Latency GPIO. For this reason, Channel #3 is not recommended for audio playback in this demo.

### Central Compute Log
```
==========================
       TSN CPSW App
==========================
Enabling clocks!
start to open driver.
EEPROM 0 MAC addr: EEPROM 1 MAC addr: MAC is not fused in eeprom instance number 2, Invalid typeword FF
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:1 From 4 To 2

Init all configs
----------------------------------------------
sitara-cpsw: init config
Mdio_open:320
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 0 is alive
PHY 3 is alive
sitara-cpsw: Create RX task for regular traffic
initQs() txFreePktInfoQ initialized with 4 pkts
MAC port addr: 44:6b:1f:2c:2d:2b
sitara-cpsw: default RX flow started
Uniconf/ModuleInit time= 798/4277 us
EnetApp_initTsn:TSN app start done!
log ovflow!
log ovflow!
INF:ubase:SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100%)
CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
log ovflow!
INF:cbase:rxChId 2 has owner dmaRxShared 0
log ovflow!
ll_avtpe_receive_data: enable Rx Zero-Copy
Cpsw_handleLinkUp:1423
MAC Port 1: link up
INF:cbase:000003-050905:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!! (142us since link change event)
WRN:gptp:000003-061284:waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=44:6B:1F:FF:FE:32:AC:F3, thisClock=44:6B:1F:FF:FE:2C:2D:2B, neighborPropDelay=445
      5. 72s : CPU load =   4.69 %
Link is Stable...
     10. 73s : CPU load =   6.03 %
LF: 10236539304, 10238382364, 10241715319
HF: 10241818374, 10241839204, 10241860034
Calculated Edge Diff = 19394
     15. 74s : CPU load =  18.29 %
     20. 75s : CPU load =  18.48 %
     25. 76s : CPU load =  18.45 %
     30. 77s : CPU load =  18.59 %
     35. 78s : CPU load =  18.73 %
     40. 79s : CPU load =  18.47 %
     45. 80s : CPU load =  18.74 %
     50. 81s : CPU load =  18.51 %
     55. 82s : CPU load =  18.54 %
     60. 83s : CPU load =  18.49 %
     65. 84s : CPU load =  18.27 %
     70. 85s : CPU load =  18.67 %
     75. 86s : CPU load =  18.37 %
     80. 87s : CPU load =  18.63 %

```
### Auto Amplifier Log
```
==========================
       TSN CPSW App
==========================
Enabling clocks!
start to open driver.
EEPROM 0 MAC addr: EEPROM 1 MAC addr: EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:1 From 4 To 3

Init all configs
----------------------------------------------
sitara-cpsw: init config
Mdio_open:320
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 0 is alive
PHY 3 is alive
sitara-cpsw: Create RX task for regular traffic
initQs() txFreePktInfoQ initialized with 4 pkts
MAC port addr: 44:6b:1f:32:ac:f3
sitara-cpsw: default RX flow started
Uniconf/ModuleInit time= 780/4259 us
EnetApp_initTsn:TSN app start done!
log ovflow!
log ovflow!
INF:ubase:SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100%)
CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
log ovflow!
INF:avtp:avtpc_init: l2-1.2.3
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=2 numRxChannels=1 dmaRxChId=2 nTxPkts=16 nRxPkts=8 pktSize=1536
INF:cbase:rxChId 2 has owner dmaRxShared 0
log ovflow!
ll_avtpe_receive_data: enable Rx Zero-Copy
      5. 67s : CPU load =   5.71 %
Cpsw_handleLinkUp:1423
MAC Port 1: link up
INF:cbase:000005-545918:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!! (144us since link change event)
WRN:gptp:000005-593194:waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=44:6B:1F:FF:FE:2C:2D:2B, thisClock=44:6B:1F:FF:FE:32:AC:F3, neighborPropDelay=442
INF:avtp:di=0, GM is stable. Adjust messages interval now
Link is Stable...
Wait for gPTP Sync........
gPTP Synced........
LF: 7208270284, 7211603187, 7214936091
HF: 7215030601, 7215051431, 7215072261
Calculated Edge Diff = 10798
     10. 68s : CPU load =   3.35 %
     15. 69s : CPU load =  15.69 %
     20. 70s : CPU load =  20.15 %
     25. 71s : CPU load =  20.61 %
     30. 72s : CPU load =  21.66 %
     35. 73s : CPU load =  21.63 %
     40. 74s : CPU load =  21.36 %
     45. 75s : CPU load =  22.04 %
     50. 76s : CPU load =  21.06 %
     55. 77s : CPU load =  21.14 %
     60. 78s : CPU load =  21.24 %
     65. 79s : CPU load =  21.14 %
     70. 80s : CPU load =  22.07 %
     75. 81s : CPU load =  21.53 %
     80. 82s : CPU load =  21.60 %
     85. 83s : CPU load =  21.40 %
     90. 84s : CPU load =  21.70 %
     95. 85s : CPU load =  21.26 %
    100. 86s : CPU load =  21.34 %
    105. 87s : CPU load =  21.95 %
```
# Troubleshooting

- **No Audio:** Ensure the audio source is properly connected and powered on. Verify that the PHY link is established and that the logs are similar to those shown in the previous section.
- **No Link:** If you are using the DP83TG721 PHY, refer to the Troubleshooting section in \ref EXAMPLES_ENET_AVB_MULTISTREAM_MCR.

# See Also

\ref NETWORKING |
\ref ENET_CPSW_AVTP