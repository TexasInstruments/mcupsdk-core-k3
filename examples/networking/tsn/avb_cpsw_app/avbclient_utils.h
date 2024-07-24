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
#ifndef __AVB_CLIENT_UTILS_H__
#define __AVB_CLIENT_UTILS_H__

#include <tsn_combase/cb_rate_reporter.h>
#include "avtpc.h"

#define DEFAULT_MCAST_ADDR "91:E0:F0:00:FE:00"
#define DEFAULT_JOIN_ADDR "91:E0:F0:00:FE:00"
#define DEFAULT_STREAMID "00:01:02:03:04:05:00:00"

#define REPORT_HEADER_LEN           (80)

#ifdef AVTP_PLATFORM_INCLUDE
#include AVTP_PLATFORM_INCLUDE
#endif
#ifndef WAIT_AVTPD_READY
#define WAIT_AVTPD_READY
#endif

#ifndef CONSOLE_RFD
#define CONSOLE_RFD 0
#define CONSOLE_READ(buf,len) read(CONSOLE_RFD, buf, len)
#endif

/* Interval for report checking */
#define REPORT_CHECK_INTERVAL_MS    (10)

typedef enum {
    TALKER_MODE=0,
    LISTENER_MODE,
} mode_type;

typedef enum {
    FIXED_DATA=0,
    AVB_TEST_VIDEO,
} data_type;

typedef struct avtptc_data {
    avtpc_data_t *avtpc;
    mode_type mode;
    data_type dtype;
    char *netdev;
    uint16_t sidl2;
    uint16_t vid;
    bool promisc;
    uint16_t max_frame_size;
    uint16_t max_intv_frames;
    uint16_t time_intv;
    int lsem_post_time;
    uint16_t priority;
    double mbps;
    uint8_t data[1500];
#ifndef HAVE_NO_POSIX_CLOCK
    clock_t ct0;
    clock_t ct1;
#endif //HAVE_NO_POSIX_CLOCK
    bool rec_tagged;
    bool no_avtpd;
    char *mcast;
    char *mjoin;
    char *sid;
    bool nodc;
    bool prts;
    bool start_menu;
    int mpsize;
    int ssize;
    int tshape;
    int tsminsl;
    int subtype;
    int quitn;
    char *shsuf;
    char *gshmem;
    int send_interval;
    int tsoffset; //usec unit
    int send_ahead_ts;
    uint64_t recv_tv1;
    uint64_t recv_last_ts;
    int addber;
    int runber;
    int report_interval;           // report interval (in seconds)
    int wthres_latency;            // warning threshold for maximum latency (us unit)
    uint64_t total_err_packets;
    uint64_t total_rx_packets;
    uint32_t report_counter;       // number of shown report
    uint64_t high_latency_count;   // counter for latency values that higher than threshold
    uint64_t total_lost_packets;   // number of lost packets on runtime
    int test_duration;             // the test will be run in `test_duration` seconds
    int avtpd_buftime; //in usec

    cb_rate_reporter_t rate_reporter;
    bool no_healthcheck; //no health check between the avtpd and avtpc
    bool avtpc_expandts32; //avtpc expands ts32 to ts64, the avtpd will not do
    bool filter_destmac;
} avtptc_data_t;

int GetArgc(char *argv[]);

int avtp_clientinit(avtptc_data_t *avtptcd, int argc, char *argv[]);

int set_ccr(client_connect_request_t *ccr, avtptc_data_t *avtptcd);

void avtp_brater_period_print(avtptc_data_t *avtptcd, bool talker, int pkt_size);

void avtp_show_final_report(avtptc_data_t *avtptcd, bool talker, int pkt_size);

#endif
