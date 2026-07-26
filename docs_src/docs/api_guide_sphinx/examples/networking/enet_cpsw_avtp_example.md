# Ethernet AVTP Example

## Introduction

::::{only} SOC_AM62DX
:::{note}
This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
:::
::::

This ethernet AVTP example illustrates the usage of IEEE Std 1722™-2016 stack with CPSW peripheral.

In this example, the DUT MAC port is connected to a PC which can act as either AVTP Talker or AVTP Listener. In the talker example, the DUT sends
audio stream in AVTP PCM format to PC, where PC logs the received PCM data in a output file. In the listener example, the PC streams the Audio from an input file and DUT receives the Audio data and prints the info to the console. Yang based configuration is also supported in the stack, However file System is not supported yet, hence full yang based support will be added in the future releases.

## Supported Combinations

::::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/tsn/aafpcmlistener_app, aafpcmtalker_app

::::

::::{only} SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/tsn/aafpcmlistener_app, aafpcmtalker_app

::::

## Prerequisites
- EVM Board
- Cat6 ethernet cable
- PC with Linux Ubuntu OS with wireshark, xl4 deb build installed.
- ffplay on PC (Optional, can be used to listen to recorded audio)

## Steps to Run the Example

### To start AVB app on PC, follow below steps:
- Create a workspace to run avtp app.
```
$ mkdir avbrun_demo && cd avbrun_demo
$ avbrun -w rnn-cl -d enp3s0 -o setcaps=1
```
- This creates a file named **`avbrun.cfg`**. open the file and modify [DEFAULT] field, `uniconf_conf = uniconf.conf,streaminfo.conf`

- To use Excelfore avbrun as talker, modify `avbrun.cfg` to read/send AVTP data from wav file
```
[Talker] `conl2t_extops: conl2t_extops = --src afile --mfile file_example_WAV_10MG.wav
```

- To read/send AVTP data from wav file, modify this line in `avbrun.cfg`
```
conl2t_extops = --src afile --mfile BeepBeep.pcm --conf conl2_talker.conf -C 2 -P 180 -F s16be
```
 Argument       | Description
 ---------------|-----------
 -C             | Channel number
 -F             | Format audio 16be
 -P             | Number of sample per frame

- To read/send AVTP data from ec3 file, modify this line in `avbrun.cfg`
```
conl2t_extops = --src afile --format aes32 --mfile in.ec3
```

- To use Excelfore avbrun as listener and dump the output in PCM format, modify this line in `avbrun.cfg`
```
[Listener] conl2t_extops: conl2l_extops = --sink afile --mfile output.pcm -C 2 -F s16be
```

- To dump the output in EC3 format, modify this line in `avbrun.cfg`
```
`conl2l_extops = --sink afile --mfile out.ec3 --sync-audio-file-type 2`: Dump to ec3 file
```

- To play output.pcm `ffplay -f s16be -ar 48k -ac 2 output.pcm`.

- Create a file with name `streaminfo.conf` and paste the contents mentioned below.
  In xl4 deb pakages from 7.0.7 version, there is new configuration file added to conl2 test app to check for stream information. Prepare streaminfo.conf with below content, replace **eno1** with the name of your network device and replace all instances of `stream-id:00-01-02-03-04-05:00-02` with your stream ID, This stream-id can be kept unchanged for the existing examples.
```
/ieee802-dot1q-cnc-config/cnc-config/domain|domain-id:domain00|/cuc|cuc-id:br0|/stream|stream-id:00-01-02-03-04-05:00-02|/talker/end-station-interfaces|mac-address:00-01-02-03-04-05|interface-name:eno1|/accept 1
/ieee802-dot1q-cnc-config/cnc-config/domain|domain-id:domain01|/cuc|cuc-id:br0|/stream|stream-id:00-01-02-03-04-05:00-02|/listener|index:0|/end-station-interfaces|mac-address:00-01-02-03-04-05|interface-name:eno1|/accept 1
/ieee802-dot1q-cnc-config/cnc-config/domain|domain-id:domain00|/cuc|cuc-id:br0|/stream|stream-id:00-01-02-03-04-05:00-02|/talker/stream-rank/rank 1
../data-frame-specification|index:0|/ieee802-mac-addresses/destination-mac-address 91-E0-F0-00-FE-00
source-mac-address 00-01-02-03-04-05
../ieee802-vlan-tag/priority-code-point 3
vlan-id 110
/ieee802-dot1q-cnc-config/cnc-config/domain|domain-id:domain00|/cuc|cuc-id:br0|/stream|stream-id:00-01-02-03-04-05:00-02|/talker/traffic-specification/
max-frames-per-interval 1
max-frame-size 1400
interval/numerator 1
denominator 8000
/ieee802-dot1q-cnc-config/cnc-config/domain|domain-id:domain01|/cuc|cuc-id:br0|/stream|stream-id:00-01-02-03-04-05:00-02|/listener|index:0|/interface-configuration/interface-list|mac-address:00-01-02-03-04-05|interface-name:eno1|/config-list|index:0|/ieee802-mac-addresses/destination-mac-address 91-E0-F0-00-FE-00
source-mac-address 00-01-02-03-04-05
../ieee802-vlan-tag/priority-code-point 3
vlan-id 110
```

- Create `uniconf.conf` file in the same folder and paste the following contents. Replace `eno1` with the name of your network device.
```
/ietf-interfaces/interfaces/interface|name:eno1|/enabled true
```

- For Talker, Create `conl2_talker.conf` and paste the following contents.
```
/xl4-extmod/xl4conl2/CONL2_INSTANCE|INSTANCE_INDEX:0|/
CONF_NOSYNC false
CONF_AVTPD_BUFFTIME_MSEC 1000
CONF_SEND_AHEADTS_USEC 20000
CONF_AUDIO_PAYLOAD_TYPE "aaf"
CONF_ECHOBACK false
CONF_DROPLATE false
CONF_SINK_DEVICE_NAME  ""
CONF_SOURCE_AUDIO_CHANNELS  2
CONF_SOURCE_AUDIO_RATE  48000
CONF_SINK_FILE_NAME ""
CONF_SOURCE_FILE_NAME ""
CONF_SOURCE_WAVE_FREQ 500
CONF_SOURCE_AUDIO_SAMPLES 180
CONF_TSOFFSET_USEC 200000
CONF_AUDIO_LITTLE false
CONF_GPTP_SHMEM "/gptp_mc_shmeno1"
CONF_SHMEM_SUFFIX "avmt"
CONF_MEDIA_SOURCE "sinwave"
CONF_SOURCE_AUDIO_FORMAT "s24be"
```

- For Listener, Create `conl2_listener.conf` and paste the following contents.
```
/xl4-extmod/xl4conl2/CONL2_INSTANCE|INSTANCE_INDEX:1|/
CONF_NOSYNC false
CONF_AVTPD_BUFFTIME_MSEC 1000
CONF_SEND_AHEADTS_USEC 20000
CONF_AUDIO_PAYLOAD_TYPE "aaf"
CONF_ECHOBACK false
CONF_DROPLATE false
CONF_SINK_DEVICE_NAME  ""
CONF_SOURCE_AUDIO_CHANNELS  2
CONF_SOURCE_AUDIO_RATE  48000
CONF_SINK_FILE_NAME ""
CONF_SOURCE_FILE_NAME ""
CONF_SOURCE_WAVE_FREQ 500
CONF_SOURCE_AUDIO_SAMPLES 180
CONF_TSOFFSET_USEC 200000
CONF_AUDIO_LITTLE false
CONF_GPTP_SHMEM "/gptp_mc_shmeno1"
CONF_SHMEM_SUFFIX "avml"
CONF_SINK_AUDIO_FILE_TYPE "1"
CONF_MEDIA_SINK "aplay"
CONF_SOURCE_AUDIO_FORMAT "s24be"
```

- To start the AVB Talker
```
avbrun -r talker
```
- To start the AVB Listener
```
avbrun -r listener
```

### Build the example

Refer [Enet CPSW TSN gPTP Examples](enet_cpsw_tsn_gptp.md) to build the avtp examples.

### HW Setup

Refer [Enet CPSW TSN gPTP Examples](enet_cpsw_tsn_gptp.md) for HW Setup.

### Create a network between EVM and host PC
EVM and PC has to be connected directly as shown below using CAT6 or CAT5 cable

:::{figure} ../../images/networking/gptp_topology_evm_pc.png
:width: 30%
Local network between PC and EVM
:::

PORT1 instead of PORT0 on EVM can be used as well.

### Run the example

:::{attention}
If you need to reload and run again, a CPU power-cycle is MUST
:::

Refer to the AVTP API guide for how to configure AVTP parameters.

### AVTP verification

#### DUT as pcmaaf_talker
Flash binary in {{ VAR_BOARD_NAME_LOWER }} and start it.

On the PC side, configure avbrun as conl2 listener(pcm) and start `avbrun -r listener`.

The log on DUT side should be printed:
```
INF:avtp:audio talker sent: 200.000000(packets/sec), 1.536000(mbps)
INF:avtp:audio talker sent: 200.000595(packets/sec), 1.536005(mbps)
INF:avtp:audio talker sent: 199.999786(packets/sec), 1.535998(mbps)
INF:avtp:audio talker sent: 200.000000(packets/sec), 1.536000(mbps)
```

On PC side, after running for a while, stop avbrun and confirm output.pcm is created.
Play the file with `ffplay -f s16be -ar 48k -ac 2 output.pcm`, the audio should be heard from speaker.

#### Verification DUT as pcmaaf_listener
Flash binary in aafpcm_listener and start it.

On the PC side, configure avbrun as conl2 talker(pcm) and start `avbrun -r talker`.

On the DUT side, correct pcm info including bitdepth, channels, format and data rate should be printed.

```
[RX 00:01:02:03:04:05:00:02] Rp#8 Mbps(1.536034, 1.536804) Delay(-23487, -11303894, -17810) Pkt(2413, 0, 0)
IFV:gptp:000369-441329:domainIndex=0, clock_master_sync_receive:the master clock rate to 97579ppb, GMdiff=-6nsec
IFV:gptp:000369-565787:domainIndex=0, clock_master_sync_receive:the master clock rate to 97429ppb, GMdiff=-72nsec
IFV:gptp:000369-690810:domainIndex=0, clock_master_sync_receive:the master clock rate to 97675ppb, GMdiff=46nsec
IFV:gptp:000369-817439:domainIndex=0, clock_master_sync_receive:the master clock rate to 97486ppb, GMdiff=-44nsec
IFV:gptp:000369-940807:domainIndex=0, clock_master_sync_receive:the master clock rate to 97839ppb, GMdiff=117nsec
IFV:gptp:000370-065716:domainIndex=0, clock_master_sync_receive:the master clock rate to 97623ppb, GMdiff=8nsec
```

## See Also

[Networking Examples](../examples_networking.rst)
