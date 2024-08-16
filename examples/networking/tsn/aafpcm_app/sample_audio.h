#ifndef AAF_SAMPLE_AUDIO_H_
#define AAF_SAMPLE_AUDIO_H_

#define TOTAL_BUFFERS           (20u)
#define RXBUFF_SIZE             (1472)
#define MEMPOOL_SIZE            (RXBUFF_SIZE*TOTAL_BUFFERS)

extern unsigned char payload_sample[];
extern int get_payload_sample_size(void);
#endif
