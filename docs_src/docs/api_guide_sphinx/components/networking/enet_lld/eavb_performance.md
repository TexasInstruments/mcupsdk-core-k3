# Performance of Ethernet AVB
## Introduction
This section provides an overview of Ethernet Audio Video Bridging (eAVB) performance benchmarking on AM275 EVM. The benchmarking evaluates the latency of audio transported over ethernet.

## Setup Details
The [Ethernet AVB Audio Playback Demo](../../../examples/networking/enet_cpsw_avb_audio_playback.md) is used to obtain the performance numbers.

### SOC Configuration
|SOC Details           | Values             |
|----------------------|--------------------|
|Core                  | R5F0 Core 0        |
|Core Operating Speed  | 1000 MHz           |
|Memory Type           | MSRAM              |
|Cache status          | Enabled            |
|EVM Type              | AM275-EVM          |
|Packet buffer memory  | MSRAM (Cached)     |
|Ethernet Link         | RGMII at 1 Gbps    |

### IEEE1722 AVB Stream Configuration
| Parameter                     | Description         |
|-------------------------------|---------------------|
| Number of Channels            | 8                   |
| IEEE1722 AVTP Subtype         | AAF PCM             |
| Sampling Rate (Media Clock Freq)| 48 kHz            |
| Bit Depth                     | 32 bits             |
| Samples Per AVTPDU            | 6 Samples           |
| IEEE1722 AVTP Packet Length            | 247 Bytes           |
| IEEE1722 AVTP Frame Transmit Interval  | 125 µs              |
| McASP Transaction Size        | 16 Samples          |
| McASP Transaction rate        | 3000 Hz (333.3 µs)  |

## Performance Measured
Below is the Setup Details
![](../../../images/networking/eavb_latency_diagram.png)

### Latency Measured
| Parameter                 | Min Latency (µs) | Max Latency (µs) |
|---------------------------|------------------|------------------|
| AVB Latency (A)           | 16               | 37               |
| McASP - McASP Latency (B) | -                | 332`*`             |
| Jack - Jack Latency (C)   | -                | 1270`*`             |

`*` This performance is benchmarked when the McASP Transaction size is 6 Samples.

### Media Clock Sync

DP83TG721 is used as Audio clock generator, IEEE1722 CRF stream is used to recover the media Clock.
The Built in CRF Slave Functionality of the DP83TG721 is not used.

| Parameter                          | Value           |
|------------------------------------|-----------------|
| Maximum Absolute Phase Difference  | 200ns`*`        |

`*` - Futher optimization is possible by tuning the control loop parameters.

For More details, refer to [Ethernet AVB Multistream Media Clock Recovery](../../../examples/networking/enet_cpsw_tsn_media_clock_recovery.md)

## See Also
