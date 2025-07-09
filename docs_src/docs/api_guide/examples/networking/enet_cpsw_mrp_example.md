# Ethernet MRP Example {#EXAMPLES_ENET_CPSW_MRP}

[TOC]

# Introduction

\cond SOC_AM62DX
\note This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
\endcond

This MRP example illustrates the usage of ``IEEE Std 802.1Q-2022 Section 35. Stream Reservation Protocol (SRP)`` stack with CPSW peripheral.

In this example, the DUT MAC port is connected to a neighbor PC which also has gptp, avtp applications and MRP application
Yang based configuration is also supported. Currently File System is not supported, will be added in future releases.

See also :\ref ENET_CPSW_MRP

# Supported Combinations

\cond SOC_AM64X

Not support in this device

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/tsn/mrptalker_app and mrplistener_app

\endcond

\cond SOC_AM263X

Not support in this device

\endcond

\cond SOC_AM273X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/tsn/mrptalker_app and mrplistener_app

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/tsn/mrptalker_app and mrplistener_app

\endcond
## Prerequisites
- EVM Board
- Cat6 ethernet cable
- PC with Linux Ubuntu OS with wireshark, xl4 deb build installed.
- The test setup will be:
  \imageStyle{mrp_test_setup.png,width:80%}
  \image html mrp_test_setup.png MRP test setup

- The test application is running on tilld0, please refer mrp_init.c to change to another network interface.

- To start avbrun with MRP mode support on PC, follow below steps:
\code

# VLAN 110 added
sudo ip link add link enp3s0 name enp3s0.110 type vlan id 110 egress-qos-map 2:2 3:3
sudo ip link set enp3s0.110 up

# Preconfig avbrun to enable running with MRP application
$ mkdir avbrun_demo && cd avbrun_demo
$ avbrun -w rnr-at -d enp3s0  -o setcaps=1
\endcode


## MRP Application state machines
This section describes mvrp/msrp state machines and how the application interact with xmrpd in each state.
For more detail, refer to source/networking/enet/core/examples/tsn/mrptalker_app/avtp_xmrpd.h and avtp_xmrpd.c.
  \imageStyle{MRP_StateMachine.png,width:80%}
  \image html MRP_StateMachine.png Local network between PC and EVM

## CBS setting at intialization
Once the MRP declare Talker Avertise (TA), it will also calculate and reserve bandwidth which suitable with TA's attribute.
But in advance, the application should declare the CBS setting (traffic class, priority and the expected IdleSlope).

\code
EnetApp_TrafficClassCfg_t gTcCfg =
{
    .tcNum = "8",
    // Priority-TC-Map      0         1          2         3         4      5       6       7 <- priority
    // For ex: priority 2 (class B) is mapping with TC 1
    .priorityToTcMap = {    "0",      "3"      , "1",      "2",      "4",   "5",    "6",    "7"}, // <- tc
    .tcToLqMap =     {      "0",      "1",       "2",       "3",     "4",   "5",    "6",    "7"}, // <- Logical queue
    .pQueueNum = "8",
    .pqToLqMap =      {     "0",       "1",       "2",       "3",     "4",    "5",    "6",   "7"}, // <- Logical Queue
    .tcMaxFrameSize = {"1500",  "1500",     "1500",     "1500", "1500", "1500", "1500", "1500"},
    .cbsEnable = "1",
    .tcToAdminIdleSlopeMap = {"1024",    "1024",     "1024",   "1024",    "1024", "1024", "1024", "4096000"} // last item is for ptp
};
// This example, is to send data with priority 2 (class B) -> it should map with TC "1"
// This data should be map to LQ#1 <-> PQ#1
// And the Admin Idle Slope is 1, for initialization, we just need to set to small value.
// While MRP declare TA, it will calculate correct idleSlope needed for TC "1", and register to HW.
\endcode

## MRP Initalization
Refer to below code for how to input MRP parameters.
This example declare mvrp with vlan attribute is 100

\code
#define BASE_VID 100
mrp_data->vid=BASE_VID;
\endcode

And the msrp attributes, are declared below:
- mrsp domain
\code
#define MSRP_SRClassID_A 6
#define MSRP_SRClassID_B 5
#define MSRP_Priority_ClassA 3
#define MSRP_Priority_ClassB 2

mrp_data->domain_info.srclass_id = MSRP_SRClassID_B;
mrp_data->domain_info.srclass_priority = MSRP_Priority_ClassB;
mrp_data->domain_info.srclass_vid = BASE_VID;

\endcode
- mrsp stream (TA):
\code
ub_bytearray8_t base_streamid={0x01, 0x02, 0x03, 0x04, 0x05,0x06, 0x00, 0x00};
ub_bytearray6_t dst_mac={0x91, 0xE0, 0xF0, 0x00, 0xFE,0x00};

memcpy(mrp_data->stream_info.stream_id, base_streamid, sizeof(mrp_data->stream_info.stream_id));
mrp_data->stream_info.stream_id[7] = appno;

memset(mrp_data->sstream_id, 0, sizeof(mrp_data->sstream_id));
bsid2ssid(mrp_data->stream_info.stream_id, mrp_data->sstream_id);

memcpy(mrp_data->stream_info.destmac, dst_mac, sizeof(mrp_data->stream_info.destmac));
mrp_data->stream_info.destmac[5] = appno;
mrp_data->stream_info.vlan_id = BASE_VID;
mrp_data->stream_info.max_frame_size = 1500;
mrp_data->stream_info.max_intv_frames = 1;
mrp_data->stream_info.priority_rank_reserved = to_priority_rank_reserved(MSRP_Priority_ClassB, MSRP_Rank_NonEmergency);
mrp_data->stream_info.accum_latency = 100000;

\endcode

## Build the example

Refer \ref EXAMPLES_ENET_CPSW_TSN_GPTP to build the avtp examples.

## HW Setup

Refer \ref EXAMPLES_ENET_CPSW_TSN_GPTP for HW Setup.

## Create a network between EVM and host PC
EVM and PC has to be connected directly as shown below using CAT6 or CAT5 cable
  \imageStyle{gptp_topology_evm_pc.png,width:30%}
  \image html gptp_topology_evm_pc.png Local network between PC and EVM

PORT1 instead of PORT0 on EVM can be used as well.

## Run the example

\attention If you need to reload and run again, a CPU power-cycle is MUST

Refer :\ref ENET_CPSW_MRP for how to configure MRP parameters.

## MRP verification
### MRP Talker on DUT and PC act as listener
Flash binary in mrptalker_app and start DUT.
Also start PC app as Listener

<b>Verification #1</b> At the beginning, the application will wait for tilld0 link is up and register cbs
\code
mrp_linkcheck: tilld0 up

EnetApp_setMrpExtControlConfig
INF:uconf:cbs_hw_action:cbs setup tilld0, tc=7
INF:uconf:update_cbs_idle_slope:cbs setup tc=7, lqueue=7, pqueue=7
ERR:cbase:LLDEnetSetCreditBasedShaping, set CBS for mac port 0, queue: 7
INF:uconf:cbs_hw_action:update_cbs_idle_slope. res=1
INF:uconf:000003-769447:notice_cb:tilld0, CBS setup completed, tc=7, idleslope=4096000
\endcode

<b>Verification #2</b> After CBS setting finish, the application will wait for gptp is sync-ed on tilld0
\code
mvrp_state_machine: Waiting gPtp sync on tilld0

INF:gptp:waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=1
INF:gptp:set asCapable for domainIndex=0, portIndex=1
INF:gptp:000004-385101:gptpgcfg_set_asCapable:domainInde=0, portIndex=1, ascapable=1
INF:gptp:000004-392575:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:000004-404430:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000004-499390:setSyncTwoStep_txSync:domainIndex=0, portIndex=1, sync gap=4500msec
INF:gptp:000004-505088:setFollowUp_txFollowUp:domainIndex=0, portIndex=1, fup gap=4507msec
mvrp_state_machine: Waiting gPtp sync on tilld0

mvrp_state_machine: Waiting gPtp sync on tilld0

INF:gptp:000005-499668:gm_stable:gm_stable_proc:domainIndex=0
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=2
mvrp_state_machine: GPTP Sync-ed on dev tilld0
\endcode

<b>Verification #3</b> After gptp sync, the MRP state machines will be running, and at the end, the avtp will be started with talker mode
\code
mvrp_state_machine: talker[vid=100]: STARTED -> REGVLAN
mvrp_state_machine: talker[vid=100]: REGVLAN -> RUNNING
mvrp_state_machine: MSRP talker[sid=01-02-03-04-05-06:00-00]: IDLE -> STARTED
msrp_state_machine: talker[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_STARTED -> MSRP_STATE_REGISTERED_DOMAIN
msrp_state_machine: talker[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_REGISTERED_DOMAIN -> MSRP_STATE_WAIT_TARGET
msrp_state_machine: talker[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_WAIT_TARGET -> MSRP_STATE_WAIT_REGIST
msrp_state_machine: talker[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_WAIT_REGIST -> MSRP_STATE_RUNNING
avtp_testclient:talker sid=01:02:03:04:05:06:00:00/vid=100 start
[TX 01:02:03:04:05:06:00:00] Rp#0 Mbps(period=4.991435, total=4.991435)
domain=0, offset=0nsec, hw-adjrate=0ppb
        gmsync=true, last_setts64=0nsec
     10.703s : CPU load =   6.14 %
[TX 01:02:03:04:05:06:00:00] Rp#1 Mbps(period=4.991116, total=4.991275)
[TX 01:02:03:04:05:06:00:00] Rp#2 Mbps(period=5.006592, total=4.996378)
[TX 01:02:03:04:05:06:00:00] Rp#3 Mbps(period=4.994784, total=4.995980)
...
\endcode

<b>Verification #4</b> On PC side also received avtp data and the report is printed
\code
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -20186ppb, GMdiff=-132nsec
listener:TestClientManager:[RX] ReportNumber# Mbps(period, total) DelayUsec(min, average, max) Packets(Received, Error, Lost)---------
[RX 01:02:03:04:05:06:00:00] Rp#0 Mbps(5.006403, 5.006403) Delay(321, 9905, 19773) Pkt(424, 0, 0)
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -17717ppb, GMdiff=4001nsec
listener:TestClientManager:[RX 01:02:03:04:05:06:00:00] Rp#1 Mbps(4.994066, 5.000234) Delay(321, 9892, 19773) Pkt(847, 0, 0)
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -16182ppb, GMdiff=5888nsec
listener:TestClientManager:[RX 01:02:03:04:05:06:00:00] Rp#2 Mbps(5.000488, 5.000320) Delay(321, 9901, 19773) Pkt(1279, 0, 0)
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -15576ppb, GMdiff=5913nsec
listener:TestClientManager:[RX 01:02:03:04:05:06:00:00] Rp#3 Mbps(4.994650, 4.998909) Delay(321, 9912, 19773) Pkt(1702, 0, 0)
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -15321ppb, GMdiff=5346nsec
listener:TestClientManager:[RX 01:02:03:04:05:06:00:00] Rp#4 Mbps(4.994031, 4.997938) Delay(280, 9858, 20855) Pkt(2125, 0, 0)
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -15202ppb, GMdiff=4646nsec
ERR:xmrpd:622475-659475:find_pack_group, data already in the list
listener:TestClientManager:[RX 01:02:03:04:05:06:00:00] Rp#5 Mbps(4.995572, 4.997538) Delay(280, 9902, 20855) Pkt(2557, 0, 0)
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to -15075ppb, GMdiff=4077nsec
domain=0, offset=0nsec, hw-adjrate=-15075ppb
        gmsync=true, last_setts64=0nsec
listener:TestClientManager:[RX 01:02:03:04:05:06:00:00] Rp#6 Mbps(5.000840, 4.998015) Delay(280, 9914, 20855) Pkt(2989, 0, 0)
...
\endcode

### MRP Listener on DUT and PC act as talker
Flash binary in mrplistener_app and start DUT.
Also start PC app as Talker
<b>Verification #1</b> At the beginning, the application will wait for tilld0 link is up and gptp is synced
\code
MAC Port 1: link up
INF:cbase:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!!
INF:gptp:index=1 speed=1000, duplex=full
mrp_linkcheck: tilld0 up
mvrp_state_machine: Waiting gPtp sync on tilld0
mvrp_state_machine: Waiting gPtp sync on tilld0
mvrp_state_machine: Waiting gPtp sync on tilld0
mvrp_state_machine: Waiting gPtp sync on tilld0
mvrp_state_machine: GPTP Sync-ed on dev tilld0
\endcode
<b>Verification #2</b> After gptp sync, the MRP state machines will be running, and at the end, the avtp will be started with listener mode
\code
mrpmanager_declare_vid: Found vid = 100 in OperListReq
mvrp_state_machine: listener[vid=100]: STARTED -> REGVLAN
mvrp_state_machine: listener[vid=100]: REGVLAN -> RUNNING
msrp_state_machine: listener[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_STARTED -> MSRP_STATE_REGISTERED_DOMAIN
msrp_state_machine: listener[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_REGISTERED_DOMAIN -> MSRP_STATE_WAIT_TARGET
msrp_state_machine: listener[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_WAIT_TARGET -> MSRP_STATE_WAIT_REGIST
msrp_state_machine: listener[sid=01-02-03-04-05-06:00-00]: MSRP_STATE_WAIT_REGIST -> MSRP_STATE_RUNNING
avtp_testclient:listener sid=01:02:03:04:05:06:00:00/vid=100 start
INF:xmrpd:Waiting for avtpd to be ready...
INF:xmrpd:waiting avtpd
INF:xmrpd:avtpd is ready
INF:gptp:gptpmasterclock_init: tsn_gptp-1.2.3, ref_counter=2
mode=1, hit return to quit
INF:xmrpd:start_listener:
INF:avtp:avtpc_init: l2-1.2.3
INF:avtp:create_connection: ci=0 frame size=1518 bufnum=4 ccdsize=6624
INF:avtp:create_connection:stream_id=01:02:03:04:05:06:00:00, subtype=3
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=4 numRxChannels=1 dmaRxChId=4 nTxPkts=8 nRxPkts=8 pktSize=1536
INF:cbase:rxChId 4 has owner dmaRxShared 0
CPSW_ALE_IOCTL_ADD_VLAN: 100
CPSW_ALE_IOCTL_ADD_VLAN: 100
INF:avtp:avtp_ethernet_open:go ahead without the pipe, it may make problems for closing
INF:avtp:ll_avtpe_receive_data: enable Rx Zero-Copy
INF:cbase:cb_lld_task_create: avtp_tilld0_91:E0:F0:00:FE:00 stack_size=8192
INF:cbase:cb_lld_task_create: avtpc_01:02:03:04:05:06:00:00 stack_size=8192
INF:xmrpd:start_listener:start
[RX] ReportNumber# Mbps(period, total) DelayUsec(min, average, max) Packets(Received, Error, Lost)---------
[RX 01:02:03:04:05:06:00:00] Rp#0 Mbps(1.007453, 1.007453) Delay(167, 12253, 25008) Pkt(88, 0, 0)
[RX 01:02:03:04:05:06:00:00] Rp#1 Mbps(0.996827, 1.002204) Delay(167, 11997, 25008) Pkt(173, 0, 0)
[RX 01:02:03:04:05:06:00:00] Rp#2 Mbps(0.995695, 1.000016) Delay(167, 12155, 25008) Pkt(260, 0, 0)
     15.704s : CPU load =   5.70 %
[RX 01:02:03:04:05:06:00:00] Rp#3 Mbps(0.996924, 0.999239) Delay(167, 12077, 25008) Pkt(347, 0, 0)
[RX 01:02:03:04:05:06:00:00] Rp#4 Mbps(0.995671, 0.998522) Delay(167, 11967, 25008) Pkt(434, 0, 0)
...
\endcode
# See Also
\ref NETWORKING |
\ref ENET_CPSW_AVTP
\ref ENET_CPSW_MRP