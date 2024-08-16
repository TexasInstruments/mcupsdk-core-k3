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

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <tsn_unibase/unibase.h>
#include "tsn_l2/avtpc.h"
#include "avtp_xmrpd.h"
#include <xmrpd/xmrpdconf/mrpgcfg.h>
#include <xmrpd/mrp_extcontrol.h>
#include "debug_log.h"
#include "tsninit.h"
#include <tsn_uniconf/yangs/ietf-interfaces_access.h>

#define MRPIPC_READ_TIMEOUT 200
#define PRINT_EVERY_N_PACKET 20

extern int avtp_testclient(int argc, char *argv[]);
extern void EnetApp_registerIdleSlope(uc_dbald *dbald, yang_db_runtime_dataq_t *ydrd, uc_notice_data_t* ucntd, const char* ndev);
extern int EnetApp_setMrpExtControlConfig(yang_db_runtime_dataq_t *ydrd, uc_notice_data_t* ucntd, char* dev);
extern bool EnetApp_isGptpSync(yang_db_runtime_dataq_t *ydrd);
static int proto_to_attr(int tpe )
{
	if( (tpe < 7) || (tpe > 12) ) return -1;
	return (tpe-7);
}
static int check_msrp_attr_list_exist(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno, msrp_attributetype_t attr_type, mrp_extctrl_list_type lsttype);

#define MAX_RETRY_COUNTER 5
static int check_msrp_oper_req_list_exist(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno, msrp_attributetype_t attr_type)
{
	int ret;
	uint8_t retry_counter=0;
	while (true)
	{
		ret = check_msrp_attr_list_exist(xmrpd_app_info, appno, attr_type, EXTCTRL_OPERATION_REQ_LIST);
		if (ret == -1)
		{
			CB_USLEEP(10000);
			retry_counter++;
			if ( retry_counter == MAX_RETRY_COUNTER) 
			{
				DPRINT("%s: exceed_retry counter. break! \n", __func__);
				break;
			}
		}
		else
		{
			break;
		}
	}

	return ret;
}

static char* get_attribute_list_prefix(msrp_attributetype_t attr_type)
{
	switch(attr_type)
	{
		case MSRP_Domain: return "D";
		case MSRP_TalkerAdvertise: return "TA";
		case MSRP_Listener: return "L";
		default: return "TF";
	}
}

/// @brief Read ext-control oper or indication list and compare to our setting
/// @param xmrpd_app_info 
/// @param attr_type 
/// @param lsttype 
/// @return 
static int check_msrp_attr_list_exist(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno, msrp_attributetype_t attr_type, mrp_extctrl_list_type lsttype)
{
	int res;
	char cmd_buf[128];
	mrp_extc_dlist_t addrdl;

	mrp_extc_dlist_init(&addrdl);

	switch(lsttype)
	{
		case EXTCTRL_OPERATION_REQ_LIST:
			snprintf(cmd_buf, sizeof(cmd_buf), "R %s,msrp O %s", xmrpd_app_info->netdev, get_attribute_list_prefix(attr_type));
			break;
		case EXTCTRL_INDICATION_LIST:
			snprintf(cmd_buf, sizeof(cmd_buf), "R %s,msrp I %s", xmrpd_app_info->netdev, get_attribute_list_prefix(attr_type));
			break;
		default:
			mrp_extc_dlist_close(&addrdl);
			return -1; // not supported
		break;
	}

	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &addrdl);
	if (res != 0)
	{
		DPRINT("%s: No entry in %s List: '%s', res=%d ", __func__, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication", cmd_buf, res);
		res = -1;
	}
	else
	{
		int en, i;
		switch(attr_type)
		{
			case MSRP_Domain:
			{
				en=ub_esarray_ele_nums(addrdl.msrp_dm);
				if (en == 0)
				{
					DPRINT("%s: No msrp %s list on %s msrp_dm", __func__, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication", xmrpd_app_info->netdev);
					res = -1;
				}
				else
				{
					res = -1;
					for(i=0;i<en;i++){
						msrp_firstvalue_data_t *msfd=(msrp_firstvalue_data_t *)ub_esarray_get_ele(addrdl.msrp_dm, i);
						DPRINT("%s: msrp_dm [vid, src_id, src_priority] = [%d,%d,%d] in %s list ", __func__, msfd->domain.srclass_vid, msfd->domain.srclass_id, msfd->domain.srclass_priority, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication");
						if (msfd->domain.srclass_id == xmrpd_app_info->mrp_data[appno].domain_info.srclass_id &&
							msfd->domain.srclass_priority == xmrpd_app_info->mrp_data[appno].domain_info.srclass_priority && 
							msfd->domain.srclass_vid == xmrpd_app_info->mrp_data[appno].domain_info.srclass_vid)
						{
							DPRINT("%s: Matched msrp_dm [vid, src_id, src_priority] = [%d,%d,%d] in %s list ", __func__, msfd->domain.srclass_vid, msfd->domain.srclass_id, msfd->domain.srclass_priority, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication");
							res = 0;
							break;
						}
					}
				}
			}
			break;
			case MSRP_TalkerAdvertise:
			{
				en=ub_esarray_ele_nums(addrdl.msrp_ta);
				if (en == 0)
				{
					DPRINT("%s:%s No msrp %s list on %s msrp_ta", __func__, xmrpd_app_info->mrp_data[appno].sstream_id, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication", xmrpd_app_info->netdev);
					res = -1;
				}
				else
				{
					res = -1;
					for(i=0;i<en;i++)
					{
						msrp_firstvalue_data_t *msfd=(msrp_firstvalue_data_t *)ub_esarray_get_ele(addrdl.msrp_ta, i);
						if ( memcmp(msfd->stream.stream_id, xmrpd_app_info->mrp_data[appno].stream_info.stream_id,sizeof(ub_streamid_t)) == 0)
						{

							static int print_ta_counter=0;
							if (print_ta_counter % PRINT_EVERY_N_PACKET == 0)
							{
								char sid[24];
								bsid2ssid(xmrpd_app_info->mrp_data[appno].stream_info.stream_id, sid);
								DPRINT("%s: Found msrp_ta [sid] = [%s] in %s list ", __func__, sid, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication");
							}
							
							print_ta_counter++;
							if (print_ta_counter==PRINT_EVERY_N_PACKET) {print_ta_counter=0;}
							
							res = 0;
							break;
						}
					}
				}
			}
			break;
			case MSRP_Listener:
			{
				en=ub_esarray_ele_nums(addrdl.msrp_ls);
				if (en == 0)
				{
					DPRINT("%s:%s No msrp %s list on %s msrp_ta", __func__, xmrpd_app_info->mrp_data[appno].sstream_id, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication", xmrpd_app_info->netdev);
					res = -1;
				}
				else
				{
					res = -1;
					for(i=0;i<en;i++)
					{
						msrp_firstvalue_data_t *msfd=(msrp_firstvalue_data_t *)ub_esarray_get_ele(addrdl.msrp_ls, i);
						if ( memcmp(msfd->stream.stream_id, xmrpd_app_info->mrp_data[appno].stream_info.stream_id,sizeof(ub_streamid_t)) == 0)
						{
							static int print_l_counter=0;
							if (print_l_counter % PRINT_EVERY_N_PACKET == 0)
							{
								char sid[24];
								bsid2ssid(xmrpd_app_info->mrp_data[appno].stream_info.stream_id, sid);
								DPRINT("%s: Found msrp_ls [sid] = [%s] in %s list ", __func__, sid, (lsttype==EXTCTRL_OPERATION_REQ_LIST)?"oper":"indication");
							}
							
							print_l_counter++;
							if (print_l_counter==PRINT_EVERY_N_PACKET) {print_l_counter=0;}
							
							res = 0;
							break;
						}
					}
				}
			}
			break;
			case MSRP_TalkerFailed: // fall thru (not handled yet)
			default:
			break;
		}
	}


	// close at the end
	mrp_extc_dlist_close(&addrdl);
	return res;
}

static int mrpmanager_mvrp_leave(xmrpd_app_data_t *xmrpd_app_info , uint8_t appno)
{
	int res;
	char cmd_buf[128];
	snprintf(cmd_buf, sizeof(cmd_buf), "D %s,mvrp A vid=%d", xmrpd_app_info->netdev, xmrpd_app_info->mrp_data[appno].vid);
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);
	return res;
}
/// @brief Declar mvrp VLAN ID to neighbors
/// @param xmrpd_app_info 
/// @return 
static int mrpmanager_declare_vid(xmrpd_app_data_t *xmrpd_app_info , uint8_t appno)
{
	int res;
	char cmd_buf[128];

	snprintf(cmd_buf, sizeof(cmd_buf), "W %s,mvrp C 1", xmrpd_app_info->netdev); // enable `write`
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	snprintf(cmd_buf, sizeof(cmd_buf), "R %s,mvrp C", xmrpd_app_info->netdev); // read and confirm addrdl.ext_ctrl = 1
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	if (res == 0 && xmrpd_app_info->mrp_data[appno].addrdl.ext_ctrl == 1)
	{
		// register vid
		snprintf(cmd_buf, sizeof(cmd_buf), "W %s,mvrp A vid=%d", xmrpd_app_info->netdev, xmrpd_app_info->mrp_data[appno].vid);
		res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
		DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

		snprintf(cmd_buf, sizeof(cmd_buf), "U %s,mvrp", xmrpd_app_info->netdev);
		res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
		DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

		mrp_extc_dlist_t addrdl;
		mrp_extc_dlist_init(&addrdl);
		snprintf(cmd_buf, sizeof(cmd_buf), "R %s,mvrp O", xmrpd_app_info->netdev);
		res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &addrdl);
		if (res != 0)
		{
			DPRINT("%s: No entry in Operation List: '%s', res=%d ", __func__, cmd_buf, res);
			res = -1;
		}
		else
		{
			int en, i;
			en=ub_esarray_ele_nums(addrdl.mvrp);
			if (en == 0)
			{
				DPRINT("%s: No mvrp Operation list on %s ", __func__, xmrpd_app_info->netdev);
				res = -1;
			}
			else
			{
				res = -1;
				for(i=0;i<en;i++){
					mvrp_firstvalue_data_t *mvfd=(mvrp_firstvalue_data_t *)ub_esarray_get_ele(addrdl.mvrp, i);
					if (mvfd->vid == xmrpd_app_info->mrp_data[appno].vid)
					{
						DPRINT("%s: Found vid = %d in OperListReq ", __func__, mvfd->vid);
						res = 0;
						break;
					}
				}
			}
		}

		// close at the end
		mrp_extc_dlist_close(&addrdl);
	}

	return res;
}

/// @brief Declare msrp Domain to neighbors
/// @param xmrpd_app_info 
/// @param portIndex 
/// @param event 
/// @param srclass_id 
/// @param srclass_priority 
/// @param srclass_vid 
/// @return 
static int mrpmanager_declare_domain(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno, int portIndex, uint8_t event,
				uint8_t srclass_id, uint8_t srclass_priority, uint16_t srclass_vid)
{
	int res;
	char cmd_buf[128];

	snprintf(cmd_buf, sizeof(cmd_buf), "W %s,msrp C 1", xmrpd_app_info->netdev); // enable `write`
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	snprintf(cmd_buf, sizeof(cmd_buf), "R %s,msrp C", xmrpd_app_info->netdev); // read and confirm addrdl.ext_ctrl = 1
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	if (res == 0 && xmrpd_app_info->mrp_data[appno].addrdl.ext_ctrl == 1)
	{
		// register domain
		snprintf(cmd_buf, sizeof(cmd_buf), "W %s,msrp A D vid=%d,cid=%d,pri=%d", 
				 xmrpd_app_info->netdev, 
				 srclass_vid,
				 srclass_id,
				 srclass_priority);
		res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
		DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

		snprintf(cmd_buf, sizeof(cmd_buf), "U %s,msrp", xmrpd_app_info->netdev);
		res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
		DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

		if (res == 0)
		{
			res = check_msrp_oper_req_list_exist(xmrpd_app_info, appno, MSRP_Domain);
		}
	}

	return res;
}

// Format: "01-02-03-04-05-06:00-00"
char *bsid2ssid(ub_streamid_t bsid, char *ssid)
{
	int i;
	for(i=0;i<7;i++){
		ub_byte2hexstr(bsid[i], &ssid[i*3]);
		ssid[(i*3)+2]='-';
	}
	ub_byte2hexstr(bsid[7], &ssid[7*3]);
	ssid[23]=0;
	ssid[17]=':';
	return ssid;
}

static int mrpmanager_declare_listener(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno, mrpdu_attribute_event_t ev, uint8_t *stream_id)
{
	int res;
	char cmd_buf[128];

	snprintf(cmd_buf, sizeof(cmd_buf), "W %s,msrp C 1", xmrpd_app_info->netdev); // enable `write`
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	snprintf(cmd_buf, sizeof(cmd_buf), "R %s,msrp C", xmrpd_app_info->netdev); // read and confirm addrdl.ext_ctrl = 1
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	if (res == 0 && xmrpd_app_info->mrp_data[appno].addrdl.ext_ctrl == 1)
	{
		char sid[24];
		bsid2ssid(stream_id, sid);

		if (ev == AEV_New)
		{
			// register listener=2, fpe=2 mean MSRP_FP_Ready
			snprintf(cmd_buf, sizeof(cmd_buf), "W %s,msrp A L sid=%s,fpe=2", 
					xmrpd_app_info->netdev, 
					sid);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

			snprintf(cmd_buf, sizeof(cmd_buf), "U %s,msrp", xmrpd_app_info->netdev);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);
			if (res == 0)
			{
				res = check_msrp_oper_req_list_exist(xmrpd_app_info, appno, MSRP_Listener);
			}
		}
		else if (ev == AEV_Lv)
		{
			// D cbeth0,msrp A L sid=11-12-13-14-15-16:21-22
			snprintf(cmd_buf, sizeof(cmd_buf), "D %s,msrp A L sid=%s", 
					xmrpd_app_info->netdev, 
					sid);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

			snprintf(cmd_buf, sizeof(cmd_buf), "U %s,msrp", xmrpd_app_info->netdev);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);
			res = 0;
		}
	}

	return res;
}

char *bmac2smac(ub_macaddr_t bmac, char *smac)
{
	int i;
	for(i=0;i<5;i++){
		ub_byte2hexstr(bmac[i], &smac[i*3]);
		smac[(i*3)+2]='-';
	}
	ub_byte2hexstr(bmac[5], &smac[5*3]);
	smac[17]=0;
	return smac;
}

static int mrpmanager_declare_talker_ad(
				xmrpd_app_data_t *xmrpd_app_info,
				uint8_t appno,
				mrpdu_attribute_event_t ev,
				uint8_t *stream_id, uint8_t *destmac,
				uint16_t vlan_id, uint16_t max_frame_size,
				uint16_t max_intv_frames, uint8_t priority_rank_reserved,
				uint32_t accum_latency)
{
	int res;
	char cmd_buf[128];

	snprintf(cmd_buf, sizeof(cmd_buf), "W %s,msrp C 1", xmrpd_app_info->netdev); // enable `write`
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	snprintf(cmd_buf, sizeof(cmd_buf), "R %s,msrp C", xmrpd_app_info->netdev); // read and confirm addrdl.ext_ctrl = 1
	res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &xmrpd_app_info->mrp_data[appno].addrdl);
	DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

	if (res == 0 && xmrpd_app_info->mrp_data[appno].addrdl.ext_ctrl == 1)
	{
		char sid[24];
		memset(sid, 0, sizeof(sid));
		bsid2ssid(stream_id, sid);

		char da[18];
		memset(da, 0, sizeof(da));
		bmac2smac(destmac, da);

		if (ev == AEV_New)
		{
			// register talker
			// W enp3s0,msrp A TA sid=01-02-03-04-05-06:00-00,da=91-E0-F0-00-FE-00,vid=100,mfs=1500,mif=1,pcp=2,ra=1,ac=100000
			uint8_t pcp =priority_rank_reserved>>5;
			uint8_t rank =(priority_rank_reserved>>4) & 1;
			snprintf(cmd_buf, sizeof(cmd_buf), "W %s,msrp A TA sid=%s,da=%s,vid=%d,mfs=%d,mif=%d,pcp=%d,ra=%d,ac=%d", 
					xmrpd_app_info->netdev, 
					sid,
					da,
					vlan_id,
					max_frame_size,
					max_intv_frames,
					pcp,
					rank,
					accum_latency
					);
			DPRINT("%s: begin mrp_extc_proc_cmd: '%s'", __func__, cmd_buf);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

			snprintf(cmd_buf, sizeof(cmd_buf), "U %s,msrp", xmrpd_app_info->netdev);
			DPRINT("%s: begin mrp_extc_proc_cmd: '%s'", __func__, cmd_buf);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

			if (res == 0)
			{
				res = check_msrp_oper_req_list_exist(xmrpd_app_info, appno, MSRP_TalkerAdvertise);
			}
		}
		else if (ev == AEV_Lv)
		{
			// D cbeth0,msrp A TA sid=11-12-13-14-15-16:21-22
			snprintf(cmd_buf, sizeof(cmd_buf), "D %s,msrp A TA sid=%s", 
					xmrpd_app_info->netdev, 
					sid);
			DPRINT("%s: begin mrp_extc_proc_cmd: '%s'", __func__, cmd_buf);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);

			snprintf(cmd_buf, sizeof(cmd_buf), "U %s,msrp", xmrpd_app_info->netdev);
			DPRINT("%s: begin mrp_extc_proc_cmd: '%s'", __func__, cmd_buf);
			res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf,  &xmrpd_app_info->mrp_data[appno].addrdl);
			DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);
		}
	}
	return res;
}

static int search_configure_vid_in_lst(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno, mrp_extctrl_list_type lst_type)
{
	int res = 0;
	int en, i;
	char cmd_buf[128];
	mvrp_firstvalue_data_t *mvfd;
	mrp_extc_dlist_t addrdl;

	switch(lst_type)
	{
		case EXTCTRL_ADMIN_REQ_LIST:
			snprintf(cmd_buf, sizeof(cmd_buf), "R %s,mvrp A", xmrpd_app_info->netdev);
			break;
		case EXTCTRL_OPERATION_REQ_LIST:
			snprintf(cmd_buf, sizeof(cmd_buf), "R %s,mvrp O", xmrpd_app_info->netdev);
			break;
		case EXTCTRL_INDICATION_LIST:
			snprintf(cmd_buf, sizeof(cmd_buf), "R %s,mvrp I", xmrpd_app_info->netdev);
			break;
		default:
			return -1;
	}

	mrp_extc_dlist_init(&addrdl);

	if (res == 0)
	{
		res=mrp_extc_proc_cmd(xmrpd_app_info->mrpgcfg, cmd_buf, &addrdl);
		// DPRINT("%s: mrp_extc_proc_cmd: '%s', res=%d ", __func__, cmd_buf, res);
	}

	// After reading, all of existing vlans are stored in xmrpd_app_info->mrp_data[appno].addrdl.mvrp
	if (res == 0)
	{
		res = -1;
		en=ub_esarray_ele_nums(addrdl.mvrp);
		for(i=0;i<en;i++){
			mvfd=(mvrp_firstvalue_data_t *)ub_esarray_get_ele(addrdl.mvrp, i);
			
			if(mvfd->vid == xmrpd_app_info->mrp_data[appno].vid)
			{
				static int print_vid_counter=0;
				if (print_vid_counter % PRINT_EVERY_N_PACKET == 0)
				{
					DPRINT("%s: found vid=%d in %s list", __func__, mvfd->vid, (lst_type == EXTCTRL_INDICATION_LIST)?"indication":"operation");
				}
				
				print_vid_counter++;
				if (print_vid_counter==PRINT_EVERY_N_PACKET) {print_vid_counter=0;}

				res = 0;
				break;
			}
		}
	}
	else
	{
		res = -1;
	}

	mrp_extc_dlist_close(&addrdl);
	return res;
}

static int mvrp_state_machine(xmrpd_app_data_t *xmrpd_app_info , uint8_t appno)
{
	int ret;
	mrp_data_t *mrp_data=&xmrpd_app_info->mrp_data[appno];

	switch(mrp_data->mvrp_data.mrp_state){
		case MVRP_STATE_IDLE:
			return -1;
		case MVRP_STATE_WAIT_GPTP_SYNC:
			if (EnetApp_isGptpSync(xmrpd_app_info->ydrd))
			{
				DPRINT("%s: GPTP Sync-ed on dev %s\n",__func__, xmrpd_app_info[appno].netdev);
				mrp_data->mvrp_data.mrp_state = MVRP_STATE_STARTED;
			}
			else
			{
				DPRINT("%s: Waiting gPtp sync on %s\n",__func__, xmrpd_app_info[appno].netdev);
			}
			break;
		case MVRP_STATE_STARTED:
			if (xmrpd_app_info->mrp_data[appno].mode == TALKER_MODE)
			{
				if( mrpmanager_declare_vid(xmrpd_app_info, appno) < 0 ){
					return -1;
				}
				mrp_data->mvrp_data.mrp_state = MVRP_STATE_REGVLAN;
				DPRINT("%s: talker[vid=%d]: STARTED -> REGVLAN \n",__func__, mrp_data->vid);
			}
			else
			{
				// listener, we need to wait for talker side to declare vid
				ret = search_configure_vid_in_lst(xmrpd_app_info, appno, EXTCTRL_INDICATION_LIST);
				if( ret < 0 ){
					DPRINT("%s: listener: waiting vid=%d \n",__func__, xmrpd_app_info->mrp_data[appno].vid);
					return 0;
				}else{
					DPRINT("%s: listener: received vid=%d\n",__func__, xmrpd_app_info->mrp_data[appno].vid);
					if( mrpmanager_declare_vid(xmrpd_app_info, appno) < 0 ){
						return -1;
					}
					mrp_data->mvrp_data.mrp_state = MVRP_STATE_REGVLAN;
					DPRINT("%s: listener[vid=%d]: STARTED -> REGVLAN \n",__func__, mrp_data->vid);
				}
			}

			break;
		case MVRP_STATE_REGVLAN:
			if (xmrpd_app_info->mrp_data[appno].mode == TALKER_MODE)
			{
				ret = search_configure_vid_in_lst(xmrpd_app_info, appno, EXTCTRL_INDICATION_LIST);
				if( ret < 0 ){
					DPRINT("%s: talker: waiting vid=%d \n",__func__, mrp_data->vid);
					return 0;
				}else{
					DPRINT("%s: talker: received vid=%d\n",__func__, mrp_data->vid);
					mrp_data->mvrp_data.mrp_state = MVRP_STATE_RUNNING;
					mrp_data->msrp_data.mrp_state = MSRP_STATE_STARTED;
					DPRINT("%s: talker[vid=%d]: REGVLAN -> RUNNING \n",__func__, mrp_data->vid);
					DPRINT("%s: MSRP talker[sid=%s]: IDLE -> STARTED \n",__func__, mrp_data->sstream_id);
				}
			}
			else
			{
				mrp_data->mvrp_data.mrp_state = MVRP_STATE_RUNNING;
				mrp_data->msrp_data.mrp_state = MSRP_STATE_STARTED;
				DPRINT("%s: listener[vid=%d]: REGVLAN -> RUNNING \n",__func__, mrp_data->vid);
			}
			break;
		case MVRP_STATE_RUNNING:
			ret = search_configure_vid_in_lst(xmrpd_app_info, appno, EXTCTRL_INDICATION_LIST);
			if( ret < 0 ) // not found
			{
				DPRINT("%s: %s: target vid=%d dissapeared\n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->vid);
				mrp_data->mvrp_data.mrp_state = MVRP_STATE_CLOSING;
				DPRINT("%s: %s[vid=%d]: RUNNING -> CLOSING \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->vid);
				return -1;
			}
			break;
		case MVRP_STATE_CLOSING:
			mrpmanager_mvrp_leave(xmrpd_app_info, appno);
			mrp_data->mvrp_data.mrp_state = MVRP_STATE_CLOSED;
			DPRINT("%s: %s[vid=%d]: CLOSING -> CLOSED \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->vid);
			break;
		case MVRP_STATE_CLOSED:
			mrp_data->mvrp_data.mrp_state = MVRP_STATE_IDLE;
			/* TODO: Check if MVRP closed */
			break;
		default:
			DPRINT("Invalid mvrp state %d\n",mrp_data->mvrp_data.mrp_state);
			break;
	}
	return 0;
}

/// @brief If talker, check current registerred stream is already in 'Operation request list' or not.
///				if not, declare talker to 'Admin request list'
///		   If listener, check current registerred stream is already in 'Operation request list' or not.
///				if not, declare listener to 'Admin request list'
/// @param xmrpd_app_info 
/// @return 
static int check_reged_update(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno)
{
	int ret;

	// Check if we already registered stream in Operation List request
	ret = check_msrp_attr_list_exist(xmrpd_app_info, appno, (xmrpd_app_info->mrp_data[appno].mode == LISTENER_MODE)?MSRP_Listener:MSRP_TalkerAdvertise, EXTCTRL_OPERATION_REQ_LIST );
	if( ret < 0 )
	{
		DPRINT("%s: We haven't registered. Join new!!\n",__func__);
		if( xmrpd_app_info->mrp_data[appno].mode == LISTENER_MODE ){
			if( mrpmanager_declare_listener(xmrpd_app_info, appno, AEV_New,
						xmrpd_app_info->mrp_data[appno].stream_info.stream_id) < 0 ){
				return -1;
			}
		}else{
			if( mrpmanager_declare_talker_ad(xmrpd_app_info, appno, AEV_New,
						xmrpd_app_info->mrp_data[appno].stream_info.stream_id, xmrpd_app_info->mrp_data[appno].stream_info.destmac,
						xmrpd_app_info->mrp_data[appno].stream_info.vlan_id, xmrpd_app_info->mrp_data[appno].stream_info.max_frame_size,
						xmrpd_app_info->mrp_data[appno].stream_info.max_intv_frames, xmrpd_app_info->mrp_data[appno].stream_info.priority_rank_reserved,
						xmrpd_app_info->mrp_data[appno].stream_info.accum_latency) < 0 ){
				return -1;
			}
		}
		return -1;
	}

	return 0;
}

/// @brief Check target stream is existed in the other side
///			if talker, get indication list listener
///			if listener, get indication list talker
/// @param xmrpd_app_info 
/// @return 
static int check_target_domain_existense(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno)
{
	return check_msrp_attr_list_exist(xmrpd_app_info, appno, MSRP_Domain, EXTCTRL_INDICATION_LIST);
}

static int msrp_state_machine(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno)
{
	mrp_data_t *mrp_data=&xmrpd_app_info->mrp_data[appno];
	uint64_t ts64;

	switch(mrp_data->msrp_data.mrp_state){
		case MSRP_STATE_IDLE:
			// wait ultil vlan registered
			return 0;
		case MSRP_STATE_STARTED:
			/// Declare domain in advance. The declared domain should stored in oper-req-list
			if( mrpmanager_declare_domain(xmrpd_app_info, appno, 0, AEV_New,
						mrp_data->domain_info.srclass_id,
						mrp_data->domain_info.srclass_priority,
						mrp_data->domain_info.srclass_vid) < 0 ){
				return -1;
			}
			mrp_data->msrp_data.mrp_state = MSRP_STATE_REGISTERED_DOMAIN;
			DPRINT("%s: %s[sid=%s]: MSRP_STATE_STARTED -> MSRP_STATE_REGISTERED_DOMAIN \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
			break;

		case MSRP_STATE_REGISTERED_DOMAIN:
			if( xmrpd_app_info->mrp_data[appno].mode == TALKER_MODE )
			{
				// Declare new Talker if we haven't register this Talker before.
				check_reged_update(xmrpd_app_info, appno);
			}
			else
			{
				#if 1
				// okay now will ignore 'domain case' and go to declare msrp listener
				#else
				// For listener, check if other side already exist same domain with us 
				if( check_msrp_attr_list_exist(xmrpd_app_info, MSRP_Domain, EXTCTRL_INDICATION_LIST) < 0 )
				{
					return 0; // Not found
				}
				#endif
			}
			mrp_data->msrp_data.mrp_state = MSRP_STATE_WAIT_TARGET;
			DPRINT("%s: %s[sid=%s]: MSRP_STATE_REGISTERED_DOMAIN -> MSRP_STATE_WAIT_TARGET \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
			break;
		case MSRP_STATE_WAIT_TARGET:
			if( xmrpd_app_info->mrp_data[appno].mode == LISTENER_MODE )
			{
				// Check if other side has talker which has same stream id with our expected listener's stream id
				if( check_msrp_attr_list_exist(xmrpd_app_info, appno, MSRP_TalkerAdvertise, EXTCTRL_INDICATION_LIST) == 0 )
				{
					// Okay. we found target talker. We can declare listener now (if not registered before)
					check_reged_update(xmrpd_app_info, appno);
				}
				else
				{
					DPRINT("%s: target not found yet \n",__func__);
					return 0;
				}
			}

			// If talker, we already declared before, now wait for newly declared listener
			mrp_data->msrp_data.mrp_state = MSRP_STATE_WAIT_REGIST;
			DPRINT("%s: %s[sid=%s]: MSRP_STATE_WAIT_TARGET -> MSRP_STATE_WAIT_REGIST \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
			break;

		case MSRP_STATE_WAIT_REGIST:
			// if( check_reged_update(xmrpd_app_info, appno) ) return 0;
			if( check_msrp_attr_list_exist(xmrpd_app_info, appno, (mrp_data->mode==TALKER_MODE)?MSRP_Listener:MSRP_TalkerAdvertise, EXTCTRL_INDICATION_LIST) < 0 )
				return 0; // waiting for target exist

			mrp_data->msrp_data.mrp_state = MSRP_STATE_RUNNING;
			DPRINT("%s: %s[sid=%s]: MSRP_STATE_WAIT_REGIST -> MSRP_STATE_RUNNING \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
			xmrpd_app_info->mrp_data[appno].stream_available = true;
			break;

		case MSRP_STATE_RUNNING:
		{
			// In this state, we always check whether the target may dissapear (with timeout) and close the msrp
			bool target_still_exist=true;
			if( xmrpd_app_info->mrp_data[appno].mode == LISTENER_MODE )
			{
				if( check_msrp_attr_list_exist(xmrpd_app_info, appno, MSRP_TalkerAdvertise, EXTCTRL_INDICATION_LIST) < 0 )
				{
					target_still_exist = false;
				}
			}
			else
			{
				if( check_msrp_attr_list_exist(xmrpd_app_info, appno, MSRP_Listener, EXTCTRL_INDICATION_LIST) < 0 )
				{
					target_still_exist = false;
				}
			}

			if( !target_still_exist )
			{
				ts64 = ub_rt_gettime64();
				if( mrp_data->msrp_data.lt_timeout && (ts64 > mrp_data->msrp_data.lt_timeout) )
				{
					DPRINT("%s: %s[sid=%s]: target disappeared\n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
					mrp_data->msrp_data.mrp_state = MSRP_STATE_CLOSING;
					xmrpd_app_info->mrp_data[appno].stream_available = false;
					DPRINT("%s: %s[sid=%s]: MSRP_STATE_RUNNING -> MSRP_STATE_CLOSING \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
					return -1;
				}
				
				DPRINT("%s: %s[sid=%s]: target may disappear\n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
				if( mrp_data->msrp_data.lt_timeout == 0 )
				{
					mrp_data->msrp_data.lt_timeout = ts64 + DISAPPEAR_TIMEOUT;
				}
			}
			else
			{
				// reset timeout counter if target appear again or still existed
				mrp_data->msrp_data.lt_timeout = 0;
			}
		}
		break;
		case MSRP_STATE_CLOSING:
			if( xmrpd_app_info->mrp_data[appno].mode == TALKER_MODE ){
				if( mrpmanager_declare_talker_ad(xmrpd_app_info, appno, AEV_Lv,
							xmrpd_app_info->mrp_data[appno].stream_info.stream_id, xmrpd_app_info->mrp_data[appno].stream_info.destmac,
							xmrpd_app_info->mrp_data[appno].stream_info.vlan_id, xmrpd_app_info->mrp_data[appno].stream_info.max_frame_size,
							xmrpd_app_info->mrp_data[appno].stream_info.max_intv_frames, xmrpd_app_info->mrp_data[appno].stream_info.priority_rank_reserved,
							xmrpd_app_info->mrp_data[appno].stream_info.accum_latency) < 0 ){
					return -1;
				}
			}else{
				if( mrpmanager_declare_listener(xmrpd_app_info, appno, AEV_Lv,
							xmrpd_app_info->mrp_data[appno].stream_info.stream_id) < 0 ){
					return -1;
				}
			}
			mrp_data->msrp_data.mrp_state = MSRP_STATE_CLOSED;
			DPRINT("%s: %s[sid=%s]: MSRP_STATE_CLOSING -> MSRP_STATE_CLOSED \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
			break;
		case MSRP_STATE_CLOSED:
			DPRINT("%s: %s[sid=%s]: MSRP_STATE_CLOSED -> MSRP_STATE_IDLE \n",__func__, (mrp_data->mode == TALKER_MODE)?"talker":"listener", mrp_data->sstream_id);
			mrp_data->msrp_data.mrp_state = MSRP_STATE_IDLE;
			return 0;
		default:
			DPRINT("Invalid msrp state %d\n",mrp_data->msrp_data.mrp_state);
			break;
	}
	return 0;
}

static void init_mrp_data(xmrpd_app_data_t *xmrpd_app_info)
{
	for (uint8_t appno=0; appno<xmrpd_app_info->avb_app_num; appno++)
	{
		mrp_data_t *mrp_data=&xmrpd_app_info->mrp_data[appno];

		mrp_data->mvrp_data.mrp_state = MVRP_STATE_IDLE;
		mrp_data->msrp_data.mrp_state = MSRP_STATE_IDLE;
		mrp_data->msrp_data.lt_timeout = 0;
	}
}

static int mrpmanager_init(xmrpd_app_data_t *xmrpd_app_info)
{
	int res;
	mrpgcfgd_t *mgcfgd;
	mgcfgd=mrpgcfg_init(0, xmrpd_app_info->dbname, NULL, true, false);

	/* Wait for gPTP/AVTP/XMRPD to be ready */
	res=mrp_extc_wait_xmrpd(mgcfgd, 0, 2000);
	if (res == 0)
	{
		DPRINT("XMRPD started. Starting XMRPC \n");
	}
	else
	{
		DPRINT("XMRPD started error. exiting... \n");
		return -1;
	}

	init_mrp_data(xmrpd_app_info);

	xmrpd_app_info->mrpgcfg = mgcfgd;

	if( mgcfgd )
		return 0;
	else
		return -1;
}

static int GetArgc(char *argv[])
{
    int argc = 0;
    while (argv[argc] != NULL) argc++;
    return argc;
}

static void *avtp_testclient_fn(void *arg)
{
	DPRINT("%s: \n",__func__);
	mrp_data_t *mrp_data = (mrp_data_t *)arg;

	char s_vid[4];
	char s_streamid[24];

	snprintf(s_vid, sizeof(s_vid), "%d", mrp_data->vid);
	char *argv[]={"avtp_testclient", "-d", mrp_data->netdev,
        "-m", (mrp_data->mode==TALKER_MODE)?"t":"l", "-B", "1000", "-v", s_vid, "-C", "-c",
        "-S", ub_bsid2ssid(mrp_data->stream_info.stream_id, s_streamid), "-b", "5", "-i", "-u", NULL}; /* '-u' must be the last opt */

    DPRINT("avtp_testclient:%s sid=%s/vid=%s start", (mrp_data->mode==TALKER_MODE)?"talker":"listener", s_streamid, s_vid);
    avtp_testclient(GetArgc(argv), argv);
	return NULL;
}

static uint8_t gAvtpStackBuf0[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gAvtpStackBuf1[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gAvtpStackBuf2[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gAvtpStackBuf3[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gAvtpStackBuf4[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gAvtpStackBuf5[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gAvtpStackBuf6[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));

static void set_thread_stack(cb_tsn_thread_attr_t* attr, uint8_t appno)
{
	if (appno == 0) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf0[0]);
	else if (appno == 1) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf1[0]);
	else if (appno == 2) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf2[0]);
	else if (appno == 3) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf3[0]);
	else if (appno == 4) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf4[0]);
	else if (appno == 5) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf5[0]);
	else if (appno == 6) cb_tsn_thread_attr_set_stackaddr(attr, &gAvtpStackBuf6[0]);
}

#define AVTP_TASK_PRIORITY	(2)
static int run_avtp_testclient(xmrpd_app_data_t *xmrpd_app_info, uint8_t appno)
{
	cb_tsn_thread_attr_t attr;

	cb_tsn_thread_attr_init(&attr, AVTP_TASK_PRIORITY, sizeof(gAvtpStackBuf0), "avtp_testclient");
	set_thread_stack(&attr, appno);
    
	if(CB_THREAD_CREATE(&xmrpd_app_info->mrp_data[appno].avtp_tc_thread, &attr, avtp_testclient_fn, &xmrpd_app_info->mrp_data[appno]))
	{
		DPRINT("%s: can't run avtpd_testclient\n",__func__);
		return -1;
	}

	return 0;
}

int mrp_linkcheck(xmrpd_app_data_t *xmrpd_app_info)
{
	int res;
	char key[UC_MAX_KEYSIZE];
	char ifname[UC_MAX_KEYSIZE -6];
	uint32_t ksize;
	void *value=NULL;
	uint32_t updown;
	uint32_t vsize;
	if (!xmrpd_app_info->linksem) {return -1;}
	if(uc_notice_sig_trywait(true, xmrpd_app_info->linksem)!=0){return 1;}
	res=uc_nc_get_notice_act(xmrpd_app_info->ucntd, xmrpd_app_info->dbald, xmrpd_app_info->semname, key, &ksize);
	if(res!=0){
		DPRINT("%s:failed in uc_nc_get_notice_act, res=%d\n", __func__, res);
		return 0;
	}

	if((ksize<5u) || (key[3]!=IETF_INTERFACES_OPER_STATUS)){
		DPRINT("%s: not expected notice\n", __func__);
		return 0;
	}
	res=uc_dbal_get(xmrpd_app_info->dbald, key, ksize, &value, &vsize);
	if(res!=0){
		DPRINT("%s: can't read oper-status\n", __func__);
		return 0;
	}
	// key+4:255, key+5:size, key+6:ifname
	memset(ifname, 0, sizeof(ifname));
	memcpy(ifname, &key[6], strlen(&key[6])+1);
	updown = *((uint32_t*)value);
	(void)uc_dbal_get_release(xmrpd_app_info->dbald, key, ksize, value, vsize);
	if (memcmp(ifname, xmrpd_app_info->netdev, strlen(xmrpd_app_info->netdev)) == 0)
	{
		if(updown==1)
		{
			DPRINT("%s: %s up\n", __func__, ifname);
			for (int i=0; i<xmrpd_app_info->avb_app_num; i++)
			{
				xmrpd_app_info->mrp_data[i].mvrp_data.mrp_state = MVRP_STATE_WAIT_GPTP_SYNC;
			}
			// Register CBS
			(void)EnetApp_setMrpExtControlConfig(xmrpd_app_info->ydrd, xmrpd_app_info->ucntd, xmrpd_app_info->netdev);
			EnetApp_registerIdleSlope(xmrpd_app_info->dbald, xmrpd_app_info->ydrd, xmrpd_app_info->ucntd, xmrpd_app_info->netdev);
		}
		else
		{
			DPRINT("%s: %s down\n", __func__, ifname);
			for (int i=0; i<xmrpd_app_info->avb_app_num; i++)
			{
				if (xmrpd_app_info->mrp_data[i].mvrp_data.mrp_state != MVRP_STATE_IDLE)
				{
					DPRINT("%s mvrp appno[%d] state changed from %d to MVRP_STATE_CLOSING\n", 
							__func__, 
							i,
							xmrpd_app_info->mrp_data[i].mvrp_data.mrp_state);
					xmrpd_app_info->mrp_data[i].mvrp_data.mrp_state = MVRP_STATE_CLOSING;
					xmrpd_app_info->mrp_data[i].msrp_data.mrp_state = MSRP_STATE_CLOSING;
				}
			}
		}
	}
	else
	{
		DPRINT("%s: We don't care about %s\n", __func__, ifname);
	}
	return 0;
	
}

int run_xmrpd_app(xmrpd_app_data_t *xmrpd_app_info)
{
	// int res=0;

	/* Wait for xmrpd started and initialize mrp manager */
	if( mrpmanager_init(xmrpd_app_info) ) {
		DPRINT("%s: Error at initializing mrpmanager. Exiting\n",__func__);
		return -1;
	}

	while(true)
	{
		if (mrp_linkcheck(xmrpd_app_info) == -1) {return -1;}

		for (uint8_t appno=0; appno<xmrpd_app_info->avb_app_num; appno++)
		{
			mvrp_state_machine(xmrpd_app_info, appno);
			msrp_state_machine(xmrpd_app_info, appno);

			if( (xmrpd_app_info->mrp_data[appno].stream_available == true) &&
					(xmrpd_app_info->mrp_data[appno].app_running == false) ){
				if( run_avtp_testclient(xmrpd_app_info, appno) < 0 ){
					return -1;
				}
				xmrpd_app_info->mrp_data[appno].app_running=true;
			}

			if( (xmrpd_app_info->mrp_data[appno].stream_available == false) &&
					(xmrpd_app_info->mrp_data[appno].app_running == true) ){
				stop_testclient();
				xmrpd_app_info->mrp_data[appno].app_running=false;
			}
		}

		CB_USLEEP(500000);
	}
}
