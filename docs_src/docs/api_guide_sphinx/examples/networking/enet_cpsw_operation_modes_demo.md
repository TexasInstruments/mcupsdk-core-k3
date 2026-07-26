# Enet CPSW Operation Modes Demo

## Introduction

- CPSW operates in two modes
 - Switch Mode - packet forwarding is enabled and packets are forwarded to Host + Other MAC ports. This is the default configuration for CPSW.
 - MAC mode - packets are only given to the Host port and are not forwarded to other MAC Ports.


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM263PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X or SOC_AM62PX
   **CPSW DUAL MAC Mode**

   - In this mode, both the MAC ports of {{ VAR_SOC_NAME }} are configured to be in MAC mode.
   - This mode requires two Network interfaces to operate.
   - It is recommended to use two separate subnets for working with DUAL MAC.
   - A single implementation of network interface and shared pool is used for both the Netifs.
   - Dual MAC feature is illustrated by the below image:

   ```{figure} ../../images/examples/dual_mac_operation.png
   :align: center

   **DUAL MAC Operation**
   ```
::::


## See Also

[Ethernet And Networking](../../components/networking/networking.rst)
