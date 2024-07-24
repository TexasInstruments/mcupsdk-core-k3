/*
 * acf_testappli.c
 * test program to use l2 layer and acf
 *
 * Copyright (C) 2018 Excelfore Corporation
 * Author: Shiro Ninomiya (shiro@excelfore.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <getopt.h>
#include "avtpc.h"
#include <stdio.h>
#include "avtpc_acf.h"
#include "tsn_gptp/gptpmasterclock.h"
#include <tsn_unibase/unibase_binding.h>
#ifdef AVTP_PLATFORM_INCLUDE
#include AVTP_PLATFORM_INCLUDE
#endif
#ifndef WAIT_AVTPD_READY
#define WAIT_AVTPD_READY
#endif

#define DEFAULT_MCAST_ADDR "91:E0:F0:00:FE:00"

static int stop_mainloop;

extern char *avtpc_acf_msgtype_str(avtpc_acf_message_type_t mt);

typedef struct acftc_data {
	avtpc_acf_data_t *avtpc_acf;
	char mode;
	char *netdev;
	uint16_t vid;
	char *mcast;
	char *sid;
	int duration_ms;
	int interval_ms;
	bool reconly;
	bool latency;
	int ahead_ts;
	uint8_t vlan_pcp;
	int align_unit;
	int align_tail;
	int burst_pn;
	char *shsuf;
	char *gshmem;
	uint32_t tshape_rate; //!< software traffic shaper, bytes per msec, 0 to disable
	int tshape_minsleep; //!< minimum sleep time for the traffic shaper, nsec unit
	bool txdirect;
	bool rxdirect;
	uint16_t tsport; //UDP test source port in direct mode
	uint16_t tdport; //UDP test dest port in direct mode
} acftc_data_t;

typedef struct user0_data {
	uint16_t magic16;
	uint64_t ts;
} __attribute__((packed)) user0_data_t;

/***** test data definitions *****/
static uint8_t payloaddu[10]={0,0,0,1,2,3,4,5,6,7};
static uint8_t *payloadd=payloaddu+2;
static int payloadd_size=sizeof(payloaddu)-2;

static avtpc_acf_msg_flexray_t flexrayd = {
	.mtv=1,
	.busid=0x1a,
	.chan=2,
	.str=0,
	.syn=1,
	.pre=0,
	.nfi=1,
	.msg_ts={0x55,0xaa,0x5a,0xa5,0x33,0x99,0x39,0x93},
	.frid=0x3aa,
	.cycle=0x2a,
};

static avtpc_acf_msg_can_t cand = {
	.mtv=0,
	.rtr=1,
	.eff=0,
	.brs=1,
	.fdf=0,
	.esi=1,
	.busid=0x15,
	.msg_ts={0x33,0x99,0x39,0x93,0x55,0xaa,0x5a,0xa5},
	.canid=0x15,
};

static avtpc_acf_msg_abcan_t abcand = {
	.mtv=1,
	.rtr=0,
	.eff=1,
	.brs=0,
	.fdf=1,
	.esi=0,
	.busid=0x0a,
	.canid=0x0a,
};

static avtpc_acf_msg_lin_t lind = {
	.mtv=1,
	.busid=0x13,
	.linid=0xa5,
	.msg_ts={0x33,0x99,0x55,0xaa,0x39,0x93,0x5a,0xa5},
};

static avtpc_acf_msg_most_t mostd = {
	.mtv=0,
	.mostid=0x09,
	.msg_ts={0x5a,0xa5,0x55,0xaa,0x39,0x93,0x33,0x99},
	.devid=0xa005,
	.fbid=0xa5,
	.instid=0x5a,
	.funcid=0xc33,
	.optype=0x0e,
};

static avtpc_acf_msg_gpc_t gpcd = {
	.msg_id={0x5a,0xaa,0x39,0x93,0x33,0x99},
};

static avtpc_acf_msg_serial_t seriald = {
	.dcd=0,
	.dtr=1,
	.dsr=0,
	.rts=1,
	.cts=0,
	.ri=1,
};

static avtpc_acf_msg_parallel_t paralleld = {
	.bwidth=0xa5,
};

static avtpc_acf_msg_sensor_t sensord = {
	.mtv=1,
	.nums=0x75,
	.sz=0x3,
	.sgroup=0x3c,
	.msg_ts={0x99,0x5a,0xa5,0x55,0xaa,0x39,0x93,0x33},
};

static avtpc_acf_msg_absensor_t absensord = {
	.nums=0x63,
	.sz=0x2,
	.sgroup=0x23,
};

#if 0
static avtpc_acf_msg_aecp_t aecpd = {
};
#endif

static avtpc_acf_msg_ancillary_t ancillaryd = {
	.mode=0x3,
	.fp=1,
	.lp=0,
	.lnum=0xaa55,
	.did=0x55,
	.sdid=0xaa,
};

static const uint16_t testdata_magic16=0xabcd;

/***** end of test data definitions *****/

static int print_usage(char *pname, acftc_data_t *acftcd)
{
	char *s;
	if((s=strchr(pname,'/'))==NULL){s=pname;}
	UB_CONSOLE_PRINT("%s [options]\n", s);
	UB_CONSOLE_PRINT("-h|--help: this help\n");
	UB_CONSOLE_PRINT("-m|--mode: t(tscf)|n(ntscf)|a(aligned tscf): default=%c\n", acftcd->mode);
	UB_CONSOLE_PRINT("-d|--netdev: network_device: defaut=%s\n", acftcd->netdev);
	UB_CONSOLE_PRINT("-v|--vid: vlan id: defaut=%d\n", acftcd->vid);
	UB_CONSOLE_PRINT("##### don't forget configure VLAN to receive data #####\n");
	UB_CONSOLE_PRINT("-i|--interval: interval(ms): defaut=%d\n", acftcd->interval_ms);
	UB_CONSOLE_PRINT("-p|--duration: duration(ms): defaut=%d, 0 for infinite\n",
		      acftcd->duration_ms);
	UB_CONSOLE_PRINT("-r|--reconly: don't send data, defaut=%d\n", acftcd->reconly);
	UB_CONSOLE_PRINT("-l|--latency: measure latency\n");
	UB_CONSOLE_PRINT("-s|--sid: stream id: default=%s\n", acftcd->sid);
	UB_CONSOLE_PRINT("-A|--mcast: multicast address: default=%s\n", DEFAULT_MCAST_ADDR);
	UB_CONSOLE_PRINT("-a|--ahead-ts: send this time ahead to the scheduled time"
		      "(nsec unit): default=%d\n", acftcd->ahead_ts);
	UB_CONSOLE_PRINT("-P|--pcp: pcp value in vlan tag: default=%d\n", acftcd->vlan_pcp);
	UB_CONSOLE_PRINT("-u|--au: align unit(ms): default=%d\n", acftcd->align_unit/1000000);
	UB_CONSOLE_PRINT("-t|--at: align tail(us): default=%d\n", acftcd->align_tail/1000);
	UB_CONSOLE_PRINT("-b|--burst: burst of packets: default=%d\n", acftcd->burst_pn);
	UB_CONSOLE_PRINT("-S|--shsuf: suffix: shared memory suffix\n");
	UB_CONSOLE_PRINT("-g|--gshmem: node : gptp shared memory node\n");
	UB_CONSOLE_PRINT("-T|--tshape: bytes per msec for traffic shaper, 0: disable\n");
	UB_CONSOLE_PRINT("-M|--minsl: minimum sleep for traffic shaper, 0: disable\n");
	UB_CONSOLE_PRINT("-I|--txdirect: enable avtpc_acf tx direct mode\n");
	UB_CONSOLE_PRINT("-R|--rxdirect: enable avtpc_acf rx direct mode\n");
	UB_CONSOLE_PRINT("-k|--tsport: src_port: UDP test source port in direct mode\n");
	UB_CONSOLE_PRINT("-K|--tdport: dst_port: UDP test dest port in direct mode\n");
	return -1;
}

static int set_options(acftc_data_t *acftcd, int argc, char *argv[])
{
	int oc;
	struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"mode", required_argument, 0, 'm'},
		{"netdev", required_argument, 0, 'd'},
		{"vid", required_argument, 0, 'v'},
		{"reconly", no_argument, 0, 'r'},
		{"mcast", required_argument, 0, 'A'},
		{"sid", required_argument, 0, 's'},
		{"interval", required_argument, 0, 'i'},
		{"duration", required_argument, 0, 'p'},
		{"latency", no_argument, 0, 'l'},
		{"ahead-ts", required_argument, 0, 'a'},
		{"pcp", required_argument, 0, 'P'},
		{"au", required_argument, 0, 'u'},
		{"at", required_argument, 0, 't'},
		{"burst", required_argument, 0, 'b'},
		{"shsuf", required_argument, 0, 'S'},
		{"gshmem", required_argument, 0, 'g'},
		{"tshape", required_argument, 0, 'T'},
		{"minsl", required_argument, 0, 'M'},
		{"txdirect", no_argument, 0, 'I'},
		{"rxdirect", no_argument, 0, 'R'},
		{"tsport", required_argument, 0, 'k'},
		{"tdport", required_argument, 0, 'K'},
		{"noubinit", no_argument, 0, 'n'},
		{0, 0, 0, 0}
	};

	while((oc=getopt_long(argc, argv, "hm:d:v:rA:s:i:p:la:P:u:t:b:S:g:T:M:IRk:K:n",
						  long_options, NULL))!=-1){
		switch(oc){
		case 'm':
			acftcd->mode=optarg[0];
			if(acftcd->mode!='t' && acftcd->mode!='n' && acftcd->mode!='a'){return -1;}
			break;
		case 'd':
			acftcd->netdev=optarg;
			break;
		case 'v':
			acftcd->vid=strtol(optarg, NULL, 0);
			break;
		case 'r':
			acftcd->reconly=true;
			break;
		case 'i':
			acftcd->interval_ms=strtol(optarg, NULL, 0);
			break;
		case 'p':
			acftcd->duration_ms=strtol(optarg, NULL, 0);
			break;
		case 'l':
			acftcd->latency=true;
			break;
		case 'a':
			acftcd->ahead_ts=strtol(optarg, NULL, 0);
			break;
		case 'b':
			acftcd->burst_pn=strtol(optarg, NULL, 0);
			break;
		case 'A':
			acftcd->mcast=optarg;
			break;
		case 's':
			acftcd->sid=optarg;
			break;
		case 'P':
			acftcd->vlan_pcp=strtol(optarg, NULL, 0);
			break;
		case 'u':
			acftcd->align_unit=strtol(optarg, NULL, 0)*1000000;
			break;
		case 't':
			acftcd->align_tail=strtol(optarg, NULL, 0)*1000;
			break;
		case 'S':
			acftcd->shsuf=optarg;
			break;
		case 'g':
			acftcd->gshmem=optarg;
			break;
		case 'T':
			acftcd->tshape_rate = strtol(optarg, NULL, 0);
			break;
		case 'M':
			acftcd->tshape_minsleep =strtol(optarg, NULL, 0)*1000;
			break;
		case 'I':
			acftcd->txdirect=true;
			break;
		case 'R':
			acftcd->rxdirect=true;
			break;
		case 'k':
			acftcd->tsport = strtol(optarg, NULL, 0);
			break;
		case 'K':
			acftcd->tdport = strtol(optarg, NULL, 0);
			break;
		case 'n':
			//noubinit must be the last one
			break;
		case 'h':
		default:
			print_usage(argv[0], acftcd);
			return -1;
		}
	}
	return 0;
}

static int receive_acf(avtpc_acf_msg_field_t *msgf, ub_streamid_t stream_id,
		       uint64_t *ts, void *cbdata)
{
	int res=0;
	acftc_data_t *acftcd=(acftc_data_t *)cbdata;
	user0_data_t *ud0;
	int cmpoffset=0;

	UB_LOG(UBL_INFO, "%s:%s\n",__func__,
		   avtpc_acf_msgtype_str((avtpc_acf_message_type_t)msgf->msg_type));

	switch(msgf->msg_type){
	case AVTPC_ACF_FLEXRAY:
		res=memcmp((&msgf->u.flexray), &flexrayd, sizeof(avtpc_acf_msg_flexray_t));
		break;
	case AVTPC_ACF_CAN:
		res=memcmp((&msgf->u.can), &cand, sizeof(avtpc_acf_msg_can_t));
		break;
	case AVTPC_ACF_ABCAN:
		res=memcmp((&msgf->u.abcan), &abcand, sizeof(avtpc_acf_msg_abcan_t));
		break;
	case AVTPC_ACF_LIN:
		res=memcmp((&msgf->u.lin), &lind, sizeof(avtpc_acf_msg_lin_t));
		break;
	case AVTPC_ACF_MOST:
		res=memcmp((&msgf->u.most), &mostd, sizeof(avtpc_acf_msg_most_t));
		break;
	case AVTPC_ACF_GPC:
		res=memcmp((&msgf->u.gpc), &gpcd, sizeof(avtpc_acf_msg_gpc_t));
		break;
	case AVTPC_ACF_SERIAL:
		res=memcmp((&msgf->u.serial), &seriald, sizeof(avtpc_acf_msg_serial_t));
		break;
	case AVTPC_ACF_PARALLEL:
		res=memcmp((&msgf->u.parallel), &paralleld, sizeof(avtpc_acf_msg_parallel_t));
		break;
	case AVTPC_ACF_SENSOR:
		res=memcmp((&msgf->u.sensor), &sensord, sizeof(avtpc_acf_msg_sensor_t));
		break;
	case AVTPC_ACF_ABSENSOR:
		res=memcmp((&msgf->u.absensor), &absensord, sizeof(avtpc_acf_msg_absensor_t));
		break;
	case AVTPC_ACF_AECP:
		//res=memcmp((&msgf->u.aecp), &aecpd, sizeof(avtpc_acf_msg_aecp_t));
		break;
	case AVTPC_ACF_ANCILLARY:
		res=memcmp((&msgf->u.ancillary), &ancillaryd, sizeof(avtpc_acf_msg_ancillary_t));
		break;
	case AVTPC_ACF_USER0:
		ud0=(user0_data_t *)msgf->payload;
		if(acftcd->latency){
			uint64_t ts64, lts64;
			ts64=ud0->ts;
			ts64=UB_NTOHLL(ts64);
			lts64=gptpmasterclock_getts64();
			UB_CONSOLE_PRINT("ts=%"PRIu64" msec, latency=%"PRIi64" usec\n",
				      (ts64%1000000000)/1000000, (lts64-ts64)/1000);
			return 0;
		}else{
			if(ntohs(ud0->magic16)!=testdata_magic16){
				UB_LOG(UBL_INFO, "wrong magic16=0x%04x\n",
				       ntohs(ud0->magic16));
				return -1;
			}
			// the first 2 bytes is 'magic16'
			cmpoffset=2;
		}
		break;
	default:
		UB_LOG(UBL_INFO, "unknown msg_type=%d\n", msgf->msg_type);
		return -1;
	}
	if(res){
		UB_LOG(UBL_INFO, "field header doens't match\n");
		avtpc_acf_print_msg_field(msgf);
	}
	if(memcmp(msgf->payload+cmpoffset, payloadd, payloadd_size)){
		UB_LOG(UBL_INFO, "payload data doens't match\n");
		res=-1;
	}
	if(msgf->pl_length!=payloadd_size+cmpoffset){
		UB_LOG(UBL_INFO, "payload size doesn't match\n");
		res=-1;
	}
	ub_log_flush();
	return res;
}

static int send_one_packet(acftc_data_t *acftcd)
{
	avtpc_acf_msg_field_t acfmfs[13];
	avtpc_acf_msg_field_t *msgfls[14];
	int i;
	for(i=0;i<12;i++) acfmfs[i].msg_type=i;
	acfmfs[12].msg_type=AVTPC_ACF_USER0;
	for(i=0;i<12;i++) {
		acfmfs[i].payload=payloadd;
		acfmfs[i].pl_length=payloadd_size;
	}
	acfmfs[12].payload=payloaddu;
	acfmfs[12].pl_length=sizeof(payloaddu);

	memcpy(&acfmfs[0].u.flexray,&flexrayd,sizeof(flexrayd));
	memcpy(&acfmfs[1].u.can,&cand,sizeof(cand));
	memcpy(&acfmfs[2].u.abcan,&abcand,sizeof(abcand));
	memcpy(&acfmfs[3].u.lin,&lind,sizeof(lind));
	memcpy(&acfmfs[4].u.most,&mostd,sizeof(mostd));
	memcpy(&acfmfs[5].u.gpc,&gpcd,sizeof(gpcd));
	memcpy(&acfmfs[6].u.serial,&seriald,sizeof(seriald));
	memcpy(&acfmfs[7].u.parallel,&paralleld,sizeof(paralleld));
	memcpy(&acfmfs[8].u.sensor,&sensord,sizeof(sensord));
	memcpy(&acfmfs[9].u.absensor,&absensord,sizeof(absensord));
	//memcpy(&acfmfs[10].u.aecp,&aecpd,sizeof(aecpd));
	memcpy(&acfmfs[11].u.ancillary,&ancillaryd,sizeof(ancillaryd));
	*((uint16_t*)acfmfs[12].payload)=htons(testdata_magic16);
	for(i=0;i<13;i++) msgfls[i]=&acfmfs[i];
	msgfls[13]=NULL;

	avtpc_acf_write_packet_mf(acftcd->avtpc_acf, msgfls, gptpmasterclock_getts64());
	return 0;
}

static int send_one_tspacket(acftc_data_t *acftcd)
{
	avtpc_acf_msg_field_t acfmf;
	avtpc_acf_msg_field_t *msgfls[2];
	uint64_t ts64;
	user0_data_t ud0;
	msgfls[0]=&acfmf;
	msgfls[1]=NULL;
	acfmf.msg_type=AVTPC_ACF_USER0;
	ud0.magic16=htons(testdata_magic16);
	acfmf.payload=&ud0;
	acfmf.pl_length=sizeof(ud0);
	ts64=gptpmasterclock_getts64();
	if(acftcd->mode=='a'){
		ts64=(ts64/acftcd->align_unit)*acftcd->align_unit +
			acftcd->align_unit + acftcd->align_tail;
	}
	ud0.ts=UB_HTONLL(ts64);
	avtpc_acf_write_packet_mf(acftcd->avtpc_acf, msgfls, ts64);
	return 0;
}

static int start_acf(acftc_data_t *acftcd)
{
	client_connect_request_t ccr;
	ub_streamid_t stream_id;
	int64_t ts0,ts1;
	int32_t dtms=0;
	int i;

	acftcd->avtpc_acf=avtpc_acf_init(acftcd->mode=='n'?AVBTP_SUBTYPE_NTSCF:AVBTP_SUBTYPE_TSCF,
					 receive_acf, acftcd, acftcd->shsuf);
	if (!acftcd->avtpc_acf){return -1;}
	avtpc_acf_set_ccr(acftcd->avtpc_acf, &ccr, acftcd->netdev, acftcd->vid);
	ccr.send_ahead_ts=acftcd->ahead_ts;
	ccr.priority=acftcd->vlan_pcp;

	ub_ssid2bsid(acftcd->sid, stream_id);
	avbtp_set_stream_id(&ccr.ht.preset_cmsh, stream_id);
	if(acftcd->mode!='n'){ccr.ht.preset_cmsh.bf=cmsh_tv_set_bit_field(ccr.ht.preset_cmsh.bf,1);}
	ub_smac2bmac(acftcd->mcast, ccr.mcast_addr);
	ub_smac2bmac(acftcd->mcast, ccr.join_mcast);
	ccr.tshape_rate=acftcd->tshape_rate;
	ccr.tshape_minsleep=acftcd->tshape_minsleep;
	if(acftcd->txdirect || acftcd->rxdirect){
		if(acftcd->txdirect){avtpc_acf_set_txdirect(acftcd->avtpc_acf);}
		if(acftcd->rxdirect){avtpc_acf_set_rxdirect(acftcd->avtpc_acf);}
		if(acftcd->tsport||acftcd->tdport){
			avtpc_acf_set_testport(acftcd->avtpc_acf, acftcd->tsport, acftcd->tdport);
		}
	}
	if(avtpc_acf_connection_request(acftcd->avtpc_acf, &ccr)){return -1;}
	ts0=ub_rt_gettime64();
	while(!stop_mainloop && (acftcd->duration_ms==0 || dtms<acftcd->duration_ms)){
		if(!acftcd->reconly) {
			for(i=0;i<acftcd->burst_pn;i++){
				if(acftcd->latency){
					send_one_tspacket(acftcd);
				}else{
					send_one_packet(acftcd);
				}
			}
		}
		CB_USLEEP(acftcd->interval_ms*1000);
		ts1=ub_rt_gettime64();
		ts1=ts1-ts0;
		dtms=ts1/UB_MSEC_NS;
	}
	avtpc_acf_close(acftcd->avtpc_acf);
	return 0;
}

#ifndef ACF_HAVE_NO_SIGNAL
#include <signal.h>
static void signal_handler(int sig)
{
	UB_LOG(UBL_INFO,"acf_testclient:%s:sig=%d\n",__func__,sig);
	stop_mainloop=1;
}

static void register_signal(void)
{
	struct sigaction sigact;
	memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler=signal_handler;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);
}
#define ACF_REGISTER_SIGNAL register_signal()
#else //!ACF_HAVE_NO_SIGNAL
#define ACF_REGISTER_SIGNAL
#endif //!ACF_HAVE_NO_SIGNAL

#ifdef ACF_TESTCLIENT_MAIN
int stop_acfclient()
{
	stop_mainloop=1;
	return 0;
}
#else //!ACF_TESTCLIENT_MAIN
#define ACF_TESTCLIENT_MAIN main
#endif //!ACF_TESTCLIENT_MAIN

int ACF_TESTCLIENT_MAIN(int argc, char *argv[])
{
	bool noubinit = false;
	bool is_direct = false;
	static acftc_data_t acftcd = {
		.avtpc_acf = NULL,
		.mode = 't',
		.netdev = DEFAULT_NETDEV,
		.vid = 110,
		.mcast = DEFAULT_MCAST_ADDR,
		.sid = "00:01:02:03:04:05:00:00",
		.interval_ms = 1000,
		.duration_ms = 0,
		.reconly = false,
		.ahead_ts = 0,
		.vlan_pcp = IEEE1722_DEFAULT_PCP,
		.align_unit = 100000000, // default 100msec
		.align_tail = 0,
		.burst_pn = 1,
		.shsuf = NULL,
		.gshmem = NULL,
	};
	if(argc>0 && (!strcmp(argv[argc-1],"--noubinit") || !strcmp(argv[argc-1],"-n"))){
		noubinit=true;
		UB_CONSOLE_PRINT("arf_testclient: noubinit=true\r\n");
	}
	if(!noubinit){
		unibase_init_para_t init_para;
		ubb_default_initpara(&init_para);
		init_para.ub_log_initstr=UBL_OVERRIDE_ISTR(
			"4,ubase:45,cbase:45,uconf:46,gptp:46,l2:46", "UBL_L2");
		unibase_init(&init_para);
	}
	if(set_options(&acftcd, argc, argv)){return -1;}

	ACF_REGISTER_SIGNAL;

	is_direct = (acftcd.txdirect || acftcd.rxdirect);
	if(!is_direct){
		UB_LOG(UBL_INFO,"Waiting for avtpd to be ready...\n");
		WAIT_AVTPD_READY;
	}
	while(!stop_mainloop && gptpmasterclock_init(acftcd.gshmem)){
		UB_LOG(UBL_INFO,"Waiting for tsn_gptpd to be ready...\n");
		CB_USLEEP(100000);
	}

	if(gptpmasterclock_init(acftcd.gshmem)){return(-1);}
	start_acf(&acftcd);
	gptpmasterclock_close();
	ubb_memory_out_close();
	unibase_close();
	return 0;
}
