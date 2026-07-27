# Ethernet Performance
## Introduction
This section provides the performance numbers of Ethernet drivers using CPSW peripheral in MCU+ SDK

## Setup Details
SOC Details           | Values             |
----------------------|--------------------|
Core                  | Main R5F0 Core 0   |
Core Operating Speed  | 800 MHz            |
Memory Type           | DDR                |
Cache status          | Enabled            |
EVM Type              | AM62D-EVM          |
PHY Card used         | DP83867 Add-on Card|

## Layer 2 Performance
![](../../../images/networking/CPSW_latency_measurement_diagram.bmp)

### Configuration Details
Configuration                   | Value                    |
--------------------------------|--------------------------|
Processing Core                 | Main R5F0 Core 0         |
Core Frequency                  | 800 MHz                  |
Ethernet Interface Type         | RGMII at 1 Gbps          |
Packet buffer memory            | DDR (uncached)           |
Scatter-gather TX               | Yes                      |
Scatter-gather RX               | Yes                      |
UDMA interrupt pacing           | NO                       |
RTOS                            | FreeRTOS                 |
RTOS application                | Modified [Enet CPSW Loopback Example](../../../examples/networking/enet_cpsw_loopback_example.md) example |
Host PC tool version            | nload                    |
Rx packet length                | 200 B                    |
Tx packet length                | 200 B                    |

### Layer 2 Latency
<table>
    <tr>
        <td style="text-align: center;"><b>Parameter</b></td>
        <td style="text-align: center;"><b>CPU<->CPSW   Latency Value (ns)</b></td>
        <td style="text-align: center;"><b>PHY (DP83867IR) Latency  (from datasheet) in ns</b></td>
        <td style="text-align: center;"><b>Total Latency   (ns)</b></td>
    </tr>
    <tr>
        <td>RX Latency</td>
        <td>19000</td>
        <td>288</td>
        <td>19288</td>
    </tr>
    <tr>
        <td>TX Latency</td>
        <td>11000</td>
        <td>384</td>
        <td>11384</td>
    </tr>
</table>

## TCP/IP Performance

### Configuration Details
Configuration                   | Value                                            |
--------------------------------|--------------------------------------------------|
Processing Core                 | Main R5F0 Core 0                                 |
Core Frequency                  | 800 MHz                                          |
Ethernet Interface Type         | RGMII at 1 Gbps                                  |
Packet buffer memory            | DDR (cached)                                     |
Hardware checksum offload       | Enabled on both Tx and Rx Side                   |
Scatter-gather TX               | Yes                                              |
Scatter-gather RX               | Yes                                              |
UDMA interrupt pacing           | Yes (realized with timer based polling at 1ms interval) |
RTOS                            | FreeRTOS                                         |
RTOS application                | [Enet Lwip CPSW Example](../../../examples/networking/enet_lwip_cpsw.md) in examples |
TCP/IP stack                    | LwIP version {{ VAR_LWIP_VERSION }}              |
Host PC tool version            | iperf v2.0.5                                     |
Number of Rx packet buffers     | 32                                               |
Number of Tx packet buffers     | 16                                               |

#### TCP Throughput
<table>
    <tr>
        <td style="text-align: left;"><b>Test</b></td>
        <td style="text-align: center;"><b>Bandwidth   (Mbps)</b></td>
        <td style="text-align: center;"><b>CPU Load   (%) </b></td>
    </tr>
    <tr>
        <td>TCP RX</td><td>154</td><td>99</td>
    </tr>
    <tr>
        <td>TCP TX</td><td>83</td><td>99</td>
    </tr>
    <tr>
        <td>TCP Bidirectional</td><td>RX=52   TX=52</td><td>100</td>
    </tr>
</table>

<b>Host PC commands:</b>
- TCP Rx and Tx (Sequential):
    $```iperf -c <evm_ip> -r```
- TCP Rx and Tx (Bidirectional):
    $```iperf -c <evm_ip> -d```

#### UDP Throughput
<table>
    <tr>
        <td rowspan="2" style="text-align: left;"><b>Test</b></td>
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 64B </b></td>
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 256B</b></td>
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 512B</b></td>
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 1470B</b></td>
    </tr>
    <tr>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
    </tr>
    <tr>
        <td rowspan="3">UDP RX</td>
        <td>5</td><td>58</td><td>0.0</td>
        <td>5</td><td>18</td><td>0.0</td>
        <td>25</td><td>42</td><td>0.0</td>
        <td>50</td><td>36</td><td>0.0</td>
    </tr>
    <tr>
        <td>10</td><td>98</td><td>8.5</td>
        <td>15</td><td>46</td><td>0.0</td>
        <td>50</td><td>82</td><td>0.1</td>
        <td>60</td><td>43</td><td>0.0</td>
    </tr>
    <tr>
        <td>15</td><td>98</td><td>37</td>
        <td>25</td><td>76</td><td>0</td>
        <td>55</td><td>95</td><td>0.1</td>
        <td>95</td><td>66</td><td>0</td>
    </tr>
    <tr>
        <td>UDP RX (Max)</td>
        <td>7</td><td>81</td><td>0.099</td>
        <td>29.9</td><td>99</td><td>0.84</td>
        <td>56</td><td>98</td><td>0.26</td>
        <td>131</td><td>95</td><td>0.045</td>
    </tr>
    <tr>
        <td>UDP TX (Max)</td>
        <td>13.2</td><td>100</td><td>0</td>
        <td>52.8</td><td>100</td><td>0.0093</td>
        <td>105</td><td>100</td><td>0.025</td>
        <td>302</td><td>100</td><td>0.039</td>
    </tr>
</table>

<b>Host PC commands:</b>
- Test with datagram length of 64B:
     $```iperf -c <evm_ip> -u -l64 -b <bw> -r```
where \<bw\> is 5M, 10M, 15M, etc

- Test with datagram length of 256B:
     $```iperf -c <evm_ip> -u -l 256 -b <bw> -r```
where \<bw\> is 25M, 50M, 100M, etc

- Test with datagram length of 512B:
     $```iperf -c <evm_ip> -u -l 512 -b <bw> -r```
where \<bw\> is 25M, 50M, 100M, etc

- Test with datagram length of 1470B (max):
     $```iperf -c <evm_ip> -u -b <bw> -r```
where \<bw\> is 25M, 50M, 100M, etc

## IEEE 802.1AS (gPTP) Performance Numbers

### Configuration Details
Configuration                   | Value                                            |
--------------------------------|--------------------------------------------------|
Processing Core                 | Main R5F0 Core 0                                 |
Core Frequency                  | 800 MHz                                          |
Ethernet Interface Type         | RGMII at 1 Gbps                                  |
Packet buffer memory            | DDR (cached)                                     |
UDMA interrupt pacing           | No (Disabled for gptp flow)                      |
RTOS                            | FreeRTOS
gptp Configuration              | Refer to [Ethernet TSN gPTP Examples](../../../examples/networking/enet_cpsw_tsn_gptp.md) on quick sync configuration|

### Performance
| Test | Measured value | 802.1AS Parameters                                                               |
|-----------------------|----------------|---------------------------------------------------------------------------------|
| 802.1AS Time to Initial Sync  | 700ms         | - sync interval = 15.625ms <br> - pdelay req = 15.625ms <br> - BMCA fixed configuration |
| 802.1AS Sync Accuracy         | 70ns          | - sync interval = 125ms <br> - pdelay req = 1s                                      |

## See Also
[Ethernet And Networking](../networking.rst)
[Enet Lwip CPSW Example](../../../examples/networking/enet_lwip_cpsw.md)
