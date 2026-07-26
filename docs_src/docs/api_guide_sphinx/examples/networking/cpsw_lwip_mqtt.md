# CPSW Lwip MQTT Client Example


## Introduction

```{note}
LwIP and MbedTLS features are made available as is from the public lwIP and MbedTLS project. SDK configuration may only enable and exercise a subset of these features.
The mbedTLS public project being used here (tag 2.13.1) can be found here: https://github.com/Mbed-TLS/mbedtls/tree/mbedtls-2.13.1
```

::::{only} SOC_AM62DX
```{note}
This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
```
::::

This example demonstrates how to run a MQTT client with TLS enabled on LwIP networking stack using raw API coupled with ethernet driver (ENET), with MbedTLS providing TLS functionality in the L4 layer.

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62DX

On {{ VAR_SOC_NAME }}, we can do ethernet based communication using CPSW
  - This is a standard ethernet switch + port HW
  - It uses the ethernet driver underneath with LwIP TCP/IP networking stack

::::

The example does the following:
- Initializes the ethernet driver for the underlying HW
- Initializes the LwIP stack for TCP/UDP IP
- Client gets a static IP address and launches the MQTT client connection request
- Based on the mode selected from app_main.c, the MQTT client acts as a subscriber or publisher
- MQTT broker waits for connection from client on port 1883 (TLS disabled) or port 8883 (TLS enabled)
- When the broker receives a connection request from the MQTT Client, a 2-way Auth is completed and both the broker and client are verified by a TLS handshake
- After the handshake is complete, if publisher mode is selected, the client will publish the message entered by user in the console, else it will subscribe to the broker

## Supported Combinations

```{note}
In this example, we have used PBUF_RAM to allocate pbufs instead of PBUF_POOLS. This is subject to change in future releases.
```

::::{only} SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/lwip/cpsw_lwip_mqtt

::::

```{note}
To use MQTT without TLS, in "cpsw_lwip_mqtt/mqtt.h", set MQTT_HAVE_TLS to 0, and rebuild the example.
```

## Configuring Syscfg

- Following Syscfg option allows flexibility to configure memory footprint based on required use case like: Number of DMA descriptors and buffering.

- Supported Options with default configuration

| Feature | Section | Description | Remarks/Default Setting |
|---------|---------|-------------|------------------------|
| Enable Packet Pool Allocation | TI Networking / Enet (CPSW) / Packet Pool Config | Flag to enable packet buffer memory allocation from enet utils library. | Default is true. |
| Number of Tx Packet | TI Networking / Enet (CPSW) / DMA channel config | No of Tx packets required for DMA channel | Default is 16. |
| Number of Rx Packet | TI Networking / Enet (CPSW) / DMA channel config | No of Rx packets required for DMA channel | Default is 40. |

## To Configure Static IP

Please refer to [Ethernet LwIP TCP/IP Static IP](../../components/networking/enet_lwip_static_ip.md).

## mbedTLS

Mbed TLS is a C library that implements cryptographic primitives, X.509 certificate manipulation and the SSL/TLS and DTLS protocols. It is distributed under the Apache License version 2.0. Its small code footprint makes it suitable for embedded systems.

- mbedTLS tag used for this example: mbedtls-2.13.1 (https://github.com/Mbed-TLS/mbedtls/tree/mbedtls-2.13.1)

## TLS certificates

Here we use self-signed openSSL generated certificates for TLS handshake. The mosquitto broker accepts certificates in PEM (.crt extension) format.

The certificates needed here are:
1. Server certificates
2. CA certificates

### Generate Certificates

- Create Key pair for Certificate authority (CA):
```
openssl genrsa -des3 -out ca.key 2048
```

- Generate certificate for CA using above key:
```
openssl req -new -x509 -days 1826 -key ca.key -out ca.crt
```

- Create server key pair:
```
openssl genrsa -out server.key 2048
```

- Self sign the Server certificates using CA key:
```
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 360
```

- Convert DER certificates to binary data (used in client_info.h):
```
xxd -i filename.der filename.h
```

## Mosquitto Broker Configurations

- Install Mosquitto broker and clients:
```
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
```

- Create a Password file with users (use "1234" as password):
```
./apps/mosquitto_passwd/mosquitto_passwd -c my_password_file am62dx_evm
./apps/mosquitto_passwd/mosquitto_passwd my_password_file pc_sub
./apps/mosquitto_passwd/mosquitto_passwd my_password_file pc_pub
```

## Steps to Run the Example

### Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS Projects Page](#ccs_projects_page)).
- When using makefiles to build, note the required combination and build using
  make command (see [Makefile Build Page](#makefile_build_page)).

### HW Setup

```{note}
Make sure you have setup the EVM with cable connections as shown in [EVM Setup Page](#evm_setup_page). In addition do below steps.
```

### Create a network between EVM and host PC

- The EVM will get an IP address statically (192.168.1.3), so make sure to connect the other end of the cable to a linux PC (192.168.1.2) running the mosquitto broker.
- To check the router connection with host PC, recommend to disconnect all other networking connections on the PC.

### Steps to execute

1. On a linux terminal, launch the broker: `./src/mosquitto -c my_mosquitto.conf -v`

2. Run the example on the TI Sitara device ({{ VAR_SOC_NAME }}).

3. Try to reach the EVM using ping:
```
ping 192.168.1.3
```

4. The client (192.168.1.3) will attempt to make a connection with the broker (192.168.1.2) and after the TLS handshake is complete, the broker logs will display a message for new connection.

5. In another linux terminal, publish data to a topic:
```
sudo LD_LIBRARY_PATH=./lib ./client/mosquitto_pub -h 192.168.1.2 -u pc_pub -P 1234 -t topic_qos1 --cafile /etc/mosquitto/ca_certificates/ca.crt --cert {PATH}/mosquitto/certs/server.crt --key {PATH}/mosquitto/certs/server.key --tls-version tlsv1.2 -m "helloworld"
```

### Sample Output

```
==========================
  CPSW LWIP MQTT + TLS
==========================
Enabling clocks!
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:23 Ver:01 <-> 'dp83867' : OK
PHY 0 is alive
Starting lwIP, local interface IP is Statically assigned
Host MAC address-0 : ac:1f:0f:84:0c:70
[LWIPIF_LWIP] NETIF INIT SUCCESS
Enet IF UP Event. Local interface IP:192.168.1.3
Network is UP ...
MQTT Client connection accepted
MQTT client "test" subscribed to topic: topic_qos1
MQTT client "test" data received: helloworld, data len: 10 bytes
```

## Troubleshooting issues

::::{only} SOC_AM62DX
- If you see MAC address as `00:00:00:00:00:00`, likely you are using a very early Si sample which does not have MAC address "fused" in. Open file `source/networking/.meta/enet_cpsw/templates/am62dx/enet_soc_cfg.c.xdt` and uncomment `#define ENET_MAC_ADDR_HACK (TRUE)`, then rebuild.
::::

- If you see a valid, non-zero MAC address and continuously seeing "Waiting for network UP..." prints in UART terminal, make sure you see `Enet IF UP Event.` message; if not, check the ethernet cable.

## See Also

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62DX
[Networking](../../components/networking/networking.rst)
::::
