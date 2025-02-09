#pragma once
#pragma pack (push, AE, 8)

#include "./errors.hh"
#include "./param_data.hh"
#include "./custom_ui.hh"

struct AE_InteractCallbacks {
	AE_Error (*CheckoutParam) (
		AE_ProgressInfoPtr    effect_ref,
		int                   index,
		int                   what_time,
		int                   time_step,
		unsigned int          time_scale,
		AE_ParamDef           *param
	);  // 0-8*

	AE_Error (*CheckinParam) (
		AE_ProgressInfoPtr    effect_ref,
		AE_ParamDef           *param
	);  // 8-8*

	int (*add_param) (AE_ProgressInfoPtr, int, AE_ParamDefPtr);  // 16-8*
	int (*abort) (AE_ProgressInfoPtr);  // 24-8*
	int (*progress) (AE_ProgressInfoPtr, int, int);  // 32-8*
	int (*register_ui) (AE_ProgressInfoPtr, AE_CustomUIInfo *);  // 40-8*
	int (*checkout_layer_audio) (AE_ProgressInfoPtr, int, int, int, unsigned int, unsigned int, int, int, int, AE_LayerAudio *);  // 48-8*
	int (*checkin_layer_audio) (AE_ProgressInfoPtr, AE_LayerAudio);  // 56-8*
	int (*get_audio_data) (AE_ProgressInfoPtr, AE_LayerAudio, AE_SndSamplePtr *, int *, unsigned int *, int *, int *, int *);  // 64-8*

	void    *reserved_str[3];  // 72-24*
	void    *reserved[10];  // 96-80*
};  // 176bytes

#pragma pack (pop, AE)
