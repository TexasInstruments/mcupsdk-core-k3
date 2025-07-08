# Ethernet TSN gPTP on CPSW along with NetxDuo stack {#EXAMPLES_ENET_NETXDUO_CPSW_GPTP}

[TOC]

# Introduction
This ethernet TSN example illustrates the usage of gPTP IEEE 802.1AS stack with CPSW peripheral with NetxDuo network stack running in parallel. Here we demonstrate a simple TCP echo server using the native NetxDuo APIs.
On the gPTP front, the application used here supports all the below modes:
    - gPTP End-Point time_transmitter mode (i.e. master mode)
    - gPTP End-Point time_receiver mode (i.e. slave mode)
    - gPTP Bridge mode

In this example, we use two Rx and two Tx DMA channel, one Rx and one Tx channel specific to gPTP traffic and one Rx and one Tx channel specific to non-gPTP traffic, this is handled by NetxDuo stack.

  \imageStyle{gPTPwithNetxDuo.png,width:20%}
  \image html gPTPwithNetxDuo.png 

Please refer to the \ref EXAMPLES_ENET_NETXDUO_CPSW_TCPSERVER page for NetxDuo TCP echo server documentation.

Please refer to the \ref EXAMPLES_ENET_CPSW_TSN_GPTP page for the above gPTP mode specific documentation.

See also :\ref ENET_CPSW_TSN_GPTP for gPTP stack documentation.



# Supported Combinations

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 threadx
 Toolchain      | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/netxduo/enet_netxduo_cpsw_gptp

# Steps to Run the Example

## Prerequisites
-  EVM Board
- Cat6 ethernet cable
- PC with Linux Ubuntu OS (or any PC running bash shell) and PTP capable network card
- Install `linuxptp`
\code
$ sudo apt-get install linuxptp
$ ptp4l -v
\endcode
- Configure linuxptp
\code
$ wget https://raw.githubusercontent.com/richardcochran/linuxptp/v4.3/configs/gPTP.cfg -O ~/gptp_config.cfg
\endcode
\attention Change the value of `priority1` in ~/gptp_config.cfg file to `100`, to enforce it to gPTP master

\attention For some network cards, there is a bug with internal propagation delay. So, in those cases you might need to increase the `neighborPropDelayThresh` in ptp_config.cfg as below-

\code
$ cat ~/gptp_config.cfg
\#
\# 802.1AS example configuration containing those attributes which
\# differ from the defaults.  See the file, default.cfg, for the
/# complete list of available options.
/#
[global]
gmCapable               1
priority1               100
priority2               248
logAnnounceInterval     0
logSyncInterval         -3
syncReceiptTimeout      3
neighborPropDelayThresh 10000
min_neighbor_prop_delay -20000000
assume_two_step         1
path_trace_enabled      1
follow_up_info          1
transportSpecific       0x1
ptp_dst_mac             01:80:C2:00:00:0E
network_transport       L2
delay_mechanism         P2P

\endcode
- `priority1` in ~/gptp_config.cfg file can be changed to make the Linux PC master or slave. Lower the number higher the priority to become master.

Please refer to the \ref EXAMPLES_ENET_NETXDUO_CPSW_TCPSERVER page to start a TCP client on PC.


## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## HW Setup

\note Make sure you have setup the EVM with cable connections as shown here, \ref EVM_SETUP_PAGE.
      In addition do below steps.

## Create a network between EVM and host PC
EVM and PC has to connected directly as shown below using CAT6 or CAT5 cable. If there is ethernet switch placed in between, make sure the switch is gPTP capable. Connect both EVM and PC to a DHCP server to get the IP addressess. 
  \imageStyle{Lwip-gPTP-setup.png,width:30%}
  \image html Lwip-gPTP-setup.png Local network between PC and EVM
 
PORT1 instead of PORT0 on EVM can be used as well.

## Run the example
  
\attention If you need to reload and run again, a CPU power-cycle is MUST

- Execute the below command in PC terminal to start the gPTP on linux: 
\code
$ sudo ptp4l -i eno1 -m -l 6 -q -f ~/gptp_config.cfg
\endcode
Replace eno1 with the network interface connected to your PC.

- After the evm gets the IP address, you can ping the IP address to verify the connection.
- Execute the below command in PC terminal to start a TCP communication with the EVM.
\code
ncat <ip-address-of-evm> 8888
\endcode
- You will see logs in the UART terminal as shown in the next section. PC side logs are with Intel i210 card.
- Launch a CCS debug session and run the example executable, see \ref CCS_LAUNCH_PAGE
- Connect board and PC as mentioned in "HW Setup" above.

## Sample Log Output
### PC Output
\code
$ sudo ptp4l -i eno1 -m -l 6 -q -f ~/gptp_config.cfg
ptp4l[7727.045]: selected /dev/ptp0 as PTP clock
ptp4l[7727.088]: port 1: INITIALIZING to LISTENING on INIT_COMPLETE
ptp4l[7727.088]: port 0: INITIALIZING to LISTENING on INIT_COMPLETE
ptp4l[7727.088]: port 1: link down
ptp4l[7727.088]: port 1: LISTENING to FAULTY on FAULT_DETECTED (FT_UNSPECIFIED)
ptp4l[7727.127]: selected local clock 6805ca.fffe.c87ac2 as best master
ptp4l[7727.127]: assuming the grand master role
ptp4l[7729.260]: port 1: link up
ptp4l[7729.300]: port 1: FAULTY to LISTENING on INIT_COMPLETE
ptp4l[7732.330]: port 1: new foreign master f4844c.fffe.fbc042-1
ptp4l[7732.354]: port 1: LISTENING to MASTER on ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES
ptp4l[7732.354]: selected local clock 6805ca.fffe.c87ac2 as best master
ptp4l[7732.354]: assuming the grand master role
\endcode
### DUT output
\code
===============================
     CPSW NETXDUO TSN GPTP     
===============================
Enabling clocks!
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:2 From 4 To 2 
Open MAC port 1
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:23 Ver:01 <-> 'DP83867' : OK

Open MAC port 2
EnetPhy_bindDriver: PHY 1: OUI:080028 Model:23 Ver:01 <-> 'DP83867' : OK

PHY 0 is alive
PHY 1 is alive
Logger_task: started
EnetApp_uniconfTask: dbname: NULL
unibase-1.1.4
INF:cbase:tilld0: has mac: 70:FF:76:1D:EC:F2
INF:cbase:tilld1: has mac: 00:00:00:00:00:00
INF:uconf:simpledb_open:no data is imported
INF:uconf:get_next_nameid:a new mod=xl4-data, enum=0
INF:uconf:get_next_nameid:a new mod=xl4-extmod, enum=1
INF:uconf:uc_hwal_open:
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=-1 numRxChannels=1 dmaRxChId=-1 nTxPkts=0 nRxPkts=0 pktSize=0
INF:uconf:get_next_nameid:a new mod=ietf-interfaces, enum=2
INF:uconf:get_next_nameid:a new mod=ieee1588-ptp-tt, enum=3
INF:uconf:get_next_nameid:a new mod=ieee802-dot1q-bridge, enum=4
INF:uconf:get_next_nameid:a new mod=excelfore-tsn-remote, enum=5
INF:uconf:get_next_nameid:a new mod=excelfore-netconf-server, enum=6
INF:uconf:get_next_nameid:a new mod=ietf-netconf-monitoring, enum=7
INF:uconf:get_next_nameid:a new mod=ietf-yang-library, enum=8
INF:uconf:get_next_nameid:a new mod=ieee802-dot1ab-lldp, enum=9
INF:uconf:get_next_nameid:a new mod=ieee802-dot1q-tsn-config-uni, enum=10
INF:uconf:get_next_nameid:a new mod=excelfore-config-uni, enum=11
Start: uniconf_task
EnetApp_gptpYangConfig:domain=0
INF:uconf:create_semname_with_dbname:null dbname is specified.
INF:uconf:000000-133949:uniconf_main:uniconf started
INF:cbase:cb_lld_task_create: uniconf_hwal_thread stack_size=16384
INF:cbase:cb_lld_task_create: uniconf_task stack_size=16384
INF:uconf:get_next_nameid:a new extmod=xl4gptp, enum=0
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_SINGLE_CLOCK_MODE=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_USE_HW_PHASE_ADJUSTMENT=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_FREQ_OFFSET_IIR_ALPHA_START_VALUE=1
INF:uconf:create_semname_with_dbname:null dbname is specified.
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_FREQ_OFFSET_IIR_ALPHA_STABLE_VALUE=4
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_PHASE_OFFSET_IIR_ALPHA_START_VALUE=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_PHASE_OFFSET_IIR_ALPHA_STABLE_VALUE=4
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_MAX_DOMAIN_NUMBER=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_CLOCK_COMPUTE_INTERVAL_MSEC=100
INF:gptp:000000-203612:gptpman_run:max_domains=1, max_ports=2
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=1 numRxChannels=1 dmaRxChId=1 nTxPkts=16 nRxPkts=32 pktSize=1536
INF:cbase:rxChId 1 has owner dmaRxShared 0
INF:gptp:000000-205259:dev:tilld0 open success
INF:cbase:tilld1: alloc mac: 70:FF:76:1D:EC:E3
INF:gptp:000000-205334:dev:tilld1 open success
INF:gptp:000000-205433:gptpnet_init:supportRtNotice=0 tout_interval=125000000Ns
INF:gptp:000000-205826:gptpnet_init:Open lldtsync OK!
INF:gptp:000000-206082:IEEE1588-2019 performance monitoring disabled.
INF:gptp:000000-206930:pp_glb_init: use-mgt-log-gptp-cap-interval=0
Start: gptp2d_task
EnetApp_initTsn:TSN app start done!
Waiting for link up...
INF:gptp:000000-218507:current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
INF:gptp:000000-219668:pp_glb_init: use-mgt-log-gptp-cap-interval=0
INF:gptp:000000-220047:current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
INF:gptp:000000-221137:pp_glb_init: use-mgt-log-gptp-cap-interval=0
INF:gptp:000000-221511:current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
INF:gptp:000000-222951:static_domains_init: instance=0, di=0, pi=1, currentToutIntervalNs=125000000
INF:gptp:000000-222961:syncIntervalNs=125000000, announceInterval=0,pdelayReqInterval=1000000000,gPtpCapableMessageInterval=0
INF:gptp:000000-222969:static_domains_init: instance=0, di=0, pi=2, currentToutIntervalNs=125000000
INF:gptp:000000-222978:syncIntervalNs=125000000, announceInterval=0,pdelayReqInterval=1000000000,gPtpCapableMessageInterval=0
INF:uconf:ydbi_get_item_ifk3vk0:no data
INF:uconf:ydbi_get_item_ifk3vk0:no data
INF:uconf:ydbi_get_item_ifk3vk0:no data
INF:gptp:000000-223167:onenet_activate:tilINF:gptp:000000-252181:domainIndex=0, GM changed old=00:00:00:00:00:00:00:00, new=70:FF:76:FF:FE:1D:EC:F2
INF:gptp:000000-252312:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=2
Waiting for link up...
Cpsw_handleLinkUp: Port 1: Link up: 1-Gbps Full-Duplex

MAC Port 1: link up
INF:cbase:000002-821759:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!! (70us since link change event)
INF:cbase:cbl_query_response:tilld1 link DOWN !!!!
INF:gptp:000002-874329:index=1 speed=1000, duplex=full
WRN:gptp:000002-874728:gptpgcfg_link_check:can't read speed
Cpsw_handleLinkUp: Port 2: Link up: 1-Gbps Full-Duplex

MAC Port 2: link up
INF:cbase:000002-922033:cbl_query_response:tilld1: link UP, speed=1000, duplex=1 !!!! (68us since link change event)
INF:gptp:000002-999265:index=2 speed=1000, duplex=full
WRN:gptp:000002-999619:waiting_for_pdelay_interval_timer_proc:portIndex=2, sourcePortIdentity=68:05:CA:FF:FE:8D:90:98, thisClock=70:FF:76:FF:FE:1D:EC:F2, neighborPropDelay=208
INF:gptp:000002-999626:waiting_for_pdelay_interval_timer_proc:portIndex=2, not asCapable
INF:gptp:000003-999226:waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=2
INF:gptp:000003-999234:set asCapable for domainIndex=0, portIndex=2
INF:gptp:000003-999601:gptpgcfg_set_asCapable:domainInde=0, portIndex=2, ascapable=1
INF:gptp:000003-999822:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000003-999831:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:000003-999912:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000004-124089:setSyncTwoStep_txSync:domainIndex=0, portIndex=2, sync gap=4125msec, tsync_ts_threshold=175msec
INF:gptp:000004-124218:setFollowUp_txFollowUp:domainIndex=0, portIndex=2, fup gap=4125msec tsync_ts_threshold=175msec
Waiting for link up...
INF:gptp:000004-532692:domainIndex=0, GM changed old=70:FF:76:FF:FE:1D:EC:F2, new=68:05:CA:FF:FE:8D:90:98
INF:gptp:000004-532751:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=0
INF:gptp:000004-532830:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000004-532838:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:000004-542487:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-542587:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=1748626152920716585
INF:gptp:000004-542926:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-543027:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=1748626152920713176
INF:gptp:000004-543161:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=1748626152920713176nsec
INF:gptp:000004-543489:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-543589:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=1748626152920709766
INF:gptp:000004-543722:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=1748626152920709766nsec
INF:gptp:000004-560819:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-560919:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-3497252305841437880
INF:gptp:000004-561255:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-561354:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-3497252305841441285
INF:gptp:000004-561487:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-3497252305841441285nsec
INF:gptp:000004-561697:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-561797:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-3497252305841444697
INF:gptp:000004-561930:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-3497252305841444697nsec
INF:gptp:000004-562141:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-562241:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-3497252305841448104
INF:gptp:000004-562INF:gptp:000004-580324:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-580423:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=6034022067180577417
INF:gptp:000004-580757:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-580856:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=6034022067180574010
INF:gptp:000004-580989:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=6034022067180574010nsec
INF:gptp:000004-581200:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-581300:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=6034022067180570609
INF:gptp:000004-581432:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=6034022067180570609nsec
INF:gptp:000004-581642:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-581742:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=6034022067180567203
INF:gptp:000004-581875:doINF:gptp:000004-600186:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-600285:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=7068055683684122551
INF:gptp:000004-600620:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-600719:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=7068055683684119153
INF:gptp:000004-600851:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=7068055683684119153nsec
INF:gptp:000004-601062:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-601162:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=7068055683684115745
INF:gptp:000004-601295:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=7068055683684115745nsec
INF:gptp:000004-601505:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-601605:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=7068055683684112336
INF:gptp:000004-601738:doINF:gptp:000004-620333:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-620433:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-8272268932028334687
INF:gptp:000004-620767:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-620867:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-8272268932028338087
INF:gptp:000004-621001:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-8272268932028338087nsec
INF:gptp:000004-621219:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-621319:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-8272268932028341494
INF:gptp:000004-621453:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-8272268932028341494nsec
INF:gptp:000004-621663:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-621763:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-8272268932028344900
INF:gptp:000004-621INF:gptp:000004-641122:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-641222:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7608824838611442492
INF:gptp:000004-641566:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-641666:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7608824838611445900
INF:gptp:000004-641798:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-7608824838611445900nsec
INF:gptp:000004-642010:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-642110:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7608824838611449307
INF:gptp:000004-642243:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-7608824838611449307nsec
INF:gptp:000004-642570:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-642670:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7608824838611452708
INF:gptp:000004-642INF:gptp:000004-660993:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-661093:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5307552747335111500
INF:gptp:000004-661542:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-661642:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5307552747335114906
INF:gptp:000004-661775:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-5307552747335114906nsec
INF:gptp:000004-661985:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-662086:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5307552747335118308
INF:gptp:000004-662219:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-5307552747335118308nsec
INF:gptp:000004-662429:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-662529:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5307552747335121714
INF:gptp:000004-662INF:gptp:000004-680465:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-680564:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=5566933831261875171
INF:gptp:000004-680898:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-680998:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=5566933831261871761
INF:gptp:000004-681132:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=5566933831261871761nsec
INF:gptp:000004-681342:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-681441:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=5566933831261868362
INF:gptp:000004-681574:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=5566933831261868362nsec
INF:gptp:000004-681784:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-681884:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=5566933831261864955
INF:gptp:000004-682018:doINF:gptp:000004-700236:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-700336:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7641982502675812398
INF:gptp:000004-700670:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-700769:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7641982502675815805
INF:gptp:000004-700902:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-7641982502675815805nsec
INF:gptp:000004-701113:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-701213:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7641982502675819213
INF:gptp:000004-701346:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-7641982502675819213nsec
INF:gptp:000004-701557:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-701657:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-7641982502675822611
INF:gptp:000004-701INF:gptp:000004-722391:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-722490:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5009133770755777639
INF:gptp:000004-722824:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-722924:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5009133770755781038
INF:gptp:000004-723058:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-5009133770755781038nsec
INF:gptp:000004-723268:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-723367:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5009133770755784450
INF:gptp:000004-723501:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-5009133770755784450nsec
INF:gptp:000004-723720:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-723819:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=-5009133770755787858
INF:gptp:000004-723INF:gptp:000004-742647:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-742746:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=3179582018627205187
INF:gptp:000004-743082:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-743181:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=3179582018627201779
INF:gptp:000004-743314:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=3179582018627201779nsec
INF:gptp:000004-743533:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-743632:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=3179582018627198377
INF:gptp:000004-743766:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=3179582018627198377nsec
INF:gptp:000004-743976:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:000004-744077:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=3179582018627194967
INF:gptp:000004-744210:doINF:gptp:000005-124120:port_announce_information:current_condition:domainIndex=0, portIndex=2, CT=5125000000, ARTT=7742187500, SRTT=5117187500
INF:gptp:000005-124183:domainIndex=0, GM changed old=68:05:CA:FF:FE:8D:90:98, new=70:FF:76:FF:FE:1D:EC:F2
INF:gptp:000005-124217:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=0
INF:gptp:000005-124413:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=2
INF:gptp:000005-124538:gm_stable:gm_stable_proc:domainIndex=0
INF:gptp:000005-249084:setSyncTwoStep_txSync:domainIndex=0, portIndex=2, sync gap=750msec, tsync_ts_threshold=175msec
INF:gptp:000005-249208:setFollowUp_txFollowUp:domainIndex=0, portIndex=2, fup gap=750msec tsync_ts_threshold=175msec
Waiting for address from DHCP server on primary interface...
Local Interface IP is: 192.168.50.117
Socket created
Listening on port 8888

\endcode

# See Also

\ref NETWORKING |
\ref EXAMPLES_ENET_CPSW_TSN_GPTP_BRIDGE |
\ref EXAMPLES_ENET_CPSW_TSN_GPTP_TR |
\ref EXAMPLES_ENET_CPSW_TSN_GPTP_TT |
\ref ENET_CPSW_TSN_GPTP