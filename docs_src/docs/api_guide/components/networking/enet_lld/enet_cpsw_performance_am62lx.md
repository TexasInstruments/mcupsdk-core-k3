# Ethernet Performance{#enetlld_performance}
[TOC]
# Introduction
This section provides the performance numbers of Ethernet drivers using CPSW peripheral in MCU+ SDK

# Setup Details
SOC Details           | Values          |
----------------------|-----------------|
Core                  | A53             |
Core Operating Speed  | 1 GHz           |
Memory Type           | DDR             |
Cache status          | Enabled         |
EVM Type              | AM62LX-EVM      |

# Layer 2 Performance
  \imageStyle{CPSW_latency_measurement_diagram.bmp,width:30%}
  \image html CPSW_latency_measurement_diagram.bmp Latency defination

## Configuration Details
Configuration                   | Value                    |
--------------------------------|--------------------------|
Processing Core                 | Main A53 Core 0          |
Core Frequency                  | 1 GHz                    |
Ethernet Interface Type         | RGMII at 1 Gbps          |
Packet buffer memory            | DDR (uncached)           |
UDMA interrupt pacing           | NO                       |
RTOS                            | FreeRTOS                 |
RTOS application                | Modified \ref EXAMPLES_ENET_CPSW_LOOPBACK \n example   |
Host PC tool version            | nload                    |
Rx packet length                | 200 B                    |
Tx packet length                | 200 B                    |
\n


## Layer 2 Latency
<table>
    <tr>
        <td style="text-align: center;"><b>Parameter</b></td>
        <td style="text-align: center;"><b>CPU<->CPSW \n Latency Value (ns)</b></td>
        <td style="text-align: center;"><b>PHY (DP83867IR) Latency\n (from datasheet) in ns</b></td>
        <td style="text-align: center;"><b>Total Latency \n (ns)</b></td>
    </tr>
    <tr>
        <td>RX Latency</td>
        <td>13821</td>
        <td>288</td>
        <td>14109</td>
    </tr>
    <tr>
        <td>TX Latency</td>
        <td>7000</td>
        <td>88</td>
        <td>7384</td>
    </tr>
</table>


# TCP/IP Performance

## Configuration Details
Configuration                   | Value                                            |
--------------------------------|--------------------------------------------------|
Processing Core                 | Main A53Core 0                                   |
Core Frequency                  | 1 GHz                                            |
Ethernet Interface Type         | RGMII at 1 Gbps                                  |
Packet buffer memory            | DDR (cached)                                     |
Hardware checksum offload       | Enabled on both Tx and Rx Side                   |
UDMA interrupt pacing           | Yes (realized with timer based interrupt pacing) |
RTOS                            | FreeRTOS                                         |
RTOS application                | \ref EXAMPLES_ENET_LWIP_CPSW in examples         |
TCP/IP stack                    | LwIP version @VAR_LWIP_VERSION                   |
Host PC tool version            | iperf v2.0.10                                    |
Number of Rx packet buffers     | 32                                               |
Number of Tx packet buffers     | 16                                               |
\n
### TCP Throughput
<table>
    <tr>
        <td style="text-align: left;"><b>Test</b></td>
        <td style="text-align: center;"><b>Bandwidth \n (Mbps)</b></td>
        <td style="text-align: center;"><b>CPU Load \n (%) </b></td>
    </tr>
    <tr>
        <td>TCP RX</td><td>93</td><td>11</td>
    </tr>
    <tr>
        <td>TCP TX</td><td>93</td><td>14</td>
    </tr>
    <tr>
        <td>TCP Bidirectional</td><td>RX=93 \n TX=93</td><td>24</td>
    </tr>
</table>

<b>Host PC commands:</b>
- TCP Rx and Tx (Sequential):\n
    $```iperf -c <evm_ip> -r```\n
- TCP Rx and Tx (Bidirectional):\n
    $```iperf -c <evm_ip> -d```\n

### UDP Throughput



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
        <td>50</td><td>8.4</td><td>0</td>
        
    </tr>
    <tr>
        <td>10</td><td>7</td><td>0</td>
        <td>50</td><td>17.2</td><td>0.06</td>
        <td>65</td><td>10</td><td>0.01</td>
        
    </tr>

    <tr>
        <td>25</td><td>17</td><td>0.06</td>
        <td>55</td><td>19.2</td><td>0.072</td>
        <td>95</td><td>13.14</td><td>0.04</td>
        
    </tr>

    <tr>
        <td>UDP RX (Max)</td>
        <td>30</td><td>20.03</td><td>0.1</td>
        <td>60</td><td>20</td><td>0.1</td>
        <td>184</td><td>23.4</td><td>0.6</td>
        
    </tr>

    

    <tr>
        <td>UDP TX (Max)</td>
        <td>168</td><td>100</td><td>1.01</td>
        <td>342</td><td>100</td><td>0.8</td>
        <td>957</td><td>100</td><td>0.0</td>
       
    </tr>
</table>


<b>Host PC commands:</b>
- Test with datagram length of 64B:\n
     $```iperf -c <evm_ip> -u -l64 -b <bw> -r```\n
where \<bw\> is 5M, 10M, 15M, etc\n

- Test with datagram length of 256B:\n
     $```iperf -c <evm_ip> -u -l 256 -b <bw> -r```\n
where \<bw\> is 25M, 50M, 100M, etc\n

- Test with datagram length of 512B:\n
     $```iperf -c <evm_ip> -u -l 512 -b <bw> -r```\n
where \<bw\> is 25M, 50M, 100M, etc\n

- Test with datagram length of 1470B (max):\n
     $```iperf -c <evm_ip> -u -b <bw> -r```\n
where \<bw\> is 25M, 50M, 100M, etc\n

# See Also
\ref NETWORKING
\ref EXAMPLES_ENET_LWIP_CPSW