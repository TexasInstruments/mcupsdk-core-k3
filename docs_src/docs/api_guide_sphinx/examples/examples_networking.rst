Ethernet and Networking
=========================

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   networking/ethfw_server_and_client
   networking/enet_cpsw_loopback_example
   networking/enet_layer2_cpsw
   networking/enet_layer2_cpsw_switch
   networking/enet_cpsw_tsn_est_example
   networking/enet_cpsw_operation_modes_demo
   networking/enet_lwip_cpsw
   networking/enet_cpsw_tsn_gptp
   networking/enet_layer2_cpsw_fast_startup_autophy
   examples_networking_avb
   networking/enet_cpsw_est
   networking/enet_cpsw_avb_audio_playback
   networking/enet_cpsw_avb_audio_etherring_demo
   networking/enet_cpsw_tsn_media_clock_recovery
   networking/enet_lwip_socket
   networking/enet_lwip_tcpclient
   networking/enet_lwip_tcpserver
   networking/enet_lwip_udp_igmp
   networking/enet_lwip_udpclient
   networking/cpsw_lwip_https
   networking/cpsw_lwip_mqtt
   networking/enet_lwip_httpserver
   networking/enet_cpsw_tsn_gptp_tr
   networking/enet_cpsw_tsn_gptp_tt
   networking/enet_cpsw_tsn_gptp_bridge
   networking/enet_cpsw_gptp_lwip
   networking/enet_tsn_avtp_aes3_aaf_example
   networking/enet_cpsw_avtp_example
   networking/enet_cpsw_tsn_crf
   networking/enet_cpsw_tsn_crf_avtp
   networking/enet_cpsw_tsn_crf_autoamp_demo
   networking/enet_cpsw_lldp_example

This page lists all the examples related to Ethernet Communication.

.. only:: SOC_AM62PX

   **Layer 2 Examples on FreeRTOS**
      - :doc:`Enet CPSW Loopback Example <networking/enet_cpsw_loopback_example>`
      - :doc:`Enet Layer 2 CPSW SWITCH Example <networking/enet_layer2_cpsw_switch>`
      - :doc:`Enet Lwip CPSW Operating Modes Demo <networking/enet_cpsw_operation_modes_demo>`

   **TCP/IP Examples using LwIP Stack on FreeRTOS**
      - :doc:`Enet Lwip CPSW Example <networking/enet_lwip_cpsw>`
      - :doc:`Enet Lwip TCP Server Example on CPSW <networking/enet_lwip_tcpserver>`

   **Time-Sensitive Networking (TSN) Examples on FreeRTOS**
      - :doc:`Ethernet TSN CPSW gPTP TimeReceiver (gPTP Slave) Example <networking/enet_cpsw_tsn_gptp_tr>`
      - :doc:`Ethernet TSN CPSW gPTP TimeTransmitter (gPTP Master) Example <networking/enet_cpsw_tsn_gptp_tt>`
      - :doc:`Ethernet TSN CPSW gPTP Bridge Example <networking/enet_cpsw_tsn_gptp_bridge>`
      - :doc:`Ethernet TSN gPTP on CPSW along with LwIP stack <networking/enet_cpsw_gptp_lwip>`

   **Ethernet Firmware**
      - :doc:`Ethernet Firmware <networking/ethfw_server_and_client>`

.. only:: SOC_AM62AX

   **Ethernet Firmware**
      - :doc:`Ethernet Firmware <networking/ethfw_server_and_client>`

.. only:: SOC_AM62X

   **Layer 2 Examples on FreeRTOS**
      - :doc:`Enet CPSW Loopback Example <networking/enet_cpsw_loopback_example>`
      - :doc:`Enet Layer 2 CPSW Example <networking/enet_layer2_cpsw>`
      - :doc:`Enet Layer 2 CPSW SWITCH Example <networking/enet_layer2_cpsw_switch>`
      - :doc:`Enet CPSW EST Example <networking/enet_cpsw_tsn_est_example>`
      - :doc:`Enet Lwip CPSW Operating Modes Demo <networking/enet_cpsw_operation_modes_demo>`

   **TCP/IP Examples using LwIP Stack on FreeRTOS**
      - :doc:`Enet Lwip CPSW Example <networking/enet_lwip_cpsw>`

   **Time-Sensitive Networking (TSN) Examples on FreeRTOS**
      - :doc:`Ethernet TSN CPSW gPTP TimeReceiver (gPTP Slave) Example <networking/enet_cpsw_tsn_gptp_tr>`
      - :doc:`Ethernet TSN CPSW gPTP TimeTransmitter (gPTP Master) Example <networking/enet_cpsw_tsn_gptp_tt>`
      - :doc:`Ethernet TSN CPSW gPTP Bridge Example <networking/enet_cpsw_tsn_gptp_bridge>`
      - :doc:`Ethernet TSN gPTP on CPSW along with LwIP stack <networking/enet_cpsw_gptp_lwip>`

.. only:: SOC_AM275X

   **Layer 2 Examples on FreeRTOS**
      - :doc:`Enet CPSW EST Example <networking/enet_cpsw_tsn_est_example>`
      - :doc:`Enet Layer 2 CPSW Example <networking/enet_layer2_cpsw>`
      - :doc:`Enet Layer 2 CPSW SWITCH Example <networking/enet_layer2_cpsw_switch>`
      - :doc:`Enet CPSW Loopback Example <networking/enet_cpsw_loopback_example>`
      - :doc:`Enet Layer 2 CPSW Fast Startup Auto PHY Example <networking/enet_layer2_cpsw_fast_startup_autophy>`
      - :doc:`Enet Lwip CPSW Operating Modes Demo <networking/enet_cpsw_operation_modes_demo>`

   **TCP/IP Examples using LwIP Stack on FreeRTOS**
      - :doc:`Enet Lwip CPSW Example <networking/enet_lwip_cpsw>`

   **Audio Video Bridging (TSN) Examples on FreeRTOS**
      - :doc:`Audio Video Bridging Examples <examples_networking_avb>`

   **Time-Sensitive Networking (TSN) Examples on FreeRTOS**
      - :doc:`Ethernet TSN CPSW gPTP TimeReceiver (gPTP Slave) Example <networking/enet_cpsw_tsn_gptp_tr>`
      - :doc:`Ethernet TSN CPSW gPTP TimeTransmitter (gPTP Master) Example <networking/enet_cpsw_tsn_gptp_tt>`
      - :doc:`Ethernet TSN CPSW gPTP Bridge Example <networking/enet_cpsw_tsn_gptp_bridge>`
      - :doc:`Ethernet TSN gPTP on CPSW along with LwIP stack <networking/enet_cpsw_gptp_lwip>`

.. only:: SOC_AM62DX

   **Layer 2 Examples on FreeRTOS**
      - :doc:`Enet CPSW Loopback Example <networking/enet_cpsw_loopback_example>`
      - :doc:`Enet Layer 2 CPSW Example <networking/enet_layer2_cpsw>`
      - :doc:`Enet Layer 2 CPSW SWITCH Example <networking/enet_layer2_cpsw_switch>`
      - :doc:`Enet CPSW EST Example <networking/enet_cpsw_tsn_est_example>`
      - :doc:`Enet Layer 2 CPSW Fast Startup Example <networking/enet_layer2_cpsw_fast_startup_autophy>`

   **TCP/IP Examples using LwIP Stack on FreeRTOS**
      - :doc:`Enet Lwip CPSW Example <networking/enet_lwip_cpsw>`
      - :doc:`Enet CPSW Operation Modes Demo <networking/enet_cpsw_operation_modes_demo>`
      - :doc:`Enet Lwip Socket Example <networking/enet_lwip_socket>`
      - :doc:`Enet Lwip TCP Client Example <networking/enet_lwip_tcpclient>`
      - :doc:`Enet Lwip TCP Server Example on CPSW <networking/enet_lwip_tcpserver>`
      - :doc:`Enet Lwip UDP IGMP Server Example <networking/enet_lwip_udp_igmp>`
      - :doc:`Enet Lwip UDP Client Example <networking/enet_lwip_udpclient>`
      - :doc:`CPSW Lwip HTTPS Server Example <networking/cpsw_lwip_https>`
      - :doc:`CPSW Lwip MQTT Client Example <networking/cpsw_lwip_mqtt>`

   **TCP/IP Examples using LwIP Stack on Baremetal (NoRTOS)**
      - :doc:`Enet LwIP HTTP Server On Bare Metal (No-RTOS) <networking/enet_lwip_httpserver>`

   **Time-Sensitive Networking (TSN) Examples on FreeRTOS**
      - :doc:`Ethernet TSN CPSW gPTP TimeReceiver (gPTP Slave) Example <networking/enet_cpsw_tsn_gptp_tr>`
      - :doc:`Ethernet TSN CPSW gPTP TimeTransmitter (gPTP Master) Example <networking/enet_cpsw_tsn_gptp_tt>`
      - :doc:`Ethernet TSN CPSW gPTP Bridge Example <networking/enet_cpsw_tsn_gptp_bridge>`
      - :doc:`Ethernet TSN gPTP on CPSW along with LwIP stack <networking/enet_cpsw_gptp_lwip>`
      - :doc:`Enet TSN AVTP AES3 AAF Example <networking/enet_tsn_avtp_aes3_aaf_example>`
      - :doc:`Ethernet AVTP Example <networking/enet_cpsw_avtp_example>`
      - :doc:`Ethernet CRF Master Example <networking/enet_cpsw_tsn_crf>`
      - :doc:`Ethernet AVTP and CRF Example <networking/enet_cpsw_tsn_crf_avtp>`
      - :doc:`Ethernet Autoamplifer with CRF Demo <networking/enet_cpsw_tsn_crf_autoamp_demo>`

   **LLDP Example on FreeRTOS**
      - :doc:`Ethernet LLDP Example <networking/enet_cpsw_lldp_example>`

   **Ethernet Firmware**
      - :doc:`Ethernet Firmware <networking/ethfw_server_and_client>`

.. only:: SOC_AM62LX

   **Layer 2 Examples on FreeRTOS**
      - :doc:`Enet CPSW Loopback Example <networking/enet_cpsw_loopback_example>`
      - :doc:`Enet Layer 2 CPSW SWITCH Example <networking/enet_layer2_cpsw_switch>`

   **TCP/IP Examples using LwIP Stack on FreeRTOS**
      - :doc:`Enet Lwip CPSW Example <networking/enet_lwip_cpsw>`

   **Time-Sensitive Networking (TSN) Examples on FreeRTOS**
      - :doc:`Ethernet TSN gPTP Examples <networking/enet_cpsw_tsn_gptp>`
