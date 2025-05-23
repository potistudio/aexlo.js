#pragma once

enum class AE_OutFlag : int {
	NONE                            = 0L,
	KEEP_RESOURCE_OPEN              = 1L << 0,
	WIDE_TIME_INPUT                 = 1L << 1,
	NON_PARAM_VARY                  = 1L << 2,
	RESERVED6                       = 1L << 3,
	SEQUENCE_DATA_NEEDS_FLATTENING  = 1L << 4,
	I_DO_DIALOG                     = 1L << 5,
	USE_OUTPUT_EXTENT               = 1L << 6,
	SEND_DO_DIALOG                  = 1L << 7,
	DISPLAY_ERROR_MESSAGE           = 1L << 8,
	I_EXPAND_BUFFER                 = 1L << 9,
	PIX_INDEPENDENT                 = 1L << 10,
	I_WRITE_INPUT_BUFFER            = 1L << 11,
	I_SHRINK_BUFFER                 = 1L << 12,
	WORKS_IN_PLACE                  = 1L << 13,
	RESERVED8                       = 1L << 14,
	CUSTOM_UI                       = 1L << 15,
	RESERVED7                       = 1L << 16,
	REFRESH_UI                      = 1L << 17,
	NOP_RENDER                      = 1L << 18,
	I_USE_SHUTTER_ANGLE             = 1L << 19,
	I_USE_AUDIO                     = 1L << 20,
	I_AM_OBSOLETE                   = 1L << 21,
	FORCE_RERENDER                  = 1L << 22,
	PiPL_OVERRIDES_OUTDATA_OUTFLAGS = 1L << 23,
	I_HAVE_EXTERNAL_DEPENDENCIES    = 1L << 24,
	DEEP_COLOR_AWARE                = 1L << 25,
	SEND_UPDATE_PARAMS_UI           = 1L << 26,
	AUDIO_FLOAT_ONLY                = 1L << 27,
	AUDIO_IIR                       = 1L << 28,
	I_SYNTHESIZE_AUDIO              = 1L << 29,
	AUDIO_EFFECT_TOO                = 1L << 30,
	AUDIO_EFFECT_ONLY               = 1L << 31
};

enum class AE_OutFlag2 : int {
	NONE                                       = 0L,
	SUPPORTS_QUERY_DYNAMIC_FLAGS               = 1L << 0,
	I_USE_3D_CAMERA                            = 1L << 1,
	I_USE_3D_LIGHTS                            = 1L << 2,
	PARAM_GROUP_START_COLLAPSED_FLAG           = 1L << 3,
	I_AM_THREADSAFE                            = 1L << 4,
	CAN_COMBINE_WITH_DESTINATION               = 1L << 5,
	DOESNT_NEED_EMPTY_PIXELS                   = 1L << 6,
	REVEALS_ZERO_ALPHA                         = 1L << 7,
	PRESERVES_FULLY_OPAQUE_PIXELS              = 1L << 8,
	SUPPORTS_SMART_RENDER                      = 1L << 10,
	RESERVED9                                  = 1L << 11,
	FLOAT_COLOR_AWARE                          = 1L << 12,
	I_USE_COLORSPACE_ENUMERATION               = 1L << 13,
	I_AM_DEPRECATED                            = 1L << 14,
	PPRO_DO_NOT_CLONE_SEQUENCE_DATA_FOR_RENDER = 1L << 15,
	RESERVED10                                 = 1L << 16,
	AUTOMATIC_WIDE_TIME_INPUT                  = 1L << 17,
	I_USE_TIMECODE                             = 1L << 18,
	DEPENDS_ON_UNREFERENCED_MASKS              = 1L << 19,
	OUTPUT_IS_WATERMARKED                      = 1L << 20,
	I_MIX_GUID_DEPENDENCIES                    = 1L << 21,
	AE13_5_THREADSAFE                          = 1L << 22,
	SUPPORTS_GET_FLATTENED_SEQUENCE_DATA       = 1L << 23,
	CUSTOM_UI_ASYNC_MANAGER                    = 1L << 24,
	SUPPORTS_GPU_RENDER_F32                    = 1L << 25,
	RESERVED12                                 = 1L << 26,
	SUPPORTS_THREADED_RENDERING                = 1L << 27,
	MUTABLE_RENDER_SEQUENCE_DATA_SLOWER        = 1L << 28
};
