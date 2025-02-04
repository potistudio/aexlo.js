#pragma once

#include "./basic.hh"
#include "./common.hh"
#include "./param_data.hh"

struct AE_InteractCallbacks {
	int (*checkout_param) (ProgressInfoPtr, int, int, int, unsigned int, PF_ParamDef *);
	int (*checkin_param) (ProgressInfoPtr, PF_ParamDef *);
	int (*add_param) (ProgressInfoPtr, int, PF_ParamDefPtr);
	int (*abort) (ProgressInfoPtr);
	int (*progress) (ProgressInfoPtr, int, int);
	int (*register_ui) (ProgressInfoPtr, PF_CustomUIInfo *);
	int (*checkout_layer_audio) (ProgressInfoPtr, int, int, int, unsigned int, unsigned int, int, int, int, PF_LayerAudio *);
	int (*checkin_layer_audio) (ProgressInfoPtr, PF_LayerAudio);
	int (*get_audio_data) (ProgressInfoPtr, PF_LayerAudio, PF_SndSamplePtr *, int *, unsigned int *, int *, int *, int *);

	void    *reserved_str[3];
	void    *reserved[10];
};
