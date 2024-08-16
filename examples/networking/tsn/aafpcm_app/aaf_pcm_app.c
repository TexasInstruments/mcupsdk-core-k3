#include "aaf_pcm_app.h"
#include "tsn_conl2/aaf_avtpc_listener.h"
#include "tsn_conl2/aaf_avtpc_talker.h"
#include "sample_audio.h"
#include "tsn_gptp/gptpmasterclock.h"
#include "kernel/dpl/TimerP.h"
#include "ti_dpl_config.h"
#include "debug_log.h"

typedef struct {
	void (*avtpc_close)(void *avtpc_talker);
	int (*avtpc_send)(void *avtpc_talker, uint64_t pts,
			  uint8_t *audio_data, uint32_t data_size);
	void *avtpc_talker;
	int read_size;
	int sent_bytes;
	uint32_t sent_packets;
} audio_talker_t;

typedef struct {
	void (*avtpc_close)(void *avtpc_listener);
	void *avtpc_listener; /* aaf or iec61883_6 */
} audio_listener_t;

audio_talker_t audio_talker;
audio_listener_t audio_listener;

typedef struct {
	audio_talker_t audio_talker;
	audio_listener_t audio_listener;
	conl2_basic_conparas_t bcp;
	int audio_samples; //number of audio samples per AVTP packet
	char* netdev;
} conl2_data_t;

SemaphoreP_Object gTimerSem;

static int audio_aaf_avtp_push_packet(uint8_t *payload, int plsize, avbtp_rcv_cb_info_t *cbinfo, void *cbdata);

static void audio_aaf_avtpc_talker_close(void *avtpc_talker)
{
	if (avtpc_talker) aaf_avtpc_talker_close(avtpc_talker);
}

static void audio_aaf_avtpc_listener_close(void *audio_listener)
{
	if (audio_listener) aaf_avtpc_listener_close(audio_listener);
}

static int audio_aaf_avtpc_talker_send(void *avtpc_talker, uint64_t pts,
					uint8_t *audio_data, uint32_t data_size)
{
	return aaf_avtpc_talker_write(avtpc_talker, pts, audio_data, data_size);
}

static int audio_aaf_talker_init(conl2_basic_conparas_t* basic_param, aaf_avtpc_pcminfo_t* pcm_info)
{
    audio_talker.avtpc_talker = aaf_avtpc_talker_init(basic_param);
	if (!audio_talker.avtpc_talker) {
		DPRINT("%s:failed to open aaf talker\n",__func__);
		return -1;
	}
    aaf_avtpc_set_pcm_info(audio_talker.avtpc_talker, pcm_info);

    audio_talker.avtpc_close = audio_aaf_avtpc_talker_close;
	audio_talker.avtpc_send = audio_aaf_avtpc_talker_send;

	return 0;
}

static int audio_aaf_listener_init(conl2_basic_conparas_t* basic_param, aaf_avtpc_pcminfo_t* pcm_info)
{
    audio_listener.avtpc_listener = aaf_avtpc_listener_init(basic_param, audio_aaf_avtp_push_packet, &audio_listener);
    if (!audio_listener.avtpc_listener) {
		DPRINT("%s:failed to open aaf listener\n",__func__);
		return -1;
	}
    audio_listener.avtpc_close=audio_aaf_avtpc_listener_close;
    return 0;
}

static void init_default_params(conl2_basic_conparas_t* basic_param, aaf_avtpc_pcminfo_t* pcm_info)
{
    basic_param->vid = 110;
    basic_param->send_ahead_ts = 20000; // ahead 20ms
    ub_streamid_t streamid = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02};;
    memcpy(basic_param->streamid, streamid, sizeof(streamid));

    ub_macaddr_t mcastmac = {0x91, 0xE0, 0xF0, 0x00, 0xFE, 0x00};
    memcpy(basic_param->mcastmac, mcastmac, sizeof(mcastmac));

    basic_param->time_intv = 250;
    basic_param->max_frm_sz = 1500;
    basic_param->max_intv_frames = 1;
    basic_param->pcp = 2;
    basic_param->avtpd_bufftime_us = 10000;
    basic_param->is_direct = true;
    

    pcm_info->format = AVBTP_AAF_FORMAT_INT_16BIT;
    pcm_info->bit_depth = 16;
    pcm_info->channels = 2;
    pcm_info->srate = 48000;
}
#ifdef AAF_PCM_TALKER_ENABLE
int start_aaf_pcm_talker(char* netdev)
{
    uint64_t pts;
    uint64_t sts, ets, tsdiff; // start and end ts, use to print report
    conl2_basic_conparas_t basic_param;
    aaf_avtpc_pcminfo_t pcm_info;
    int32_t status;

    memset(&basic_param, 0, sizeof(basic_param));
    memset(&pcm_info, 0, sizeof(pcm_info));
    memcpy(basic_param.netdev, netdev, strlen(netdev));
    init_default_params(&basic_param, &pcm_info);

    status = SemaphoreP_constructBinary(&gTimerSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);

    while(gptpmasterclock_init(NULL)){
        UB_LOG(UBL_INFO,"Waiting for tsn_gptpd to be ready...\n");
        CB_USLEEP(100000);
    }

    // 1ms => buffer size = 48 (frames per 1ms) * 1 (ms) * 2 (16 bit-depth) * 2 (channels) = 960 bytes

    if (audio_aaf_talker_init(&basic_param, &pcm_info) == -1) return -1;

    int pcmbuf_size = 48 * 2 * 2; // 960 bytes
    int total_frames = get_payload_sample_size() / pcmbuf_size;
    sts = ub_mt_gettime64();
    // repeat: start from 0 and read until last sync frame

    while(true)
    {
        for (int frame=0; frame<total_frames; frame++)
        {
            SemaphoreP_pend(&gTimerSem, SystemP_WAIT_FOREVER);
            uint8_t* audio_buf = &payload_sample[frame * pcmbuf_size];
            // DPRINT("%s:\n", __func__);
            // ub_hexdump(true, true, &send_data[0], 32, 0x00); // first 16 bytes 
            // DPRINT("\n");

            pts = gptpmasterclock_getts64();
            if (audio_talker.avtpc_send( audio_talker.avtpc_talker, 
                                    pts + basic_param.send_ahead_ts,
                                    audio_buf, 
                                    pcmbuf_size) < 0) 
            {
                return -1;
            }
            audio_talker.sent_packets++;
            audio_talker.sent_bytes += pcmbuf_size;

            ets = ub_mt_gettime64();
            tsdiff = ets - sts;
            if (tsdiff >= UB_SEC_NS) {
                UB_LOG(UBL_INFO,"audio talker sent: %f(packets/sec), %f(mbps)\n",
                    (float)audio_talker.sent_packets/((float)tsdiff/(float)UB_SEC_NS),
                    (float)(audio_talker.sent_bytes * 8000.0f)/(float)tsdiff);
                audio_talker.sent_packets = 0;
                audio_talker.sent_bytes = 0;

                sts = ets;
            }
        }
    }

    return 0;
}
#endif

static int audio_aaf_avtp_push_packet(uint8_t *payload, int plsize,
				avbtp_rcv_cb_info_t *cbinfo, void *cbdata)
{
    static int total_rx_frames = 0;
    audio_listener_t *audio_listener = (audio_listener_t *)cbdata;
    if (!audio_listener) {return -1;}

    avbtp_sd_info_t *rsdinfo=&cbinfo->u.rsdinfo;
    aaf_avtpc_pcminfo_t pcminfo;
    if (rsdinfo->u.aaf.format == AVBTP_AAF_FORMAT_AES3_32BIT)
    {
        UB_LOG(UBL_INFO,"%s unexpected rx format %d\n", __func__, rsdinfo->u.aaf.format);
        return -1;
    }

    if (aaf_avtpc_get_pcm_info(&cbinfo->u.rsdinfo, &pcminfo) == 0)
    {
        /// 48000 frames print one time
        int rx_frames = plsize / (pcminfo.bit_depth / 8) / pcminfo.channels;
        total_rx_frames += rx_frames;
        if (total_rx_frames >= 48000)
        {
            UB_LOG(UBL_INFO,"[RX] pcminfo bdepth[%d] channels[%d] format[%d] srate[%d]\n", 
                         pcminfo.bit_depth, 
                         pcminfo.channels, 
                         pcminfo.format, 
                         pcminfo.srate);
            total_rx_frames = 0;
        }
    }

    return 0;
}

int start_aaf_pcm_listener(char* netdev)
{
    conl2_basic_conparas_t basic_param;
    aaf_avtpc_pcminfo_t pcm_info;

    memset(&basic_param, 0, sizeof(basic_param));
    memset(&pcm_info, 0, sizeof(pcm_info));
    memcpy(basic_param.netdev, netdev, strlen(netdev));
    init_default_params(&basic_param, &pcm_info);

	while(gptpmasterclock_init(NULL)){
		UB_LOG(UBL_INFO,"Waiting for tsn_gptpd to be ready...\n");
		CB_USLEEP(100000);
	}

    if (audio_aaf_listener_init(&basic_param, &pcm_info) == -1) return -1;

    while(true)
    {
        CB_USLEEP(100000);
        ub_log_flush();
    }

    return 0;
}

void avbTimerIsr(void)
{
    SemaphoreP_post(&gTimerSem);
}
