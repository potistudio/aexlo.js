#ifndef AEXLO_OUTPUT_DATA_H_
#define AEXLO_OUTPUT_DATA_H_

#include "./basic.h"

typedef struct {
	unsigned int         my_version;
	char           name[PF_MAX_EFFECT_NAME_LEN + 1];
	PF_Handle        global_data;
	int           num_params;
	PF_Handle        sequence_data;
	int           flat_sdata_size;
	PF_Handle        frame_data;
	int           width;
	int           height;
	PF_Point         origin;
	PF_OutFlags      out_flags;
	char           return_msg[PF_MAX_EFFECT_MSG_LEN + 1];
	int           start_sampL;
	int           dur_sampL;
	PF_SoundWorld    dest_snd;
	PF_OutFlags2     out_flags2;
} PF_OutData;

#endif
