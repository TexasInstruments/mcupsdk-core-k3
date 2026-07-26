Ethernet And Networking
=========================

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   networking_lwip
   enet_cpsw_tsn_gptp_apiguide
   ../../examples/networking/enet_cpsw_tsn_gptp
   enet_lld/enet_lld_top
   enet_cpsw_avtp_apiguide
   enet_cpsw_lldp_apiguide
   networking_features

.. only:: SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X or SOC_AM62LX

   Overview
   --------

   Advances in automated factories and smart vehicles require advanced networking capabilities, real-time processing and more advanced motor-control topologies. TI Networking solution packaged with the SDK provide a rapidly growing need for Sitara MCU to out space traditional MCUs and deliver processor-like capabilities. Networking is a broad terms used to cover Ethernet (IEEE 802.3), EtherCAT Profinet and other ethernet-like communication protocols used in industrial, automotive and other general use cases.

   .. image:: ../../images/networking/networking_apps.png
      :alt: Figure: Industrial And Automotive Networking Applications

   This document covers driver software architecture, Application Programming Interfaces (API), protocol stack usage, **LwIP** (`Light Weight IP stack <https://savannah.nongnu.org/git/?group=lwip>`__), examples and demos that are packaged in the SDK. The out-of-box Ethernet (CPSW) Examples enables fast on-board and accelerates the development cycle. This document also provides API guide for low level Ethernet, Industrial communication protocols drivers along with Layer-2 (low level) examples to enable advanced users to integrate the custom stack.

   **Networking is supported using following two hardware Peripherals:**

   - Common Port SWitch (**CPSW**) : CPSW subsystem provides IEEE 802.3 standard Ethernet gigabit speed packet communication for the device and can also be configured as an Ethernet switch. CPSW supports RGMII and RMII Interfaces.

   .. only:: SOC_AM64X or SOC_AM243X

      - Programmable Real-Time Unit and Industrial Communication Subsystem - Gigabit (**PRU-ICSSG**) : PRU-ICSSG is firmware programmable and can take on various personalities like Industrial Communication Protocol Switch (for protocols like EtherCAT, Profinet, EtherNet/IP), Ethernet Switch, Ethernet MAC, Industrial Drives, etc. PRU-ICSSG supports RGMII and MII modes.

   .. only:: SOC_AM62PX

      To know more about the hardware peripherals, please refer to datasheet and Technical Reference Manual (TRM) on the product page:

      - `AM62P <https://www.ti.com/product/AM62P>`__

   .. only:: SOC_AM62X

      To know more about the hardware peripherals, please refer to datasheet and Technical Reference Manual (TRM) on the product page:

      - `AM62X <https://www.ti.com/product/AM620-Q1>`__

   Salient Features
   -----------------

   .. image:: ../../images/networking/netowrking_features.png
      :alt: Figure: Networking Software Features

   Software Components Overview
   ------------------------------

   Below is the software components overview highlighting mainly the components used in the Networking software development.

   .. only:: SOC_AM64X or SOC_AM243X or SOC_AM62DX or SOC_AM275X

      .. image:: ../../images/networking/networking_layer_with_mbedtls.png
         :alt: Figure: Networking Software Components Overview

   .. only:: SOC_AM263X or SOC_AM263PX or SOC_AM273X

      .. image:: ../../images/networking/cpdma_networking_block_diagram.png
         :alt: Figure: Networking Software Components Overview

   .. only:: SOC_AWR294X

      .. image:: ../../images/networking/netowrking_layer.png
         :alt: Figure: Networking Software Components Overview

   Examples and Demos
   --------------------

   You can find out-of-box examples and demos :doc:`here <../../examples/examples_networking>`.

   .. only:: SOC_AM263X or SOC_AM263PX or SOC_AM273X or SOC_AM243X or SOC_AM62DX or SOC_AM275X

      You can find ethernet performance data :doc:`here <enet_lld/enetlld_performance>`.

   It consists of below sub-modules

   - **Ethernet Driver** - :doc:`Enet-LLD <enet_lld/enet_lld_top>` - Ethernet Low-Level Driver providing interface for standard Ethernet MAC and switch using CPSW peripheral
   - **TCP/IP Stack** - :doc:`Lightweight IP (LwIP) <networking_lwip>`
   - **TSN Stack** - :doc:`Ethernet TSN and gPTP Stack - API and Integration Guide <enet_cpsw_tsn_gptp_apiguide>`
   - `Ethernet TSN gPTP Examples <../../examples/networking/enet_cpsw_tsn_gptp.html>`__

   .. only:: SOC_AM62DX or SOC_AM62X or SOC_AM62AX or SOC_AM275X

      - **AVB Stack** - :doc:`Ethernet CPSW AVTP - API and Integration Guide <enet_cpsw_avtp_apiguide>`
      - **LLDP Stack** - :doc:`Ethernet CPSW LLDP - API and Integration Guide <enet_cpsw_lldp_apiguide>`
