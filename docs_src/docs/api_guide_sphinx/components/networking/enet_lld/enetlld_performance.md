# Ethernet Performance on AM62P

```{contents}
:depth: 2
:local:
```

## Introduction

This section provides the performance numbers of Ethernet drivers using CPSW peripheral in MCU+ SDK.

## Setup Details

| SOC Details | Values |
|---|---|
| Core | R5F |
| Core Operating Speed | 800 MHz |
| Memory Type | DDR |
| Cache status | Enabled |
| EVM Type | AM62PX-LP |

## Layer 2 Performance

### Configuration Details

| Configuration | Value |
|---|---|
| Processing Core | Main R5F0 Core 0 |
| Core Frequency | 800 MHz |
| Ethernet Interface Type | RGMII at 1 Gbps |
| Packet buffer memory | DDR (uncached) |
| Scatter-gather TX | Yes |
| Scatter-gather RX | Yes |
| UDMA interrupt pacing | NO |
| RTOS | FreeRTOS |
| Rx packet length | 200 B |
| Tx packet length | 200 B |

### Layer 2 Latency

| Parameter | CPU<->CPSW Latency Value (ns) | PHY (DP83867IR) Latency (from datasheet) in ns | Total Latency (ns) |
|---|---|---|---|
| RX Latency | 20000 | 288 | 20288 |
| TX Latency | 10000 | 384 | 10384 |

## TCP/IP Performance

### Configuration Details

| Configuration | Value |
|---|---|
| Processing Core | WKUP R5F0 Core 0 |
| Core Frequency | 800 MHz |
| Ethernet Interface Type | RGMII at 1 Gbps |
| Packet buffer memory | DDR (cached) |
| Hardware checksum offload | Enabled on both Tx and Rx Side |
| Scatter-gather TX | Yes |
| Scatter-gather RX | Yes |
| UDMA interrupt pacing | Yes (realized with timer based interrupt pacing) |
| RTOS | FreeRTOS |
| TCP/IP stack | LwIP version {{ VAR_LWIP_VERSION }} |
| Host PC tool version | iperf v2.0.10 |
| Number of Rx packet buffers | 32 |
| Number of Tx packet buffers | 16 |

### TCP Throughput

| Test | Bandwidth (Mbps) | CPU Load (%) |
|---|---|---|
| TCP RX | 93 | 38 |
| TCP TX | 93 | 70 |
| TCP Bidirectional | RX=87 / TX=85.4 | 97.5 |

**Host PC commands:**
- TCP Rx and Tx (Sequential): `iperf -c <evm_ip> -r`
- TCP Rx and Tx (Bidirectional): `iperf -c <evm_ip> -d`

### UDP Throughput

| Test | BW 64B (Mbps) | CPU 64B (%) | Loss 64B (%) | BW 256B (Mbps) | CPU 256B (%) | Loss 256B (%) | BW 512B (Mbps) | CPU 512B (%) | Loss 512B (%) | BW 1470B (Mbps) | CPU 1470B (%) | Loss 1470B (%) |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| UDP RX | 5 | 30 | 0.0 | 5 | 15 | 0.0 | 25 | 34 | 0.01 | 50 | 16 | 0.0 |
| UDP RX | 10 | 58 | 0.15 | 15 | 38 | 0.02 | 50 | 65 | 0.2 | 65 | 38 | 0.01 |
| UDP RX | 15 | 84 | 0.2 | 25 | 61 | 0.5 | 65 | 82 | 0.3 | 100 | 56 | 0.08 |
| UDP RX (Max) | 17 | 100 | 1.5 | 42 | 97 | 0.9 | 80 | 99 | 0.5 | 177 | 99.8 | 0.33 |
| UDP TX (Max) | 26 | 100 | 0.0 | 64 | 100 | 0.0 | 130 | 100 | 0.0 | 372 | 100 | 0.0 |

**Host PC commands:**
- 64B: `iperf -c <evm_ip> -u -l 64 -b <bw> -r` where `<bw>` is 5M, 10M, 15M, etc.
- 256B: `iperf -c <evm_ip> -u -l 256 -b <bw> -r` where `<bw>` is 25M, 50M, 100M, etc.
- 512B: `iperf -c <evm_ip> -u -l 512 -b <bw> -r` where `<bw>` is 25M, 50M, 100M, etc.
- 1470B (max): `iperf -c <evm_ip> -u -b <bw> -r` where `<bw>` is 25M, 50M, 100M, etc.
