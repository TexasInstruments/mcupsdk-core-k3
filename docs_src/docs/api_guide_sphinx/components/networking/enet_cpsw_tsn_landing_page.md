# Time-Sensitive Networking (TSN)

## Overview

TI's TSN stack provides a comprehensive IEEE 802.1 Time-Sensitive Networking implementation for Sitara MCU+ SoC families.
The stack is co-developed with Excelfore Corporation and runs on FreeRTOS, integrated with the Enet LLD over the CPSW peripheral.

The TSN Stack provides hardware configuration abstractions for some features 802.1 TSN features like 802.1av, 802.3br, 802.1Qbv etc.
The stack is organized into four open-source core libraries plus optional evaluation libraries for AVB (AVTP):

:::{only} SOC_AM62LX or SOC_AM62PX or SOC_AM62X
| Library        | Role                                                                 | Source Path                                                 |
|----------------|----------------------------------------------------------------------|-------------------------------------------------------------|
| tsn_unibase    | Platform-independent utility functions (logging, memory, lists)      | `source/networking/tsn/tsn-stack/tsn_unibase/`             |
| tsn_combase    | Communication primitives (sockets, threads, timers, IPC)             | `source/networking/tsn/tsn-stack/tsn_combase/`             |
| tsn_gptp       | IEEE 802.1AS-2020 gPTP protocol state machines and clock servo        | `source/networking/tsn/tsn-stack/tsn_gptp/`                |
| tsn_uniconf    | Universal YANG configuration daemon with SimpleDB                    | `source/networking/tsn/tsn-stack/tsn_uniconf/`             |
| yangemb        | YANG database licensing library (required for all TSN applications)  | `source/networking/tsn/tsn-stack/license_lib/`             |
:::

:::{only} SOC_AM62DX or SOC_AM275X
An additional evaluation library provides AVB (AVTP) support:

| Library        | Role                                                                 | Source Path                                                 |
|----------------|----------------------------------------------------------------------|-------------------------------------------------------------|
| tsn_unibase    | Platform-independent utility functions (logging, memory, lists)      | `source/networking/tsn/tsn-stack/tsn_unibase/`             |
| tsn_combase    | Communication primitives (sockets, threads, timers, IPC)             | `source/networking/tsn/tsn-stack/tsn_combase/`             |
| tsn_gptp       | IEEE 802.1AS-2020 gPTP protocol state machines and clock servo        | `source/networking/tsn/tsn-stack/tsn_gptp/`                |
| tsn_uniconf    | Universal YANG configuration daemon with SimpleDB                    | `source/networking/tsn/tsn-stack/tsn_uniconf/`             |
| tsn_l2 / tsn_conl2 *(eval)* | IEEE 1722-2016 AVTP (AAF PCM, AES3, CRF)            | `source/networking/tsn/tsn-stack/eval_lib/`                |
| yangemb        | YANG database licensing library (required for all TSN applications)  | `source/networking/tsn/tsn-stack/license_lib/`             |
:::


## Features and IEEE Standard Coverage

### Feature/Standard Supported

The following TSN Features of CPSW are supported to be configurable by the TSN Stack.

:::{only} SOC_AM62LX or SOC_AM62PX or SOC_AM62X
| Feature                                    | IEEE Standard     | Notes                                                           |
|--------------------------------------------|-------------------|-----------------------------------------------------------------|
| Credit-Based Shaper (CBS / FQTSS)          | 802.1Qav          | Hardware per-class CBS shaper in CPSW; reserves per-stream bandwidth using idle slope; YANG model configuration available |
| Interspersing Express Traffic (IET)        | IEEE 802.3br      | CPSW frame preemption separating express and preemptable traffic queues (802.3br / 802.1Qbu); YANG model configuration available |
| Enhancements for Scheduled Traffic (EST)   | 802.1Qbv          | Time-aware gate control list (GCL) via CPSW TAS hardware; per-traffic-class gate scheduling with nanosecond precision; YANG model configuration available |
| Time Synchronization (gPTP)                | 802.1AS-2020      | Full end-to-end IEEE 802.1AS-2020 stack; grandmaster, slave, and Bridge/Relay Instances; tested against Intel and TI endpoints; YANG data model configuration available |
:::

:::{only} SOC_AM62DX or SOC_AM275X
| Feature                                    | IEEE Standard     | Notes                                                           |
|--------------------------------------------|-------------------|-----------------------------------------------------------------|
| Credit-Based Shaper (CBS / FQTSS)          | 802.1Qav          | Hardware per-class CBS shaper in CPSW; reserves per-stream bandwidth using idle slope; YANG model configuration available |
| Interspersing Express Traffic (IET)        | IEEE 802.3br      | CPSW frame preemption separating express and preemptable traffic queues (802.3br / 802.1Qbu); YANG model configuration available |
| Enhancements for Scheduled Traffic (EST)   | 802.1Qbv          | Time-aware gate control list (GCL) via CPSW TAS hardware; per-traffic-class gate scheduling with nanosecond precision; YANG model configuration available |
| Time Synchronization (gPTP)                | 802.1AS-2020      | Full end-to-end IEEE 802.1AS-2020 stack; grandmaster, slave, and Bridge/Relay Instances; tested against Intel and TI endpoints; YANG data model configuration available |
| Audio Video Bridging (AVB)                 | IEEE 1722-2016    | IEEE 1722-2016 AVTP transport layer abstraction; AAF PCM, AES3, and CRF subtypes; talker and listener roles; evaluation library (Excelfore) |
:::

#### Supported Features - gPTP

- IEEE 802.1AS-2020 grandmaster (Time Transmitter), slave (Time Receiver), and bridge/Relay Instance (Boundary clock mode)
- Peer-to-peer (P2P) path delay measurement via PDelay_Req / PDelay_Resp / PDelay_Resp_Follow_Up exchange
- Best Master Clock Algorithm (BMCA) with full priority vector comparison
- Announce, Sync, Follow_Up, and Signaling message exchange
- gPTP Capable advertisement and negotiation via organization-specific signaling TLVs
- Multiple clock domain support (CMLDS) — up to 2 simultaneous domains (`GPTP_MAX_DOMAINS`)
- Hardware timestamping integration for Sync and PDelay messages
- IIR clock servo with configurable phase and frequency filter coefficients (`PHASE_OFFSET_IIR_ALPHA`, `FREQ_OFFSET_IIR_ALPHA`)
- Quick sync mode: reduced time-to-lock via shortened compute interval, increased frequency update rate, and hardware phase adjustment
- AVNU compliance mode (configurable)
- Static port state configuration (bypass BMCA for fixed topologies)

#### Not Supported Features - gPTP

- End-to-end (E2E) delay mechanism — P2P only
- No Transparent Clock support
- More than 2 simultaneous gPTP clock domains (`GPTP_MAX_DOMAINS` ceiling = 2)
- UDP/IPv4 transport — Ethernet L2 only

```{eval-rst}
.. only:: SOC_AM62DX or SOC_AM275X

   Supported Features - AVB
   ^^^^^^^^^^^^^^^^^^^^^^^^^

   - IEEE 1722-2016 AVTP subtypes: AAF (PCM and AES3 audio), CRF (Clock Reference Format), CVF (Compressed Video), ACF, TSCF, NTSCF
   - AAF audio sample rates: 8 kHz - 192 kHz; formats: Int16, Int24, Int32, Float32, AES3
   - Talker and Listener roles; configurable stream counts (``AVB_TALKER_STREAMS_NUMBER``, ``AVB_LISTENER_STREAMS_NUMBER``)
   - CBS (Credit-Based Shaper) integration for per-stream bandwidth reservation
   - CRF media clock recovery with pull/multiplier support; DP83TG721 and CDCE1214 PHY support
   - VLAN ID and PCP (Priority Code Point) per-stream configuration
   - ACF subtypes: CAN, FlexRay, LIN, Sensor, Serial, Parallel, and user-defined

   Not Supported Features - AVB
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   - AVDECC (IEEE 1722.1) - device discovery, enumeration, and stream connection management
   - SVF (SDI Video Format), RVF (Raw Video Format), MMA (MIDI), AEF (AES-encrypted), and VSF (Vendor Specific) subtypes
   - MSRP / IEEE 802.1Qat stream reservation protocol (manual CBS configuration required)
   - AVTP over UDP/IP transport - Ethernet L2 only
   - Receiver timeout callback in direct RX mode
```


## Architecture

### Software Block Diagram

![TSN Stack Software Block Diagram](../../images/networking/tsn_architecture.png)

## Resource Utilization

The table below depicts the typical resource utilization of TSN Features in a typical TSN included application.

:::{only} SOC_AM62DX or SOC_AM275X
| Resource   | Count | Usage                                                                                 |
|------------|-------|---------------------------------------------------------------------------------------|
| TX channel | 2     | gPTP (1), AVTP Tx (1)                                                                 |
| RX flow    | 2     | gPTP (1), AVTP Rx (1)                                                                 |
| Tasks      | 3     | uniconf_task (1), gptp2d_task (1), avtp_rx_task (1) |
:::

:::{only} SOC_AM62LX or SOC_AM62PX or SOC_AM62X
| Resource   | Count | Usage                                                                                 |
|------------|-------|---------------------------------------------------------------------------------------|
| TX channel | 1     | gPTP (1)                                                                 |
| RX flow    | 1     | gPTP (1)                                                                 |
| Tasks      | 2     | uniconf_task (1), gptp2d_task (1) |
:::

:::{admonition} Note
Default configuration: each use case uses one dedicated CPSW Tx DMA channel and one dedicated Rx Flow per port. Debug builds use 16 KB stack per task (`TSN_TSK_STACK_SIZE = 16 KB`).
:::

## Examples and Feature Coverage

:::{only} SOC_AM62LX or SOC_AM62PX

| Example | Feature Demonstrated | Standards Exercised |
|---------|----------------------|---------------------|
| [gPTP Time Receiver](../../examples/networking/enet_cpsw_tsn_gptp_tr.md) | gPTP slave mode, clock lock to grandmaster | 802.1AS-2020 |
| [gPTP Time Transmitter](../../examples/networking/enet_cpsw_tsn_gptp_tt.md) | gPTP grandmaster mode | 802.1AS-2020 |
| [gPTP Bridge](../../examples/networking/enet_cpsw_tsn_gptp_bridge.md) | gPTP Relay Instance (Boundary clock / bridge) | 802.1AS-2020 |

:::

:::{only} SOC_AM62X

| Example | Feature Demonstrated | Standards Exercised |
|---------|----------------------|---------------------|
| [gPTP Time Receiver](../../examples/networking/enet_cpsw_tsn_gptp_tr.md) | gPTP slave mode, clock lock to grandmaster | 802.1AS-2020 |
| [gPTP Time Transmitter](../../examples/networking/enet_cpsw_tsn_gptp_tt.md) | gPTP grandmaster mode | 802.1AS-2020 |
| [gPTP Bridge](../../examples/networking/enet_cpsw_tsn_gptp_bridge.md) | gPTP Relay Instance (Boundary clock / bridge) | 802.1AS-2020 |
| [TSN EST](../../examples/networking/enet_cpsw_est.md) | Scheduled Traffic gate control list (GCL) | 802.1Qbv |

:::

:::{only} SOC_AM275X

| Example | Feature Demonstrated | Standards Exercised |
|---------|----------------------|---------------------|
| [gPTP Time Receiver](../../examples/networking/enet_cpsw_tsn_gptp_tr.md) | gPTP slave mode, clock lock to grandmaster | 802.1AS-2020 |
| [gPTP Time Transmitter](../../examples/networking/enet_cpsw_tsn_gptp_tt.md) | gPTP grandmaster mode | 802.1AS-2020 |
| [gPTP Bridge](../../examples/networking/enet_cpsw_tsn_gptp_bridge.md) | gPTP Relay Instance (Boundary clock / bridge) | 802.1AS-2020 |
| [TSN EST](../../examples/networking/enet_cpsw_est.md) | Scheduled Traffic gate control list (GCL) | 802.1Qbv |
| [AVTP AAF PCM](../../examples/networking/enet_cpsw_avtp_example.md) | AVTP AAF PCM Talker + Listener, CBS shaper | IEEE 1722-2016, 802.1Qav |
| [AVTP AES3 AAF](../../examples/networking/enet_tsn_avtp_aes3_aaf_example.md) | AVTP AES3 (Dolby EC3) format listener | IEEE 1722-2016 |
| [Multistream MCR](../../examples/networking/enet_cpsw_tsn_media_clock_recovery.md) | Multistream AAF PCM + CRF media clock recovery | IEEE 1722-2016 |
| [CRF Master](../../examples/networking/enet_cpsw_tsn_crf.md) | CRF master clock reference stream | IEEE 1722-2016 |
| [CRF + AVTP](../../examples/networking/enet_cpsw_tsn_crf_avtp.md) | CRF combined with AVTP | IEEE 1722-2016 |
| [AutoAmp Demo](../../examples/networking/enet_cpsw_tsn_crf_autoamp_demo.md) | Multistream AAF PCM + CRF + TCP control server | IEEE 1722-2016, 802.1Qav |
| [AVB Audio Playback](../../examples/networking/enet_cpsw_avb_audio_playback.md) | End-to-end AVB audio playback | 802.1AS-2020, 802.1Qav, 1722 |
| [AVB Ethernet Ring](../../examples/networking/enet_cpsw_avb_audio_etherring_demo.md) | Zonal audio playback with Ethernet ring topology | 802.1AS-2020, 802.1Qav, 1722 |

:::

:::{only} SOC_AM62DX

| Example | Feature Demonstrated | Standards Exercised |
|---------|----------------------|---------------------|
| [gPTP Time Receiver](../../examples/networking/enet_cpsw_tsn_gptp_tr.md) | gPTP slave mode, clock lock to grandmaster | 802.1AS-2020 |
| [gPTP Time Transmitter](../../examples/networking/enet_cpsw_tsn_gptp_tt.md) | gPTP grandmaster mode | 802.1AS-2020 |
| [gPTP Bridge](../../examples/networking/enet_cpsw_tsn_gptp_bridge.md) | gPTP Relay Instance (Boundary clock / bridge) | 802.1AS-2020 |
| [TSN EST](../../examples/networking/enet_cpsw_est.md) | Scheduled Traffic gate control list (GCL) | 802.1Qbv |
| [AVTP AAF PCM](../../examples/networking/enet_cpsw_avtp_example.md) | AVTP AAF PCM Talker + Listener, CBS shaper | IEEE 1722-2016, 802.1Qav |
| [AVTP AES3 AAF](../../examples/networking/enet_tsn_avtp_aes3_aaf_example.md) | AVTP AES3 (Dolby EC3) format listener | IEEE 1722-2016 |
| [CRF Master](../../examples/networking/enet_cpsw_tsn_crf.md) | CRF master clock reference stream | IEEE 1722-2016 |
| [CRF + AVTP](../../examples/networking/enet_cpsw_tsn_crf_avtp.md) | CRF combined with AVTP | IEEE 1722-2016 |
| [AutoAmp Demo](../../examples/networking/enet_cpsw_tsn_crf_autoamp_demo.md) | Multistream AAF PCM + CRF + TCP control server | IEEE 1722-2016, 802.1Qav |

:::


## Interoperability Tests

### gPTP Interoperability

The following third-party devices/Stacks have been used for interoperability verification of the IEEE 802.1AS-2020 gPTP implementation:

| Peer Hardware                    | Peer Software                    | Roles Tested                                              |
|----------------------------------|-----------------------------------|-----------------------------------------------------------|
| Intel I210 NIC                   | Linux `ptp4l` (linuxptp)         | Grandmaster, slave, Bridge/Relay                          |
| Intel I350 NIC                   | Linux `ptp4l` (linuxptp)         | Grandmaster, slave, Bridge/Relay                          |
| TI EVM                           | TI gPTP stack (TSN SDK)          | Peer-to-peer slave / master; daisy-chain with multiple nodes     |
| TI EVM with DP83TG721 PHY        | TI gPTP stack (TSN SDK)          | Grandmaster, slave                                        |


## Memory Footprint

All measurements are on Sitara R5F, release build. Columns: Code = `.text`, Read Only = `.rodata` / `.const`, Read Write = `.bss` + `.data` (RAM).

### Configuration 1: gPTP Only

:::{admonition} Note
Measured using [gptp_cpsw_app](../../examples/networking/enet_cpsw_tsn_gptp_tr.md) (AM275x R5F, release, `-flto` disabled), It is expected to reduce further by 10-20% by enabling -`-flto` flag.
:::

| Library      | Code (KB) | Read Only (KB) | Read Write (KB) | Total (KB) |
|--------------|-----------|----------------|-----------------|------------|
| tsn_unibase  | 4         | 1              | 7               | 12         |
| tsn_combase  | 14        | 4              | 18              | 36         |
| tsn_uniconf  | 34        | 12             | 67              | 113        |
| tsn_gptp     | 61        | 12             | 25              | 97         |
| yangemb      | 3         | 1              | 0               | 3          |
| **Total**    | **117**   | **29**         | **116**         | **262**    |

```{eval-rst}
.. only:: SOC_AM62DX or SOC_AM275X

   Configuration 2: gPTP + AVB
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^
```

::::{only} SOC_AM62DX or SOC_AM275X
:::{admonition} Note
Measured using [aafpcmtalker_app](../../examples/networking/enet_cpsw_avtp_example.md) (AM275x R5F, release, `-flto` disabled), It is expected to reduce further by 10-20% by enabling -`-flto` flag.
The number of talker and listener streams is application-level configuration (`AVB_TALKER_STREAMS_NUMBER`,
`AVB_LISTENER_STREAMS_NUMBER` in `avtp_buildconf.h`) and does not affect the library footprint.
:::

| Library           | Code (KB) | Read Only (KB) | Read Write (KB) | Total (KB) |
|-------------------|-----------|----------------|-----------------|------------|
| tsn_unibase       | 5         | 1              | 7               | 13         |
| tsn_combase       | 15        | 4              | 18              | 37         |
| tsn_uniconf       | 35        | 13             | 67              | 114        |
| tsn_gptp          | 63        | 13             | 25              | 100        |
| tsn_l2 / tsn_conl2| 27        | 6              | 9               | 42         |
| yangemb           | 3         | 1              | 0               | 3          |
| **Total**         | **147**   | **38**         | **124**         | **309**    |
::::


## Performance Metrics

```{eval-rst}
.. only:: SOC_AM275X

   AVB End-to-End Audio Latency (AM275x EVM)
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
```

:::{only} SOC_AM275X
Measured using [Ethernet AVB Audio Playback Demo](../../examples/networking/enet_cpsw_avb_audio_playback.md).

**Test Setup:**
- SoC: AM275x, Cortex-R5F0 Core 0 @ 1000 MHz, MSRAM cached
- Link: RGMII @ 1 Gbps
- AVTP subtype: AAF PCM, 8 channels, 48 kHz, 32-bit, 6 samples/AVTPDU, 125 µs packet interval

| Measurement              | Min      | Max      |
|--------------------------|----------|----------|
| AVB network latency (A)  | 16 µs    | 37 µs    |
| McASP–McASP latency (B)  | —        | 332 µs * |
| Jack–Jack latency (C)    | —        | 1270 µs *|

\* Measured with McASP transaction size = 6 samples.
:::

```{eval-rst}
.. only:: SOC_AM275X

   Media Clock Recovery Accuracy (AM275x EVM)
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
```

:::{only} SOC_AM275X
CRF slave via DP83TG721 PHY:

| Parameter                        | Value   |
|----------------------------------|---------|
| Max absolute phase difference    | 200 ns* |

CRF slave via CDCE1214 PHY:

| Parameter                        | Value   |
|----------------------------------|---------|
| Max absolute phase difference    | 40 us* |

\* Further improvement is possible by tuning CRF control-loop parameters.
:::

### gPTP performance

| gPTP Parameter    | Value    | Notes                                                                                              |
|-------------------|----------|----------------------------------------------------------------------------------------------------|
| Initial time to sync | ~500 ms | Measured from link up with Quick sync enabled. See {ref}`gPTP Time-to-Sync Optimization <gptp-time-to-sync-optimization>` for tuning details. |
| Sync accuracy     | < 100 ns | Tested with Intel I210, I229, and I350 NICs and TI EVM-to-EVM setups.                            |


For memory optimization, time-to-sync tuning, troubleshooting, and known limitations see:

- [TSN Developer Guidelines](enet_cpsw_tsn_developer_guide.md) — TSN Developer Guidelines (memory footprint, sync optimization, troubleshooting, limitations)


## See Also

- [TSN Userguide](enet_cpsw_tsn_architecture_guide.md) — gPTP/AVB design, hardware interaction, and EST/CBS/IET configuration via uniconf
- [Ethernet TSN and gPTP Stack - API and Integration Guide](enet_cpsw_tsn_gptp_apiguide.md) — gPTP stack API and integration guide
- [TSN Developer Guidelines](enet_cpsw_tsn_developer_guide.md) — TSN Developer Guidelines (memory, sync tuning, troubleshooting, limitations)
- [Ethernet TSN gPTP Examples](../../examples/networking/enet_cpsw_tsn_gptp.md) — gPTP example index
- [Ethernet And Networking](networking.rst) — Ethernet and Networking overview

:::{only} SOC_AM275X
- [eAVB Performance](enet_lld/eavb_performance.md) — eAVB latency performance data
- [Ethernet AVB Stack - API and Integration Guide](enet_cpsw_avtp_apiguide.md) — AVB stack API and integration guide
:::

:::{only} SOC_AM62DX
- [Ethernet AVB Stack - API and Integration Guide](enet_cpsw_avtp_apiguide.md) — AVB stack API and integration guide
:::
