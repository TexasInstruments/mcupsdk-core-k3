# Ethernet AVB Audio Playback Demo

## Introduction
This example demonstrates audio playback over Ethernet AVB (Audio Video Bridging) using the eAVB stack. The setup involves two devices: a Central Compute and an Auto Amplifier. Audio captured from each device is transmitted over the network using eAVB protocol, allowing both devices to play back audio recorded from the other. The eAVB stack ensures synchronized, low-latency audio streaming in both directions, showcasing real-time audio transport and playback between the Central and Amplifier units.

Both Central Compute and Auto Amplifier handle presentation time via AVTP presentation-time offset (`PRESENTATION_TIME_OFFSET_NS`, 750000 ns / 0.75 ms). The media‑clock edge count from McASP callbacks maps to a gPTP timestamp indicating when each audio sample must be rendered onto the physical output wire. An AVTP presentation‑time offset is added to this timestamp, enabling *timestamp‑gated rendering*: audio buffers are held until the calculated presentation time, guaranteeing exact output timing. This mechanism maintains constant latency for use‑cases such as active noise cancellation (ANC).

See also [Ethernet AVB Stack - API and Integration Guide](../../components/networking/enet_cpsw_avtp_apiguide.md)

### Presentation‑time design
- Presentation time is the gPTP timestamp at which an audio sample must be rendered onto the physical hardware output wire.
- Audio sampling timestamp ensures constant latency for use‑cases such as active noise cancellation (ANC).
- Timestamp‑gated rendering holds audio samples until the calculated presentation time, guaranteeing exact output timing.

### Media Clock Recovery Mechanism
The demo uses a dedicated McASP to derive a 300 Hz signal from the same main clock source (CDCE) that generates the 48 kHz media clock. Both clocks are related since they derive from the same source. Using CDCE frequency control and a PID controller, both frequency and phase synchronization are achieved. Feeding 48 kHz directly to CPTS would cause excessive CPU load, so the 300 Hz signal is used for efficient timestamping.

```{figure} ../../images/networking/cdce_mcr.png
:align: center
:width: 50%

Media Clock Recovery Mechanism
```

### Synchronizing Starts
At start‑up, the first edge of the 48 kHz media clock is timestamped to calculate the edge difference. Thereafter, the 300 Hz signal edges are timestamped to extrapolate any media‑clock edge timestamp.

![Synchronizing Starts](../../images/networking/pres_time_sync.png)

### Edge Timestamp Calculation
The media‑clock timestamp for edge $ N $ is calculated from the 300 Hz edge timestamp:

- $ N  $– Media‑clock edge count for which timestamp is needed
- $ N_t $ – 300 Hz edge count for which timestamp is obtained
- $ T_{st} $ – 300 Hz timestamp for $N_t$ edge
- $ T_{mc} $ – Media‑clock timestamp of $N$‑th edge
- $ T_{io} $ – Initial offset between media‑clock edge and 300 Hz edge
- $ P  $– Media‑clock period

```{math}
T_{mc} = (N - N_t) \times P + (T_{st} - T_{io})
```

### Talker Presentation‑time Handling
The talker (Central Compute) captures audio, timestamps it using the media‑clock edge count, adds the presentation‑time offset, and transmits the AVTP packet with the presentation time.

![Talker Presentation Time Handling](../../images/networking/pres_time_talker.png)

### Listener Presentation‑time Handling
The listener (Auto Amplifier) receives the AVTP packet, extracts the presentation time, and uses the index‑aware circular buffer to hold the audio samples until the calculated presentation time for gated rendering.

![Listener Presentation Time Handling](../../images/networking/pres_time_listener.png)

### Index‑Aware Circular Buffer
The index‑aware circular buffer retains sequence information of audio samples, necessary for synchronous playback. The producer can put samples at any index; the consumer can request samples from any index. This maintains synchronization and is resilient to sample losses while preserving absolutely constant jack‑to‑jack latency.

## Supported Combinations

:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos, c75ss0-0_freertos
 Toolchain      | ti-arm-clang, ti-c7000
 Board          | {{ VAR_BOARD_NAME_LOWER }}-dp83tg721, {{ VAR_BOARD_NAME_LOWER }}-dp83867
 Example folder | source/networking/enet/core/examples/tsn/aafpcm_audio_demo/central_compute, auto_amplifier

:::

## Prerequisites
- 2 x EVM boards with DP83TG721 Add-on PHY or DP83867 Add-on PHY.
- CAT6 or Automotive Ethernet Cable.
- Earphones with 3.5mm Jack.
- 3.5mm Aux Cable
- An Audio Source, can be a PC/Laptop or a Mobile Phone with 3.5mm Jack.

### HW Setup

![](../../images/networking/am275_b2b_setup.png)

- Connect Audio Input to J1 Top, Connect Earphone Jack to J4 Top on the other EVM.

## Overview

![](../../images/networking/demo1_overview.png)

## Demo Configuration Parameters

| Parameter                     | Description         |
|-------------------------------|---------------------|
| Number of Channels            | 8                   |
| Sample Rate (Media Clock Freq)| 48 kHz              |
| Bit Depth                     | 32 bits             |
| McASP Transaction Size        | 16 Samples          |
| Samples Per AVTPDU            | 6 Samples           |
| AVB Transaction Frequency     | 8000 Hz (125 µs)    |
| McASP Transaction Frequency   | 8000 Hz (125 µs)    |
| AVTP Packet Length            | 243 Bytes           |

## Performance

For the Performance of this Demo, Refer to the [Performance of Ethernet AVB](../../components/networking/enet_lld/eavb_performance.md).

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

- Load both the Central Compute and Auto Amplifier applications onto the EVMs, starting each application one after the other. On the Central Compute EVM, make sure to load both the C7x and R5 binaries.
- Wait about 15 seconds. Audio playback will start and should be audible if the audio input is properly connected.

#### Central Compute Log
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
EnetPhy_bindDriver:1943 
Open MAC port 2
EnetPhy_bindDriver:1943 
PHY 0 is alive
PHY 3 is alive
sitara-cpsw: Create RX task for regular traffic 
initQs() txFreePktInfoQ initialized with 4 pkts
MAC port addr: 44:6b:1f:32:ae:89
sitara-cpsw: default RX flow started
Uniconf/ModuleInit time= 799/4304 us
EnetApp_initTsn:TSN app start done!
log ovflow!
log ovflow!
INF:ubase:SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100%)
CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
log ovflow!
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=2 numRxChannels=1 dmaRxChId=2 nTxPkts=16 nRxPkts=8 pktSize=1536
INF:cbase:rxChId 2 has owner dmaRxShared 0
log ovflow!
avtpc_direct_setup:direct is set: tx=0, rx=1
Cpsw_handleLinkUp:1423 
MAC Port 1: link up
log ovflow!
      5. 65s : CPU load =   4.54 %
Link is Stable...
Clock Started...
INF:avtp:Calculated Edge Difference = -35195
     10. 66s : CPU load =  20.04 %
     15. 67s : CPU load =  24.52 %
     20. 68s : CPU load =  24.72 %


```
#### Auto Amplifier Log
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
EnetPhy_bindDriver:1943 
Open MAC port 2
EnetPhy_bindDriver:1943 
PHY 0 is alive
PHY 3 is alive
sitara-cpsw: Create RX task for regular traffic 
initQs() txFreePktInfoQ initialized with 4 pkts
MAC port addr: 44:6b:1f:2c:2d:2b
sitara-cpsw: default RX flow started
Uniconf/ModuleInit time= 792/4317 us
EnetApp_initTsn:TSN app start done!
log ovflow!
log ovflow!
INF:ubase:SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100%)
CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
log ovflow!
INF:cbase:rxChId 2 has owner dmaRxShared 0
log ovflow!
avtpc_direct_setup:direct is set: tx=0, rx=1
Cpsw_handleLinkUp:1423 
MAC Port 1: link up
INF:cbase:000004-242920:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!! (145us since link change event)
WRN:gptp:000004-280200:waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=44:6B:1F:FF:FE:32:AE:89, thisClock=44:6B:1F:FF:FE:2C:2D:2B, neighborPropDelay=442
INF:avtp:di=0, GM is stable. Adjust messages interval now
      5. 64s : CPU load =   5.55 %
Link is Stable...
Clock Started...
INF:avtp:Calculated Edge Difference = -134836
INF:avtp:phase_err_ns:0.000000,freq_err_ppm:0.000000,stage_elapsed_us:0,freq_fine:0,phase_fine:0
INF:avtp:phase_err_ns:-1527.829294,freq_err_ppm:-1.293099,stage_elapsed_us:826485,freq_fine:0,phase_fine:0
INF:avtp:phase_err_ns:510.648865,freq_err_ppm:0.926200,stage_elapsed_us:826471,freq_fine:1,phase_fine:0
     10. 65s : CPU load =  18.64 %
INF:avtp:phase_err_ns:302.791209,freq_err_ppm:0.114778,stage_elapsed_us:1859638,freq_fine:1,phase_fine:0
INF:avtp:phase_err_ns:190.340999,freq_err_ppm:0.075654,stage_elapsed_us:2789455,freq_fine:1,phase_fine:0
INF:avtp:phase_err_ns:113.252282,freq_err_ppm:0.037879,stage_elapsed_us:3822533,freq_fine:1,phase_fine:0
INF:avtp:phase_err_ns:86.703892,freq_err_ppm:0.035895,stage_elapsed_us:4855680,freq_fine:1,phase_fine:0
INF:avtp:phase_err_ns:55.962021,freq_err_ppm:-0.063701,stage_elapsed_us:5785499,freq_fine:1,phase_fine:1
     15. 66s : CPU load =  31.70 %
INF:avtp:phase_err_ns:152.735821,freq_err_ppm:-0.047165,stage_elapsed_us:6818665,freq_fine:1,phase_fine:1
INF:avtp:phase_err_ns:144.934868,freq_err_ppm:0.031697,stage_elapsed_us:7851742,freq_fine:1,phase_fine:1
INF:avtp:phase_err_ns:141.207333,freq_err_ppm:-0.006721,stage_elapsed_us:8886563,freq_fine:1,phase_fine:1
INF:avtp:phase_err_ns:115.835011,freq_err_ppm:0.045094,stage_elapsed_us:9814706,freq_fine:1,phase_fine:1
INF:avtp:phase_err_ns:89.470468,freq_err_ppm:0.042644,stage_elapsed_us:10847874,freq_fine:1,phase_fine:1
     20. 67s : CPU load =  31.92 %
INF:avtp:phase_err_ns:61.303666,freq_err_ppm:-0.009539,stage_elapsed_us:11880952,freq_fine:1,phase_fine:1
INF:avtp:phase_err_ns:67.348672,freq_err_ppm:0.028797,stage_elapsed_us:12810769,freq_fine:1,phase_fine:1
INF:avtp:phase_err_ns:30.575313,freq_err_ppm:0.020218,stage_elapsed_us:13843916,freq_fine:1,phase_fine:1
```
## Troubleshooting

- **No Audio:** Ensure the audio source is properly connected and powered on. Verify that the PHY link is established and that the logs are similar to those shown in the previous section.
- **No Link:** If you are using the DP83TG721 PHY, refer to the Troubleshooting section in [Ethernet AVB Multistream Media Clock Recovery](enet_cpsw_tsn_media_clock_recovery.md).

## Integration Guidelines

This section provides detailed steps to integrate AVB Talker or Listener functionality into an audio-only C7x application.

### 1. Compilation Requirements

**Include paths to add:**
```
<SDK_INSTALL_PATH>/source/networking/tsn/tsn-stack/tsn_avb/avb_if
<SDK_INSTALL_PATH>/source/networking/tsn/tsn-stack/tsn_avb/shm_cirbuf
<SDK_INSTALL_PATH>/source/networking/tsn/tsn-stack/tsn_avb/clock_recovery
<SDK_INSTALL_PATH>/source/networking/tsn/tsn_unibase
<SDK_INSTALL_PATH>/source/networking/tsn/tsn_combase
<SDK_INSTALL_PATH>/source/networking/tsn/tsn-stack/eval_src/tsn_conl2
<SDK_INSTALL_PATH>/source/networking/tsn/tsn_gptp
```

**Libraries to link (in order):**
- `avb_if-freertos.<SOC>.<core>.<toolchain>.lib` — AVB talker/listener registration and transmit task
- `shm_idxbuf-freertos.<SOC>.<core>.<toolchain>.lib` — Index-aware shared-memory circular buffer
- `clock_rec-freertos.<SOC>.<core>.<toolchain>.lib` — Media clock recovery (frequency + phase sync)
- `crf_task-freertos.<SOC>.<core>.<toolchain>.lib` — Clock Reference Frame task for clock recovery transport
- `gptpmasterclock-freertos.<SOC>.<core>.<toolchain>.lib` — gPTP master clock proxy/time expansion
- `unibase-freertos.<SOC>.<core>.<toolchain>.lib` — Platform-independent utilities
- `combase-freertos.<SOC>.<core>.<toolchain>.lib` — Communication utilities (sockets, mutexes, semaphores)
- `conl2-freertos.<SOC>.<core>.<toolchain>.lib` — Evaluation library implementing IEEE 1722 AVTP
- `yangemb-freertos.<SOC>.<core>.<toolchain>.lib` — YangDB licensing library (1-hour limit for AVTP)

**Source files to compile (if building from source):**
- `avb_if/avb_if.c`
- `shm_cirbuf/shm_idxbuf.c`
- `clock_recovery/clock_rec.c`
- `clock_recovery/crf_task.c`
- `clock_recovery/clock_hw.c`
- `clock_recovery/clock_rec_priv.c`
- `tsn_conl2/aaf_avtpc_talker.c`
- `tsn_conl2/aaf_avtpc_listener.c`
- `tsn_conl2/conl2*.c` (AVTP stack sources)

### 2. Memory Allocation Requirements

**Shared-Memory Rings (SHM):**
- Each talker stream: `ShmIdxBuf_getRequiredSize(capacityFrames, frameSize)` bytes
- Each listener stream: same formula
- `frameSize = (bit_depth / 8) * channels` (e.g., 32-bit × 8 channels = 32 bytes/frame)
- Demo uses 16-sample frames at 48 kHz → 125 µs interval → 6 samples per AVTPDU
- Ring capacity: typically 100–200 ms of audio (e.g., 4800–9600 frames at 48 kHz)

**HW Spinlocks:**
- Each SHM region requires a unique HW spinlock number (`lockNumber` in config)
- Must not conflict with any other concurrently accessed SHM region
- Base address: `CSL_SPINLOCK0_BASE`

**AVB Talker Task Stack:**
- Default: 8 KB (`AVB_IF_TASK_STACK_SIZE_DEFAULT`)
- Priority: 16 (`AVB_IF_TASK_PRIORITY_DEFAULT`) — **must be lower (numerically higher) than gPTP task**

**Statistics Logging Task (optional):**
- Stack: 2 KB, Priority: 4, Period: 100 ms
- Started lazily on first `statsLogEnable=true` registration

### 3. Media Clock Recovery Integration

The media clock recovery library (`clock_rec`) is a standalone component. Include for linking:
- Header: `clock_rec.h`
- Source: `clock_rec.c`, `crf_task.c`, `clock_hw.c`

**Key APIs:**
- `CrfTask_create(&params)` — Starts clock recovery task (role: TALKER or LISTENER)
- `ClockRec_getMediaClockTimestamp(edgeIndex)` — Convert media-clock edge to gPTP time
- `ClockRec_getMediaClockEdgeCount(gptpTime)` — Convert gPTP time to media-clock edge
- `ClockRec_clockStartedHook()` — Application implements: called when HW bootstrap complete
- `ClockRec_needsRestartHook()` — Application implements: advisory restart heuristic

**Clock Source Configuration:**
- CDCE-based: `clkSrc = CLOCK_REC_SOURCE_CDCE` (derives 300 Hz from 48 kHz master clock)
- PHY-based: `clkSrc = CLOCK_REC_SOURCE_PHY`
- Correction flags: `CLOCK_REC_CORRECT_FREQUENCY | CLOCK_REC_CORRECT_PHASE`
- Parent clock frequency: 48000 Hz (media clock)
- Timestamp interval: 160 (300 Hz → 3.33 ms period)

### 4. Registering Talker and Listener Streams

**Talker Registration:**
```c
AvbIf_TalkerConfig talkerCfg = {
    .netdev                = "tilld0",
    .streamID              = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01},
    .destMacAddr           = {0x91, 0xE0, 0xF0, 0x00, 0xFE, 0x01},
    .vlanID                = 110,
    .priority              = 3,                    // VLAN PCP
    .timeInterval_us       = 125,                  // Must be multiple of 125 µs
    .pcminfo               = {.format = AVBTP_AAF_FORMAT_INT_32BIT,
                               .channels = 8, .bit_depth = 32, .srate = 48000},
    .shmAddr               = <peer-initialized SHM ring base>,
    .capacityFrames        = <ring depth in frames>,
    .lockNumber            = <unique HW spinlock number>,
    .presentationOffset_ns = 750000,               // 0.75 ms presentation-time offset (750000 ns)
    .statsLogEnable        = false,
};

AvbIf_TalkerHandle talkerHandle;
status = AvbIf_registerTalker(&talkerCfg, &talkerHandle);
```

**Listener Registration (two-step):**
```c
// Step 1: Initialize shared listener socket (once per application)
AvbIf_ListenerNetConfig listenerNetCfg = {
    .netdev          = "tilld0",
    .destMacAddr     = {0x91, 0xE0, 0xF0, 0x00, 0xFE, 0x01},
    .vlanID          = 110,
    .priority        = 3,
    .timeInterval_us = 125,
};
status = AvbIf_initListenerTask(&listenerNetCfg);

// Step 2: Register each listener stream
AvbIf_ListenerConfig listenerCfg = {
    .streamID        = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02},
    .pcminfo         = {.format = AVBTP_AAF_FORMAT_INT_32BIT,
                         .channels = 8, .bit_depth = 32, .srate = 48000},
    .timeInterval_us = 125,
    .shmAddr         = <peer-initialized SHM ring base>,
    .capacityFrames  = <ring depth in frames>,
    .lockNumber      = <unique HW spinlock number>,
    .statsLogEnable  = false,
};

AvbIf_ListenerHandle listenerHandle;
status = AvbIf_registerListener(&listenerCfg, &listenerHandle);
```

**Listener Stream Dispatch:**
- The full 8-byte `streamID` is the key of a hash table (`AVB_IF_LISTENER_HASH_SIZE = 32` buckets) that maps each arriving packet to its registered stream
- All registered listener streams **must have a distinct `streamID`**; compile-time limit is `AVB_IF_MAX_LISTENERS = 10`
- Each stream has its own RX callback: set `AvbIf_ListenerConfig.rxCallback` (+ `rxCallbackArg`) to handle that stream's packets yourself, or leave it `NULL` to use the built-in callback that writes into the SHM ring (then `pcminfo`, `timeInterval_us` and the SHM fields are required)
- CRF (clock recovery) packets with subtype `AVBTP_SUBTYPE_CRF` are automatically forwarded to `CrfTask_rxCallback()` — they do not occupy a listener slot

**Talker Limits:**
- `AVB_IF_MAX_TALKERS = 4` (compile-time)
- PDU size must not exceed `AVB_IF_MAX_PDU_BYTES = 15360` bytes (10 × 1536)

### 5. Task Scheduling and Timer Integration

**AVB Talker Task:**
- Created internally by `AvbIf_initListenerTask()` (call once before any `registerTalker()`)
- Task name: `"AvbTalkerTask"`, Priority: 16, Stack: 8 KB
- Blocks on a counting semaphore (`AvbIf_tickSem`)
- **Application must provide a periodic timer callback** that posts this semaphore

**Timer Callback Setup (in SysConfig or code):**
```c
// In .syscfg: CONFIG_TIMERx.timerCallback = "AvbIf_talkerTickCallback"
// Or register manually:
TimerP_Params timerParams;
TimerP_Params_init(&timerParams);
timerParams.period      = 125;              // microseconds (must match timeInterval_us)
timerParams.timerMode   = TimerP_MODE_PERIODIC;
timerParams.timerCallback = AvbIf_talkerTickCallback;
TimerP_construct(&timerObj, &timerParams);
TimerP_start(&timerObj);
```

**Critical Priority Ordering:**
- gPTP task (tsn_gptp): priority 2 (`GPTP_TASK_PRIORITY`) — highest priority
- CRF task: priority 8 (`CRF_TASK_PRIORITY_DEFAULT`)
- ClockSync tick task: priority 10 (between CRF and AVB)
- AVB talker task: priority 16 (`AVB_IF_TASK_PRIORITY_DEFAULT`)
- Statistics task: priority 4 (lowest)

**Initialization Sequence:**
```c
// 1. Wait for gPTP to initialize
while (gptpmasterclock_init(NULL)) { ClockP_usleep(100000); }

// 2. Start Clock Recovery (CrfTask) — waits for link/gPTP internally
status = CrfTask_create(&crfTaskParams);
DebugP_assert(status == SystemP_SUCCESS);

// 3. Initialize AVB talker task
status = AvbIf_initListenerTask();
DebugP_assert(status == SystemP_SUCCESS);

// 4. Register talker/listener streams
status = AvbIf_registerTalker(&talkerCfg, &talkerHandle);
status = AvbIf_initListenerTask(&listenerNetCfg);
status = AvbIf_registerListener(&listenerCfg, &listenerHandle);

// 5. Wait for link stability
while (!link_stable) { ClockP_usleep(100000); }

// 6. Wait for clock recovery to complete bootstrap
SemaphoreP_pend(&clockStartedSem, SystemP_WAIT_FOREVER);

// 7. Initialize ClockSync (gPTP-proxied time for presentation timestamps)
ClockSyncApp_init();

// 8. Start audio McASP transfers
MCASP_startTransferTx(...);
MCASP_startTransferRx(...);
```

**Presentation-Time Offset:**
- Constant added to media-clock timestamp to form AVTP presentation time
- Demo value: `750000 ns` (0.75 ms) — allows buffer to absorb network jitter
- Talker: `presentationTime = ClockRec_getMediaClockTimestamp(edgeIndex) + offset`
- Listener: `edgeIndex = ClockRec_getMediaClockEdgeCount(presentationTimeGptp)`

**ClockSync (gPTP Proxy Time):**
- Application implements `AvbIf_getGptpProxyTime()` → calls `ClockSync_getCurrentTimeNs()`
- `ClockSync_tick()` must run periodically (100 µs default) from a timer ISR → task
- See `clocksync.h` / `clocksync.c` for API

## See Also

[Ethernet And Networking](../../components/networking/networking.rst) |
[Ethernet AVB Stack - API and Integration Guide](../../components/networking/enet_cpsw_avtp_apiguide.md)
