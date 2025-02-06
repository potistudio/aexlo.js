#pragma once

enum class AE_Command : int {
	ABOUT = 0,
	GLOBAL_SETUP,
	UNUSED_0,
	GLOBAL_SETDOWN,
	PARAMS_SETUP,
	SEQUENCE_SETUP,
	SEQUENCE_RESETUP,
	SEQUENCE_FLATTEN,
	SEQUENCE_SETDOWN,
	DO_DIALOG,
	FRAME_SETUP,
	RENDER,
	FRAME_SETDOWN,
	USER_CHANGED_PARAM,
	UPDATE_PARAMS_UI,
	EVENT,
	GET_EXTERNAL_DEPENDENCIES,
	COMPLETELY_GENERAL,
	QUERY_DYNAMIC_FLAGS,
	AUDIO_RENDER,
	AUDIO_SETUP,
	AUDIO_SETDOWN,
	ARBITRARY_CALLBACK,
	SMART_PRE_RENDER,
	SMART_RENDER,
	RESERVED1,
	RESERVED2,
	RESERVED3,
	GET_FLATTENED_SEQUENCE_DATA,
	TRANSLATE_PARAMS_TO_PREFS,
	RESERVED4,
	SMART_RENDER_GPU,
	GPU_DEVICE_SETUP,
	GPU_DEVICE_SETDOWN,
	NUM_CMDS,
};
