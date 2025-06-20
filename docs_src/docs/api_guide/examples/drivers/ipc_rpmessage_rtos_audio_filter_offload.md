# IPC RP Message RTOS Audio Filter Offload {#EXAMPLES_DRIVERS_IPC_RPMESSAGE_RTOS_AUDIO_FILTER_OFFLOAD}

[TOC]

# Introduction

This example shows usage of RP Message APIs to offload the audio processing from Master Core to DSP Core by exchanging messages between RTOS/NORTOS CPUs

In this example,
- All cores on startup after driver initialization wait for getting in sync
- The sender can be any RTOS/NORTOS CPUs.
- DSP Core services the Master Core messages which points to the buffer
  containing audio data and parameters of the signal chain.
- The DSP application on receiving the message from Master Core would trigger the audio filter
  signal chain on the buffer with the parameters and sends an acknowledgement to Master Core with the
  CPU task load.
- The master core will send the input data, output filtered data and the metrics to the host utility using Socket Communication
- The DSP signal chain operating on the data would be as follows

Figure below shows the signal chain, where, the input is eight-channel, 256 block size audio data in channel interleaved
form. The output is the processed eight-channel, 256 block size audio data in channel interleaved form.

The incoming audio stream is assumed to be sampled at 48KHz.

\imageStyle{ipc_rpmsg_linux_audio_filter_signalchain.png,width:100%}
\image html ipc_rpmsg_linux_audio_filter_signalchain.png "TISP audio signal chain"

## Configuring CasadeBiquad Low-Pass Filter:
This filter is a three-stage, direct form 1 design with a low-pass cut-off frequency of 10KHz.

The filter coefficients were obtained through signal_chain.py script in
${SDK_INSTALL_PATH}/srouce/tisp/test/TISP_idat_gen/audio_signal_chain/cascadeBiquad_FIR/ folder.

"cascadeBiquad0CoeffCase5" array in ${SDK_INSTALL_PATH}/examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload/
am62dx-evm/c75ss0-0_freertos/ti-c7000/TISP_cascadeBiquad_FIR_test.cpp handles the coefficients that
determines the cut-off and type of this filter.

The module expects channel interleaved data as input and outputs the processed data in channel interleaved form as well.
Please refer to TISP's and DSPLIB's documentation for more details on the cascadeBiquad filter's implementation.

## Configuring CasadeBiquad High-Pass Filter:
This filter is also a three-stage, direct form 1 design with a high-pass cut-off frequency of 2KHz.

The filter coefficients were obtained through signal_chain.py script in
${SDK_INSTALL_PATH}/srouce/tisp/test/TISP_idat_gen/audio_signal_chain/cascadeBiquad_FIR/ folder.

"cascadeBiquad1CoeffCase5" array in ${SDK_INSTALL_PATH}/examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload/
am62dx-evm/c75ss0-0_freertos/ti-c7000/TISP_cascadeBiquad_FIR_test.cpp handles the coefficients that
determines the cut-off and type of this filter.

The module expects channel interleaved data as input and outputs the processed data in channel interleaved form as well.

## Configuring FIR Low-Pass Filter:
This filter is a 64-tap low-pass filter with a cut-off frequency of 8KHz.

The filter coefficients were obtained through signal_chain.py script in
${SDK_INSTALL_PATH}/srouce/tisp/test/TISP_idat_gen/audio_signal_chain/cascadeBiquad_FIR/ folder.

"filterCoeffCase5" array in ${SDK_INSTALL_PATH}/examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload/
am62dx-evm/c75ss0-0_freertos/ti-c7000/TISP_cascadeBiquad_FIR_test.cpp handles the coefficients that
determines the cut-off and type of this filter.

The expects channel de-interleaved data as input and outputs the processed data in channel de-interleaved form as well.
Please refer to TISP's and DSPLIB's documentation for more details on the FIR filter's implementation.

## Real FFT and IFFT Real:
These modules perform FFT and IFFT of a real signal [numChannels, numSamples].
Please  refer to TISP's and FFTLIB's documentation for more implementation details.

## Matrix Transpose:
This module is placed appropriately to convert the data format between de-interleaved and interleaved formats within the signal chain.
Please refer to TISP's and DSPLIB's documentation for more details on the implementation.

# Supported Combinations

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload

\endcond

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see \ref MAKEFILE_BUILD_PAGE). This will build all the dependant CPU makefiles as well.

## Create a network between EVM and host PC

- The EVM will get an IP address using DHCP, so make sure to connect the other end of the cable
connected to a network which has a DHCP server running.

- To get started one can create a simple local network
  between the EVM and the host PC by using a home broadband/wifi router as shown below.
  Most such routers run a DHCP server

  \imageStyle{lwip_example_01.png,width:30%}
  \image html lwip_example_01.png Local network between PC and EVM

- To check the router connection with host PC, it is recommended to disconnect all other networking conenctions
  on the PC, sometimes you may need to disable firewall SW, and make sure the router is able
  to assign a IP address to your host PC.

- After we run the example on the EVM (next step), the EVM will similarly be assigned a IP address, and then host
  can communicate with the EVM using the assigned IP address.

- To enable static IP, set the static IP in the ipAddr variable in the App_setupNetif() before passing it as argument
  to initiate the netif, and stop the dhcp from starting in the App_allocateIPAddress() function.

## Run the example

- To run this demo, a sample audio of 8 channel need to be copied to SD card mentioning `input.wav` as the file name.
- Run the host utility script provided in below mentioned path which act as the client to connect to the server hosted by EVM
    ```
    cd ${SDK_INSTALL_PATH}/examples/drivers/ipc/ipc_rpmsg_rtos_audio_filter_offload/master/host_interface/audmon.py
    ```
- Run the application on both master and dsp core
- Only ethernet mode data visualisation is supported by the application
- Filter can toggled ON/OFF using the host utility

## Host-Side Utility
```
Refer: https://github.com/TexasInstruments/rpmsg-dma/blob/main/example/audio_offload/host%20utility/README.md
```

- Run the host utility by providing the ip address given by evm as the argument as shown below
    \code
    python audmon.py ip 192.168.1.100
    \endcode
  "192.168.1.100" should be replaced with EVM IP.

# See Also

\ref DRIVERS_IPC_RPMESSAGE_PAGE

# Sample Output

\code

Starting IPC RPMSG DSP OFFLOAD example on main core 0
==========================
  CPSW LWIP TCP SERVER
==========================
Enabling clocks!
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:0 From 4 To 1
Open MAC port 1
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:23 Ver:01 <-> 'DP83867' : OK
Open MAC port 2
EnetPhy_bindDriver: PHY 3: OUI:080028 Model:23 Ver:01 <-> 'DP83867' : OK
PHY 0 is alive
PHY 3 is alive
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
Host MAC address-0 : 04:25:e8:65:0b:4c
[0]Enet IF UP Event. Local interface IP:0.0.0.0
[LWIPIF_LWIP] Enet has been started successfully
[0]Waiting for network UP ...
[0]Waiting for network UP ...
Cpsw_handleLinkUp: Port 1: Link up: 1-Gbps Full-Duplex
MAC Port 1: link up
[0]Network Link UP Event
[0]Waiting for network UP ...
[0]Waiting for network UP ...
[0]Waiting for network UP ...
[0]Waiting for network UP ...
[0]Waiting for network UP ...
[0]Enet IF UP Event. Local interface IP:192.168.1.100
Network is UP ...
[LOG] Accepted new connection 801311C0
[CMD] Accepted new connection 80131180
[INP] Accepted new connection 80131140
[OUT] Accepted new connection 80131100
All Connections are Up ...

==========================
   WAV FILE META DATA
==========================
ChunkID: RIFF
ChunkSize: 92178526
Format: WAVE
Subchunk1ID: fmt
Subchunk1Size: 40
AudioFormat: 65534
NumChannels: 8
SampleRate: 48000
ByteRate: 768000
BlockAlign: 16
BitsPerSample: 16
Subchunk2ID:
Subchunk2Size: 1599
[IPC] Cores are in sync ...
All Connections are Closed ...

\endcode
