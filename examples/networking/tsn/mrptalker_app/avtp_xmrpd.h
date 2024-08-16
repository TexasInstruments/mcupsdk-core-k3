/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
#ifndef __AVTP_TC_XMRPD_H_
#define __AVTP_TC_XMRPD_H_

#include <stdbool.h>
#include <stdint.h>
#include "mrp_datatypes.h"
#include <xmrpd/xmrpdconf/mrpgcfg.h>
#include <tsn_uniconf/yangs/yang_db_runtime.h>
#include <xmrpd/mrpman.h>
#include <xmrpd/mrp_map.h>
#include <xmrpd/mrp_extcontrol.h>
#include "avtp_xmrpd.h"

#define DEFAULT_MCAST_ADDR "91:E0:F0:00:FE:00"
#define DEFAULT_JOIN_ADDR "91:E0:F0:00:FE:00"

typedef enum {
	TALKER_MODE=0,
	LISTENER_MODE,
} mode_type;

typedef enum {
	EXTCTRL_OPERATION_REQ_LIST, // RO
	EXTCTRL_ADMIN_REQ_LIST, // RW
	EXTCTRL_INDICATION_LIST // RO
} mrp_extctrl_list_type;

typedef enum {
	MVRP_STATE_IDLE=1, // Started + network down
	MVRP_STATE_WAIT_GPTP_SYNC, // Network up
	MVRP_STATE_STARTED, // gPTP sync-ed
	MVRP_STATE_REGVLAN,
	MVRP_STATE_RUNNING,
	MVRP_STATE_CLOSING,
	MVRP_STATE_CLOSED
}mvrp_state_t;

typedef enum {
	MSRP_STATE_IDLE=1,    // Started + network down
	MSRP_STATE_STARTED,   // MVRP STARTED
	MSRP_STATE_REGISTERED_DOMAIN,
	MSRP_STATE_WAIT_TARGET,
	MSRP_STATE_WAIT_REGIST,
	MSRP_STATE_RUNNING,
	MSRP_STATE_CLOSING,
	MSRP_STATE_CLOSED
}msrp_state_t;

typedef struct mvrp_data {
	mvrp_state_t mrp_state;
}mvrp_data_t;

#define NUM_MSRP_ATTR_TYPES 4
#define DISAPPEAR_TIMEOUT 1E9
typedef struct msrp_data {
	msrp_state_t mrp_state;
	uint64_t lt_timeout;
}msrp_data_t;

#define MAX_AVB_APP	(7)
typedef struct mrp_data {
	mrp_extc_dlist_t addrdl;

	// Inputs
	mode_type mode;
	uint16_t vid;
	double mbps;
	bool rec_tagged;
	msrp_domain_data_t domain_info;
	msrp_stream_data_t stream_info;
	char sstream_id[24]; // for debugging
	bool stream_available;
	CB_THREAD_T avtp_tc_thread;
	bool app_running;
	char *netdev;

	// keep state machines
	mvrp_data_t mvrp_data;
	msrp_data_t msrp_data;
}mrp_data_t;

typedef struct xmrpd_at_data {
	char *dbname;
	uc_dbald *dbald;
	uc_notice_data_t* ucntd;
	yang_db_runtime_dataq_t *ydrd;
	char *netdev;
	mrpgcfgd_t *mrpgcfg; 

	// keep input + statemachines for mrp app
	uint8_t avb_app_num;
	mrp_data_t mrp_data[MAX_AVB_APP];

	// Use for check network link status
	UC_NOTICE_SIG_T *linksem;
	char semname[12+16+1]; // strlen(XMRP_LINKSEMNAME)+64bitTS+NULL
} xmrpd_app_data_t;  //xmrpd avtp_testclient data

int stop_testclient(void); // Implemented in avtp_testclient
int run_xmrpd_app(xmrpd_app_data_t *xmrpd_app_info);
int avtp_xmrpd_start(int argc,char *argv[]);
char *bsid2ssid(ub_streamid_t bsid, char *ssid);

#endif //__AVTP_TC_XMRPD_H_
