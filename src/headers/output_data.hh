#pragma once

#include "./basic.hh"
#include "./out_flags.hh"
#include "./parameters/point.hh"

struct AE_OutData {
	unsigned int         my_version;
	char           name[PF_MAX_EFFECT_NAME_LEN + 1];
	PF_Handle        global_data;
	int           num_params;
	PF_Handle        sequence_data;
	int           flat_sdata_size;
	PF_Handle        frame_data;
	int           width;
	int           height;
	AE_PointParam         origin;
	AE_OutFlag      out_flags;
	char           return_msg[PF_MAX_EFFECT_MSG_LEN + 1];
	int           start_sampL;
	int           dur_sampL;
	PF_SoundWorld    dest_snd;
	AE_OutFlag2     out_flags2;
};
