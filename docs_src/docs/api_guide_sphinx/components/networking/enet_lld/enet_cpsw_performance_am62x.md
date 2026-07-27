# Ethernet Performance
## Introduction
This section provides the performance numbers of Ethernet drivers using CPSW peripheral in MCU+ SDK

## Setup Details
SOC Details           | Values          |
----------------------|-----------------|
Core                  | A53             |
Core Operating Speed  | 1 GHz           |
Memory Type           | DDR             |
Cache status          | Enabled         |
EVM Type              | AM62x-SK        |

## Layer 2 Performance
![](../../../images/networking/CPSW_latency_measurement_diagram.bmp)

### Configuration Details
Configuration                   | Value                    |
--------------------------------|--------------------------|
Processing Core                 | Main A53 Core 0          |
Core Frequency                  | 1 GHz                    |
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
        <td>7000</td>
        <td>384</td>
        <td>7384</td>
    </tr>
</table>

## TCP/IP Performance

### Configuration Details
Configuration                   | Value                                            |
--------------------------------|--------------------------------------------------|
Processing Core                 | Main A53Core 0                                   |
Core Frequency                  | 1 GHz                                            |
Ethernet Interface Type         | RGMII at 1 Gbps                                  |
Packet buffer memory            | DDR (cached)                                     |
Hardware checksum offload       | Enabled on both Tx and Rx Side                   |
Scatter-gather TX               | Yes                                              |
Scatter-gather RX               | Yes                                              |
UDMA interrupt pacing           | Yes (realized with timer based interrupt pacing) |
RTOS                            | FreeRTOS                                         |
RTOS application                | [Enet Lwip CPSW Example](../../../examples/networking/enet_lwip_cpsw.md) in examples |
TCP/IP stack                    | LwIP version {{ VAR_LWIP_VERSION }}              |
Host PC tool version            | iperf v2.0.10                                    |
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
        <td>TCP RX</td><td>93</td><td>11</td>
    </tr>
    <tr>
        <td>TCP TX</td><td>93</td><td>11</td>
    </tr>
    <tr>
        <td>TCP Bidirectional</td><td>RX=93   TX=93</td><td>24</td>
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
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 256B </b></td>
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 512B</b></td>
        <td colspan="3" style="text-align: center;"><b>Datagram Length = 1470B</b></td>
    </tr>
    <tr>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
        <td><b>Bandwidth (Mbps)</b></td><td><b>CPU Load (%)</b></td><td><b>Packet Loss (%)</b></td>
    </tr>
   <tr>
        <td rowspan="3">UDP RX</td>
        <td>5</td><td>4</td><td>0</td>
        <td>25</td><td>9</td><td>0.016</td>
        <td>50</td><td>7.44</td><td>0</td>
    </tr>
    <tr>
        <td>10</td><td>7</td><td>0</td>
        <td>50</td><td>17.2</td><td>0.11</td>
        <td>65</td><td>9.27</td><td>0.01</td>
    </tr>
    <tr>
        <td>25</td><td>16.6</td><td>0.06</td>
        <td>65</td><td>21</td><td>4.8</td>
        <td>95</td><td>13.14</td><td>0.66</td>
    </tr>
    <tr>
        <td>UDP RX (Max)</td>
        <td>30</td><td>19.7</td><td>0.1</td>
        <td>60</td><td>20</td><td>0.1</td>
        <td>175</td><td>23.4</td><td>0.59</td>
    </tr>
    <tr>
        <td>UDP RX (Max)   with 128 Rx buffers</td>
        <td>115</td><td>69.1</td><td>0.1</td>
        <td>240</td><td>74.8</td><td>0.1</td>
        <td>720</td><td>90.8</td><td>1.3</td>
    </tr>
    <tr>
        <td>UDP TX (Max)</td>
        <td>175</td><td>100</td><td>0.05</td>
        <td>350</td><td>100</td><td>0.0</td>
        <td>957</td><td>100</td><td>0.0</td>
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

## See Also
[Ethernet And Networking](../networking.rst)
[Enet Lwip CPSW Example](../../../examples/networking/enet_lwip_cpsw.md)
