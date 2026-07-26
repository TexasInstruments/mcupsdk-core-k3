# Ethernet AVB Audio Playback and Etherring Demo

## Introduction
This example demonstrates the zonal audio use case using the AM275 central compute platform. It showcases how audio streams can be transmitted from the central node to multiple zones for zonal playback, as well as how audio from individual zones can be sent back to the central node for playback. The demo also highlights the system's ability to measure and showcase latency performance, specifically focusing on the impact of overlapping latency-sensitive audio and control data traffic within an Ethernet ring (etherring) configuration. This setup is representative of automotive zonal architectures, where synchronized and low-latency audio distribution is critical.

See also :[Ethernet AVB Stack - API and Integration Guide](../../components/networking/enet_cpsw_avtp_apiguide.md)

## Supported Combinations

:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos, c75ss0-0_freertos
 Toolchain      | ti-arm-clang, ti-c7000
 Board          | {{ VAR_BOARD_NAME_LOWER }}-dp83867
 Example folder | source/networking/enet/core/examples/tsn/aafpcm_audio_etherring_demo/central_compute, auto_amplifier

:::

## Prerequisites
- 4 x EVM boards with 2x DP83867 Add-on PHY on each EVM.
- 4 x CAT6 or Automotive Ethernet Cable.
- 2 x Audio Expansion Card
- Earphones with 3.5mm Jack
- 3.5mm Aux Cable
- An Audio Source, can be a PC/Laptop or a Mobile Phone with 3.5mm Jack.

### HW Setup

![](../../images/networking/audio_etherring_setup.png)

## Audio Traffic Overview
![](../../images/networking/audio_etherring_avb.png)

## Control Traffic Overview
![](../../images/networking/audio_etherring_control.png)

## Background Traffic Overview
![](../../images/networking/audio_etherring_background.png)

## Demo Configuration Parameters

### Stream Configuration Table
| Stream/Traffic        | Description                                         | Packet Size   | Packet Interval   |
|-----------------------|-----------------------------------------------------|---------------|-------------------|
| **gPTP**              | PTP messages for time synchronization               | ~100 Bytes    | 125 ms – 1 s      |
| **Control Data**      | GPIO data mimicking vehicle control data            | ~100 Bytes    | 250 µs            |
| **AVB MIC (Class A)** | Low-latency data for vehicle noise cancellation     | ~300 Bytes    | 125 µs            |
| **AVB CRF**           | CRF messages for audio clock synchronization        | ~200 Bytes    | 20 ms             |
| **AVB SPK (Class A)** | Low-latency data for speaker audio                  | ~300 Bytes    | 125 µs            |
| **Best Effort**       | Background data (non-critical)                      | Random        | Random            |

### Stream ID Table
| Source Device    | Stream Description                | Stream ID                | Destination MAC Address   |  Data Input       | Data Output            |
|------------------|-----------------------------------|--------------------------|---------------------------|-------------------|------------------------|
| Central          | Central Microphone to All Zones   | 00:01:02:03:04:05:00:01  | 91:E0:F0:00:FE:01         | Central J1 and J2 | All Zones J3 and J4    |
| Amplifier Right  | Amp Microphone to Central         | 00:01:02:03:04:05:00:11  | 91:E0:F0:00:FE:11         | Right J1 and J2   | Audio Expansion Card 1 |
| Amplifier Tail   | Amp Microphone to Central         | 00:01:02:03:04:05:00:12  | 91:E0:F0:00:FE:12         | Tail J1 and J2    | Central J3 and J4      |
| Amplifier Left   | Amp Microphone to Central         | 00:01:02:03:04:05:00:13  | 91:E0:F0:00:FE:13         | Left J1 and J2    | Audio Expansion Card 2 |
| Central          | Central gpio1 to Right            | 00:01:02:03:04:05:01:01  | 91:E0:F0:00:FE:01         | Central J31-1     | Right J28-2            |
| Central          | Central gpio2 to Left             | 00:01:02:03:04:05:01:02  | 91:E0:F0:00:FE:02         | Central J31-3     | Left J28-2             |
| Central          | Central gpio3 to Tail             | 00:01:02:03:04:05:01:03  | 91:E0:F0:00:FE:03         | Central J31-5     | Tail J28-2             |
| Amplifier Right  | Amp gpio1 to Central              | 00:01:02:03:04:05:01:21  | 91:E0:F0:00:FE:21         | Right J31-1       | Central J31-2          |
| Amplifier Left   | Amp gpio3 to Central              | 00:01:02:03:04:05:01:22  | 91:E0:F0:00:FE:22         | Left J31-1        | Central J31-4          |
| Amplifier Tail   | Amp gpio2 to Central              | 00:01:02:03:04:05:01:23  | 91:E0:F0:00:FE:23         | Tail J31-1        | Central J31-8          |

### AVTP Stream Configuration
The following parameters are valid for all the AVTP AAF Streams in the above demo unless specified.
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

## Steps to Run the Example

### Build the example
- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- When using makefiles to build, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

### Run the example

:::{attention}
If you need to reload and run the demo again, a CPU power cycle is REQUIRED.
:::


- Since this demo uses 4 AM275 EVMs, for the ease of use, it is recommended to go with the SD Boot instead of loading from CCS. For more information on how to use SD Boot refer to the [SBL SD](../drivers/sbl_sd.md) page.
- Load both the Central Compute and Auto Amplifier applications onto the EVMs, starting each application one after the other. On the Central Compute EVM, make sure to load both the C7x and R5 binaries.
- Type the Role of the Device on the terminal as specified and press enter. It is important to open the UART Terminal before powering on the board so this prompt will not be missed.
- Wait about 30 seconds. Audio playback will start after this message and should be audible if the audio input is properly connected. The Control Data also starts along with the audio data.

:::{note}
Channel #3 periodically transmits a magic number to trigger the Latency GPIO. For this reason, Channel #3 is not recommended for audio playback in this demo.
:::

#### Central Compute Log
```
=====================================
       AVB Audio Playback Demo
=====================================

0 - Central Compute Node
1 - Zone Left Node
2 - Zone Right Node
3 - Zone Tail Node
Enter the nodeId :
0
Got Node Id: 0
Acting as Central Compute Node
Enabling clocks!
start to open driver.
EEPROM 0 MAC addr: EEPROM 1 MAC addr: EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:1 From 4 To 3

Init all configs
----------------------------------------------
sitara-cpsw: init config
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 0 is alive
PHY 3 is alive
initQs() txFreePktInfoQ initialized with 10 pkts
MAC port addr: 44:6b:1f:32:ae:89
sitara-cpsw: default RX flow started
AEC1 is not Detected, skipping Configuration...AEC2 is not Detected, skipping Configuration...Uniconf/ModuleInit time= 911/5297 us
log ovflow!
INF:ubase:GPTP_MEDIUM_ALLOC: fragsize=16 fragused/fragnum=865/944 (91%)
INF:ubase:GPTP_SMALL_ALLOC: fragsize=4 fragused/fragnum=19/74 (25%)
INF:ubase:SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100%)
EnetApp_initTsn:TSN app start done!
CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
Waiting for C7x Core......
log ovflow!
INF:avtp:avtpc_direct_setup:direct is set: tx=0, rx=1
INF:avtp:ll_avtpe_receive_data: enable Rx Zero-Copy
C7x Core Started......
Wait for Linkup......
EnetCbsApp_registerCbsEnableToUniconf: succeeded

ask uniconf to write adminIdleSlop succeeded

INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=7, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
Registered adminIdleSlope finished. tc=7
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=6
INF:uconf:respond_getnotice:a notice with a deletion
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=6, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=5
ask uniconf to write adminIdleSlop succeeded

log ovflow!
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=4, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
Registered adminIdleSlope finished. tc=4
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=3
INF:uconf:respond_getnotice:a notice with a deletion
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=3, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=2
ask uniconf to write adminIdleSlop succeeded

log ovflow!
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=1, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
Registered adminIdleSlope finished. tc=1
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=0
INF:uconf:respond_getnotice:a notice with a deletion
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
EnetCbsApp_registerCbsEnableToUniconf: succeeded

Configured CBS


INF:uconf:respond_getnotice:a notice with a deletion
INF:uconf:create_semname_with_dbname:null dbname is specified.
INF:uconf:get_queue_map_params:netdev=tilld0, num_tc=0
Wait for Linkup......
Wait for Linkup......
Wait for Linkup......
Wait for Linkup......
Wait for Linkup......
Cpsw_handleLinkUp:1423
MAC Port 1: link up
INF:cbase:000009-849599:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!! (79us since link change event)
INF:gptp:index=1 speed=1000, duplex=full
INF:gptp:set neighborGptpCapable, domainIndex=0, portIndex=1 wtout=24000000000
Cpsw_handleLinkUp:1423
MAC Port 2: link up
INF:cbase:000009-949645:cbl_query_response:tilld1: link UP, speed=1000, duplex=1 !!!! (121us since link change event)
log ovflow!
Wait for Linkup......
WRN:gptp:000010-874382:waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=44:6B:1F:FF:FE:32:AC:F3, thisClock=44:6B:1F:FF:FE:32:AE:89, neighborPropDelay=450
INF:gptp:waiting_for_pdelay_interval_timer_proc:portIndex=1, not asCapable
log ovflow!
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:000011-000154:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000011-124167:setSyncTwoStep_txSync:domainIndex=0, portIndex=2, sync gap=11125msec, tsync_ts_threshold=175msec
INF:gptp:000011-124407:setFollowUp_txFollowUp:domainIndex=0, portIndex=2, fup gap=11125msec tsync_ts_threshold=175msec
INF:gptp:waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=1
INF:gptp:set asCapable for domainIndex=0, portIndex=1
INF:gptp:000011-874779:gptpgcfg_set_asCapable:domainInde=0, portIndex=1, ascapable=1
INF:gptp:000011-999254:setSyncTwoStep_txSync:domainIndex=0, portIndex=1, sync gap=12000msec, tsync_ts_threshold=175msec
INF:gptp:000011-999703:setFollowUp_txFollowUp:domainIndex=0, portIndex=1, fup gap=12000msec tsync_ts_threshold=175msec
log ovflow!
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=2 numRxChannels=1 dmaRxChId=2 nTxPkts=8 nRxPkts=16 pktSize=1536
INF:avtp:avtpc_direct_setup:direct is set: tx=1, rx=0
LF: 6851138459, 6854144659, 6857477614
HF: 6857555319, 6857576154, 6857596984
Waiting for gPTP sync....
INF:avtp:Edge Diff = 14882
WRN:gptp:computePropTime: computed PropTime is out of range = -4295, set 0
WRN:gptp:computePropTime: computed PropTime is out of range = -2169, set 0
Waiting for gPTP sync....
WRN:gptp:computePropTime: computed PropTime is out of range = -583, set 0
WRN:gptp:computePropTime: computed PropTime is out of range = -61, set 0
INF:gptp:set neighborGptpCapable, domainIndex=0, portIndex=2 wtout=24000000000
Waiting for gPTP sync....
EtherRing Host Mac Address: 44:6b:1f:32:ae:89
Configuring stream Index 0 as Talker
Configuring stream Index 1 as Talker
Configuring stream Index 2 as Talker
Subscribing to streamID 00:01:02:03:04:05:01:21
Configuring stream Index 3 as Listener
Registering Mac Address 91:e0:f0:00:fe:21
Subscribing to streamID 00:01:02:03:04:05:01:22
Configuring stream Index 4 as Listener
Registering Mac Address 91:e0:f0:00:fe:22
Subscribing to streamID 00:01:02:03:04:05:01:23
Configuring stream Index 5 as Listener
Registering Mac Address 91:e0:f0:00:fe:23
ERR:avtp:crfApp_spinTalker: Non Consecutive Media Clock Timestamp
ERR:avtp:crfApp_spinTalker: Non Consecutive Media Clock Timestamp
     27.819s : CPU load =  19.53 %
     32.820s : CPU load =  49.64 %
     37.821s : CPU load =  48.32 %
     42.822s : CPU load =  48.57 %
INF:avtp:Registered Callback for streamID:00:01:02:03:04:05:00:13
INF:avtp:Registered Callback for streamID:00:01:02:03:04:05:00:11
INF:avtp:Registered Callback for streamID:00:01:02:03:04:05:00:12
ERR:avtp:crfApp_spinTalker: Non Consecutive Media Clock Timestamp
     47.823s : CPU load =  71.28 %
     52.824s : CPU load =  70.27 %
     57.825s : CPU load =  69.57 %
     62.826s : CPU load =  71.13 %
     67.827s : CPU load =  73.58 %
     72.828s : CPU load =  73.43 %
     77.829s : CPU load =  73.48 %
```
#### Auto Amplifier Log
```
=====================================
       AVB Audio Playback Demo
=====================================

0 - Central Compute Node
1 - Zone Left Node
2 - Zone Right Node
3 - Zone Tail Node
Enter the nodeId :
2
Got Node Id: 2
Acting as Zone Right Node
Enabling clocks!
start to open driver.
EEPROM 0 MAC addr: EEPROM 1 MAC addr: MAC is not fused in eeprom instance number 2, Invalid typeword FF
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:1 From 4 To 2

Init all configs
----------------------------------------------
sitara-cpsw: init config
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 0 is alive
PHY 3 is alive
initQs() txFreePktInfoQ initialized with 18 pkts
MAC port addr: 44:6b:1f:2c:2d:2b
sitara-cpsw: default RX flow started
Uniconf/ModuleInit time= 733/4253 us
log ovflow!
INF:ubase:GPTP_MEDIUM_ALLOC: fragsize=16 fragused/fragnum=865/944 (91%)
INF:ubase:GPTP_SMALL_ALLOC: fragsize=4 fragused/fragnum=19/74 (25%)
INF:ubase:SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100%)
EnetApp_initTsn:TSN app start done!
CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
log ovflow!
cb_lld_task_create: avtpcrx_tilld0 stack_size=8192
INF:uconf:uc_dbal_setproc:l2
INF:avtp:rxethernet_setup:rxethernet_setup is done
INF:avtp:avtpc_direct_setup:direct is set: tx=0, rx=1
INF:avtp:ll_avtpe_receive_data: enable Rx Zero-Copy
Wait for Linkup......
EnetCbsApp_registerCbsEnableToUniconf: succeeded

ask uniconf to write adminIdleSlop succeeded

INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=7, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
Registered adminIdleSlope finished. tc=7
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=6
log ovflow!
get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=6, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=5
ask uniconf to write adminIdleSlop succeeded

log ovflow!
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=4, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
Registered adminIdleSlope finished. tc=4
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=3
INF:uconf:respond_getnotice:a notice with a deletion
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=3, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=2
ask uniconf to write adminIdleSlop succeeded

log ovflow!
INF:uconf:ydbi_get_item_ifk3vk0:no data
ERR:uconf:get_tc_cbs_parameters:tilld0, speed is 0, Link may Down
ERR:uconf:update_cbs_idle_slope:tc=1, no cbs parameters
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
Registered adminIdleSlope finished. tc=1
ask uniconf to write adminIdleSlop succeeded

Registered adminIdleSlope finished. tc=0
INF:uconf:respond_getnotice:a notice with a deletion
ERR:uconf:uc_hwal_writehw:error in ietf_interfaces
EnetCbsApp_registerCbsEnableToUniconf: succeeded

Configured CBS


INF:uconf:respond_getnotice:a notice with a deletion
INF:uconf:create_semname_with_dbname:null dbname is specified.
INF:uconf:get_queue_map_params:netdev=tilld0, num_tc=0
Wait for Linkup......
Wait for Linkup......
Wait for Linkup......
Wait for Linkup......
Wait for Linkup......
Cpsw_handleLinkUp:1423
MAC Port 2: link up
INF:cbase:000009-229694:cbl_query_response:tilld1: link UP, speed=1000, duplex=1 !!!! (90us since link change event)
INF:gptp:index=2 speed=1000, duplex=full
INF:gptp:set neighborGptpCapable, domainIndex=0, portIndex=2 wtout=24000000000
Wait for Linkup......
Cpsw_handleLinkUp:1423
MAC Port 1: link up
INF:cbase:000009-829601:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!! (75us since link change event)
INF:gptp:index=1 speed=1000, duplex=full
INF:gptp:set neighborGptpCapable, domainIndex=0, portIndex=1 wtout=24000000000
Wait for Linkup......
WRN:gptp:000010-249268:waiting_for_pdelay_interval_timer_proc:portIndex=2, sourcePortIdentity=44:6B:1F:FF:FE:2C:2E:4A, thisClock=44:6B:1F:FF:FE:2C:2D:2B, neighborPropDelay=442
INF:gptp:waiting_for_pdelay_interval_timer_proc:portIndex=2, not asCapable
WRN:gptp:000010-874366:waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=44:6B:1F:FF:FE:32:AE:89, thisClock=44:6B:1F:FF:FE:2C:2D:2B, neighborPropDelay=445
INF:gptp:waiting_for_pdelay_interval_timer_proc:portIndex=1, not asCapable
log ovflow!
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:000011-249639:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000011-374089:setSyncTwoStep_txSync:domainIndex=0, portIndex=2, sync gap=11375msec, tsync_ts_threshold=175msec
INF:gptp:000011-374207:setFollowUp_txFollowUp:domainIndex=0, portIndex=2, fup gap=11375msec tsync_ts_threshold=175msec
INF:gptp:waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=1
INF:gptp:set asCapable for domainIndex=0, portIndex=1
INF:gptp:000011-874461:gptpgcfg_set_asCapable:domainInde=0, portIndex=1, ascapable=1
log ovflow!
INF:gptp:000012-055606:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-551008215nsec
INF:gptp:gptpmasterclock_init: tsn_gptp-1.2.3, ref_counter=2
INF:avtp:avtpc_init: l2-1.2.3
LF: 7284784135, 7287650984, 7290983940
HF: 7291059980, 7291080815, 7291101645
Waiting for gPTP sync....
INF:avtp:Edge Diff = 13218
INF:gptp:domainIndex=0, clock_master_sync_receive:stable rate
INF:gptp:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-551007148
INF:gptp:set_phase_offsetGM:domainIndex=0, stable
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=2
INF:gptp:000014-749059:gm_stable:gm_stable_proc:domainIndex=0
Waiting for gPTP sync....
Waiting for gPTP sync....
EtherRing Host Mac Address: 44:6b:1f:2c:2d:2b
Subscribing to streamID 00:01:02:03:04:05:01:01
Configuring stream Index 0 as Listener
Registering Mac Address 91:e0:f0:00:fe:01
Configuring stream Index 3 as Talker
     27.623s : CPU load =   8.68 %
     32.625s : CPU load =  16.81 %
     37.626s : CPU load =  16.89 %
     42.627s : CPU load =  16.87 %
     47.628s : CPU load =  27.74 %
     52.629s : CPU load =  28.00 %
     57.630s : CPU load =  28.13 %
     62.631s : CPU load =  28.00 %
```
## Troubleshooting

- **No Audio:** Ensure the audio source is properly connected and powered on. Verify that the PHY link is established and that the logs are similar to those shown in the previous section.

## See Also

[Ethernet And Networking](../../components/networking/networking.rst) |
[Ethernet AVB Stack - API and Integration Guide](../../components/networking/enet_cpsw_avtp_apiguide.md)
