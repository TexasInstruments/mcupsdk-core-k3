#ifndef DOLBY_EC3_SAMPLE_AUDIO_H_
#define DOLBY_EC3_SAMPLE_AUDIO_H_

#define EC3_SYNC_FRMSIZE                 (384)
#define AUDIO24BIT_AES3FRAMES_NEEDED     (EC3_SYNC_FRMSIZE * 2 / 6)
#define SMPTE_PREAMBLE_AES3FRAMES_NEEDED (2)
#define AES3_SIZE_OF_FRAME               (8)
#define AES3_CARRY_SMPTE_DATA_SIZE       (AUDIO24BIT_AES3FRAMES_NEEDED + SMPTE_PREAMBLE_AES3FRAMES_NEEDED)*AES3_SIZE_OF_FRAME

extern unsigned char payload_sample[];
extern int get_payload_sample_size(void);
#endif