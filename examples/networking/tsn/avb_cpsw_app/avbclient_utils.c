/*
 *  Copyright (c) Texas Instruments Incorporated 2024
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "avbclient_utils.h"
#include <tsn_uniconf/ucman.h>
#include <tsn_uniconf/uc_dbal.h>
#include <tsn_unibase/unibase_binding.h>
#include <tsn_unibase/unibase.h>

static void show_report_header_footer(avtptc_data_t *avtptcd, bool is_header);

static int print_usage(char *pname, avtptc_data_t *avtptcd)
{
    char *s;
    if((s=strchr(pname,'/'))==NULL){s=pname;}
    UB_CONSOLE_PRINT("%s [options]\n", s);
    UB_CONSOLE_PRINT("-h|--help: this help\n");
    UB_CONSOLE_PRINT("-m|--mode: l(listener)|t(talker): default=talker\n");
    UB_CONSOLE_PRINT("-d|--netdev: network_device: defaut=%s\n", avtptcd->netdev);
    UB_CONSOLE_PRINT("-v|--vid: vlan id: defaut=%d\n", avtptcd->vid);
    UB_CONSOLE_PRINT("-s|--mfsize: max frame size(without L2 header): defaut=%d\n",
             avtptcd->max_frame_size);
    UB_CONSOLE_PRINT("-f|--miframes: max number of frames: defaut=%d\n",
             avtptcd->max_intv_frames);
    UB_CONSOLE_PRINT("-t|--interval: interval time: defaut=%d\n", avtptcd->time_intv);
    UB_CONSOLE_PRINT("-e|--lsempost: listener semaphore post time: defaut=%d\n",
             avtptcd->lsem_post_time);
    UB_CONSOLE_PRINT("-r|--priority: priority: default=%d\n", avtptcd->priority);
    UB_CONSOLE_PRINT("-b|--mbps: bit rate: default(Mbps)=%f\n", avtptcd->mbps);
    UB_CONSOLE_PRINT("-p|--promisc: use promiscuous mode, default=%d\n", avtptcd->promisc);
    UB_CONSOLE_PRINT("-g|--rtag: receive tagged data from socket\n");
    UB_CONSOLE_PRINT("-n|--noavtpd: [BOOL]: optional_argument, '-nfalse' run avtpd "
             "internally, default=%s\n", avtptcd->no_avtpd?"true":"false");
    UB_CONSOLE_PRINT("-q|--quitn: N(number of packets): quit after handling N packets\n");
    UB_CONSOLE_PRINT("-A|--mcast: multicast address: default=%s\n", DEFAULT_MCAST_ADDR);
    UB_CONSOLE_PRINT("-S|--sid: stream id: default=%s\n", DEFAULT_STREAMID);
    UB_CONSOLE_PRINT("-N|--nodc: don't check data contents\n");
    UB_CONSOLE_PRINT("-P|--prts: print timestamps\n");
    UB_CONSOLE_PRINT("-T|--tshape: bytes_per_msec: set software traffic shaper\n");
    UB_CONSOLE_PRINT("-M|--tsminsl: minimum_sleep_time: set minimum sleep time(usec unit)"
             " in the shaper\n");
    UB_CONSOLE_PRINT("-E|--subtype: subtype: set 1722 subtype, default=CVF(3)\n");
    UB_CONSOLE_PRINT("-H|--shsuf: suffix: shared memory suffix\n");
    UB_CONSOLE_PRINT("-G|--gshmem: shared node: gptp shared memory node\n");
    UB_CONSOLE_PRINT("-D|--data: type of test data: v(avbvideo)|f(fixed): default=fixed\n");
    UB_CONSOLE_PRINT("-I|--interval: sending interval(usec): defaut=%d\n",
             avtptcd->send_interval);
    UB_CONSOLE_PRINT("-o|--tsoffset: usec: this time is added on talker pts, default=%dusec\n",
             avtptcd->tsoffset);
    UB_CONSOLE_PRINT("-w|--aheadts: usec: send this time ahead to timestamp in avtpd, "
             "default=%dusec\n", avtptcd->send_ahead_ts);
    UB_CONSOLE_PRINT("           setting -1, no timing control by timestamp in the talker\n");
    UB_CONSOLE_PRINT("-x|--addber: error bit number: add bit error in a second, default=%d\n",
             avtptcd->addber);
    UB_CONSOLE_PRINT("-y|--report-interval: seconds: interval for reporting information (bitrate, latency, ...), default=%d\n",
             avtptcd->report_interval);
    UB_CONSOLE_PRINT("-Z|--wthres-latency: usec: warning threshold for maximum latency, default=%d\n",
             avtptcd->wthres_latency);
    UB_CONSOLE_PRINT("-B|--avtpd-buftime: usec: avtpd buffer time in usec, default=%d\n",
             avtptcd->avtpd_buftime);
    UB_CONSOLE_PRINT("-a|--test-duration: sec: duration time of the testing will be run (unset for running forever) , default=%d\n",
             avtptcd->test_duration);
    UB_CONSOLE_PRINT("-c|--no-healthchk: no health check between avtpd and avtpc\n");
    UB_CONSOLE_PRINT("-C|--avtpc-expandts: the avtpc expands ts32 to ts64\n");
    UB_CONSOLE_PRINT("-F|--filter-dstmac: enable avtpd to filter the destination mac\n");
    return -1;
}

static int set_options(avtptc_data_t *avtptcd, int argc, char *argv[])
{
    int oc;
    int res;
    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"mode", required_argument, 0, 'm'},
        {"netdev", required_argument, 0, 'd'},
        {"vid", required_argument, 0, 'v'},
        {"mfsize", required_argument, 0, 's'},
        {"miframes", required_argument, 0, 'f'},
        {"tintv", required_argument, 0, 't'},
        {"priority", required_argument, 0, 'r'},
        {"mbps", required_argument, 0, 'b'},
        {"promisc", no_argument, 0, 'p'},
        {"rtag", no_argument, 0, 'g'},
        {"noavtpd", optional_argument, 0, 'n'},
        {"mcast", required_argument, 0, 'A'},
        {"sid", required_argument, 0, 'S'},
        {"nodc", no_argument, 0, 'N'},
        {"prts", no_argument, 0, 'P'},
        {"lsempost", required_argument, 0, 'e'},
        {"tshape", required_argument, 0, 'T'},
        {"tsminsl", required_argument, 0, 'M'},
        {"subtype", required_argument, 0, 'E'},
        {"shsuf", required_argument, 0, 'H'},
        {"gshmem", required_argument, 0, 'G'},
        {"data", required_argument, 0, 'D'},
        {"quitn", required_argument, 0, 'q'},
        {"interval", required_argument, 0, 'I'},
        {"tsoffset", required_argument, 0, 'o'},
        {"aheadts", required_argument, 0, 'w'},
        {"addber", required_argument, 0, 'x'},
        {"report-interval", required_argument, 0, 'y'},
        {"wthres-latency", required_argument, 0, 'Z'},
        {"avtpd-buftime", required_argument, 0, 'B'},
        {"test-duration", required_argument, 0, 'a'},
        {"no-healthchk", no_argument, 0, 'c'},
        {"avtpc-expandts", no_argument, 0, 'C'},
        {"filter-dstmac", no_argument, 0, 'F'},
        {"noubinit", no_argument, 0, 'u'},
        {0, 0, 0, 0}
    };

    while((oc=getopt_long(argc, argv,
        "hm:d:v:s:f:t:r:b:pgn::e:q:A:S:NPT:M:E:H:G:D:a:I:o:w:x:y:Z:B:cCFu",
        long_options, NULL))!=-1){
        switch(oc){
        case 'm':
            if(optarg[0]=='l'){avtptcd->mode=LISTENER_MODE;}
            break;
        case 'd':
            avtptcd->netdev=optarg;
            break;
        case 'v':
            avtptcd->vid=strtol(optarg, NULL, 0);
            break;
        case 's':
            avtptcd->max_frame_size=strtol(optarg, NULL, 0);
            break;
        case 'f':
            avtptcd->max_intv_frames=strtol(optarg, NULL, 0);
            break;
        case 't':
            avtptcd->time_intv=strtol(optarg, NULL, 0);
            break;
        case 'p':
            avtptcd->promisc=true;
            break;
        case 'r':
            avtptcd->priority=strtol(optarg, NULL, 0);
            break;
        case 'b':
            avtptcd->mbps=strtof(optarg, NULL);
            break;
        case 'g':
            avtptcd->rec_tagged=true;
            break;
        case 'n':
            if (optarg && !strcmp(optarg, "false")){avtptcd->no_avtpd=false;}
            break;
        case 'e':
            avtptcd->lsem_post_time=strtol(optarg, NULL, 0);
            break;
        case 'q':
            avtptcd->quitn=strtol(optarg, NULL, 0);
            break;
        case 'A':
            avtptcd->mcast=optarg;
            avtptcd->mjoin=optarg;
            break;
        case 'S':
            avtptcd->sid=optarg;
            break;
        case 'N':
            avtptcd->nodc=true;
            break;
        case 'P':
            avtptcd->prts=true;
            break;
        case 'T':
            avtptcd->tshape=strtol(optarg, NULL, 0);
            break;
        case 'M':
            avtptcd->tsminsl=strtol(optarg, NULL, 0);
            break;
        case 'E':
            avtptcd->subtype=strtol(optarg, NULL, 0);
            break;
        case 'H':
            avtptcd->shsuf=optarg;
            break;
        case 'G':
            avtptcd->gshmem=optarg;
            break;
        case 'D':
            if(optarg[0]=='v'){avtptcd->dtype=AVB_TEST_VIDEO;}
            break;
        case 'I':
            avtptcd->send_interval=strtol(optarg, NULL, 0);
            break;
        case 'a':
            avtptcd->test_duration=strtol(optarg, NULL, 0);
            break;
        case 'o':
            avtptcd->tsoffset=strtol(optarg, NULL, 0);
            break;
        case 'w':
            avtptcd->send_ahead_ts=strtol(optarg, NULL, 0);
            if(avtptcd->send_ahead_ts!=-1){avtptcd->send_ahead_ts*=1000;}
            break;
        case 'x':
            avtptcd->addber=strtol(optarg, NULL, 0);
            break;
        case 'y':
            avtptcd->report_interval=strtol(optarg, NULL, 0);
            break;
        case 'Z':
            avtptcd->wthres_latency=strtol(optarg, NULL, 0);
            break;
        case 'B':
            avtptcd->avtpd_buftime=strtol(optarg, NULL, 0);
            break;
        case 'c':
            avtptcd->no_healthcheck=true;
            break;
        case 'C':
            avtptcd->avtpc_expandts32=true;
            break;
        case 'F':
            avtptcd->filter_destmac=true;
            break;
        case 'u':
            //noubinit must be the last one
            break;
        case 'h':
        default:
            return print_usage(argv[0], avtptcd);
        }
    }

    res=optind;
    optind=0;
    return res;
}

int set_ccr(client_connect_request_t *ccr, avtptc_data_t *avtptcd)
{
    ub_streamid_t stream_id;
    char astr[32];
    if(avtptcd->mode==LISTENER_MODE){ccr->con_mode=AVTP_LISTENER_CONNECTION;}
    else{ccr->con_mode=AVTP_TALKER_CONNECTION;}
    strcpy(ccr->netdev, avtptcd->netdev);
    ccr->promisc=avtptcd->promisc;
    if(avtptcd->vid){ccr->tagged=true;}
    ccr->rec_tagged=avtptcd->rec_tagged;
    ccr->max_frame_size=avtptcd->max_frame_size;
    ccr->max_intv_frames=avtptcd->max_intv_frames;
    ccr->time_intv=avtptcd->time_intv;
    ccr->lsem_post_time=avtptcd->lsem_post_time;
    ccr->priority=avtptcd->priority;
    ccr->rank=1;
    ccr->avtpd_bufftime=avtptcd->avtpd_buftime;
    if(!avtptcd->sid){sprintf(astr, "00:01:02:03:04:05:%02X:%02X",
            avtptcd->sidl2>>8, avtptcd->sidl2&0xff);}
    else{strcpy(astr, avtptcd->sid);}
    ub_ssid2bsid(astr, stream_id);
    avbtp_set_stream_id(&ccr->ht.preset_cmsh, stream_id);
    ccr->ht.preset_cmsh.hh.subtype=avtptcd->subtype;
    ccr->ht.preset_cmsh.fsd2=htonl(
        (AVBTP_CVF_FORMAT_RFC<<24)|(AVBTP_CVF_FORMAT_SUBTYPE_MJPEG<<16));
    ccr->ht.preset_cmsh.hh.bf0 |= 0x01;
    set_header_fsd3((&ccr->ht.preset_cmsh), 0x1000);
    ccr->vlanid=avtptcd->vid;
    ub_smac2bmac(avtptcd->mcast, ccr->mcast_addr);
    ub_smac2bmac(avtptcd->mjoin, ccr->join_mcast);
    ccr->send_ahead_ts=1000000; // 1msec
    ccr->no_healthcheck=avtptcd->no_healthcheck;
    ccr->avtpc_expandts32=avtptcd->avtpc_expandts32;
    ccr->filter_destmac=avtptcd->filter_destmac;
    return 0;
}

void avtp_brater_period_print(avtptc_data_t *avtptcd, bool talker, int pkt_size)
{
    if(avtptcd->rate_reporter.total_size == 0){return;}

    if(avtptcd->rate_reporter.end_ts - avtptcd->rate_reporter.last_ts
       >= avtptcd->rate_reporter.period_ns){
        double rate, prate;
        uint64_t latency_avg;

        cb_rate_reporter_calc(&avtptcd->rate_reporter, &rate, &prate, &latency_avg);

        if(talker){
            UB_CONSOLE_PRINT("[TX %s] Rp#%d Mbps(period=%f, total=%f)\n",
                             avtptcd->sid, ++avtptcd->report_counter, prate, rate);
        }else{
            if(avtptcd->report_counter==0){
                UB_CONSOLE_PRINT("[RX] ReportNumber# Mbps(period, total) "
                                 "DelayUsec(min, average, max) "
                                 "Packets(Received, Error, Lost)---------\n");
            }
            UB_CONSOLE_PRINT("[RX %s] Rp#%d Mbps(%f, %f) Delay(%d, %d, %d) "
                             "Pkt(%"PRIu64", %"PRIu64", %"PRIu64")\n",
                             avtptcd->sid,
                             ++avtptcd->report_counter,
                             prate, rate,
                             (int)(avtptcd->rate_reporter.latency_min/1000),
                             (int)(latency_avg/1000),
                             (int)(avtptcd->rate_reporter.latency_max/1000),
                             avtptcd->total_rx_packets,
                             avtptcd->total_err_packets,
                             avtptcd->total_lost_packets);
        }
    }
}

void avtp_show_final_report(avtptc_data_t *avtptcd, bool talker, int pkt_size)
{
    if(avtptcd->rate_reporter.total_size == 0){return;}

    if (avtptcd->rate_reporter.last_ts > avtptcd->rate_reporter.start_ts){
        double rate, prate;
        uint64_t latency_avg;

        cb_rate_reporter_calc(&avtptcd->rate_reporter, &rate, &prate, &latency_avg);

        show_report_header_footer(avtptcd, true);
        if(talker){
            UB_CONSOLE_PRINT("+ talker: total rate %f Mbps\n", rate);
        }else{
            UB_CONSOLE_PRINT("+ listener: total rate %f Mbps\n", rate);
            UB_CONSOLE_PRINT("+ total received packets: %"PRIu64"\n",
                             (uint64_t)(avtptcd->rate_reporter.total_size/pkt_size));
            UB_CONSOLE_PRINT("+ total lost packets: %"PRIu64"\n",
                             avtptcd->total_lost_packets);
            if (avtptcd->dtype==FIXED_DATA){
                UB_CONSOLE_PRINT("+ total error packets: %"PRIu64"\n",
                                 avtptcd->total_err_packets);
            }

            UB_CONSOLE_PRINT("+ ts latency: max=%"PRIu64" nsec, min=%"PRIu64
                             " nsec, average=%"PRIu64" nsec\n",
                             avtptcd->rate_reporter.latency_max,
                             avtptcd->rate_reporter.latency_min,
                             latency_avg);

            UB_CONSOLE_PRINT("+ High latency counter (threshold:%d usec): %"PRIu64"\n",
                            avtptcd->wthres_latency, avtptcd->high_latency_count);
        }
        show_report_header_footer(avtptcd, false);
    }
}

static void show_report_header_footer(avtptc_data_t *avtptcd, bool is_header)
{
    char buf[REPORT_HEADER_LEN+1];
    int ret;

    ret = 0;
    if (is_header) {
        ret = snprintf(buf, sizeof (buf), "----- Report during %d seconds --",
                       avtptcd->test_duration);
    }

    while (ret <= REPORT_HEADER_LEN-1) {
        buf[ret++]='-';
    }
    buf[ret]='\0';

    if (is_header){UB_CONSOLE_PRINT("\n");}
    UB_CONSOLE_PRINT("%s\n", buf);
    if (!is_header){UB_CONSOLE_PRINT("\n");}
}

int GetArgc(char *argv[])
{
    int argc = 0;

    while (argv[argc] != NULL)
    {
        argc++;
    }
    return argc;
}

int avtp_clientinit(avtptc_data_t *avtptcd, int argc, char *argv[])
{
    unibase_init_para_t init_para;
    bool noubinit=false;
    memset(avtptcd, 0, sizeof(avtptc_data_t));
    avtptcd->mode = TALKER_MODE;
    avtptcd->dtype = FIXED_DATA;
    avtptcd->netdev = DEFAULT_NETDEV;
    avtptcd->vid = 110;
    avtptcd->max_frame_size = 1500;
    avtptcd->max_intv_frames = 1;
    avtptcd->time_intv = 250;
    avtptcd->lsem_post_time = DEFAULT_LSEM_POST_TIME;
    avtptcd->priority = 2;
    avtptcd->mbps = 1.0;
    avtptcd->no_avtpd = true;
    avtptcd->mjoin = DEFAULT_JOIN_ADDR;
    avtptcd->mcast = DEFAULT_MCAST_ADDR;
    avtptcd->subtype = AVBTP_SUBTYPE_AAF;
    avtptcd->send_interval = 1000;
    avtptcd->send_ahead_ts = -1;
    avtptcd->test_duration = -1; // Running forever
    avtptcd->sid = DEFAULT_STREAMID;

    // By default, report every 1 seconds
    avtptcd->report_interval = 1;
    // By default, show warning if maximum latency
    // is larger than 20ms.
    avtptcd->wthres_latency = 20000;
    avtptcd->avtpd_buftime = 200000; //200msec should be big enough

    if(argc>0 && (!strcmp(argv[argc-1],"--noubinit") || !strcmp(argv[argc-1], "-u"))){
        noubinit=true;
    }
    if(!noubinit){
        ubb_default_initpara(&init_para);
        init_para.ub_log_initstr=UBL_OVERRIDE_ISTR(
            "4,ubase:45,cbase:45,uconf:46,gptp:46,l2:46", "UBL_L2");
        unibase_init(&init_para);
    }

    if(set_options(avtptcd, argc, argv)<0){return -1;}
    avtptcd->addber=(avtptcd->addber)*(avtptcd->report_interval);
    avtptcd->runber=avtptcd->addber;

    if(strstr(avtptcd->netdev, CB_VIRTUAL_ETHDEV_PREFIX)==avtptcd->netdev){
        // need the IP/UDP header space
        avtptcd->max_frame_size -= CCDBUFF_PAYLOAD_OFFSET + 20;
    }

    WAIT_AVTPD_READY;

    if(gptpmasterclock_init(avtptcd->gshmem)){return -1;}
    if(!noubinit){
        ubb_memory_out_close();
        unibase_close();
    }
    return 0;
}
