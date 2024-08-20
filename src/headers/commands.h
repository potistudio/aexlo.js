#ifndef AEXLO_COMMANDS_H_
#define AEXLO_COMMANDS_H_

typedef int PF_Cmd;

enum {
	PF_Cmd_ABOUT = 0,
	PF_Cmd_GLOBAL_SETUP,
	PF_Cmd_UNUSED_0,
	PF_Cmd_GLOBAL_SETDOWN,
	PF_Cmd_PARAMS_SETUP,
	PF_Cmd_SEQUENCE_SETUP,
	PF_Cmd_SEQUENCE_RESETUP,
	PF_Cmd_SEQUENCE_FLATTEN,
	PF_Cmd_SEQUENCE_SETDOWN,
	PF_Cmd_DO_DIALOG,
	PF_Cmd_FRAME_SETUP,
	PF_Cmd_RENDER,
	PF_Cmd_FRAME_SETDOWN,
	PF_Cmd_USER_CHANGED_PARAM,
	PF_Cmd_UPDATE_PARAMS_UI,
	PF_Cmd_EVENT,
	PF_Cmd_GET_EXTERNAL_DEPENDENCIES,
	PF_Cmd_COMPLETELY_GENERAL,
	PF_Cmd_QUERY_DYNAMIC_FLAGS,
	PF_Cmd_AUDIO_RENDER,
	PF_Cmd_AUDIO_SETUP,
	PF_Cmd_AUDIO_SETDOWN,
	PF_Cmd_ARBITRARY_CALLBACK,
	PF_Cmd_SMART_PRE_RENDER,
	PF_Cmd_SMART_RENDER,
	PF_Cmd_RESERVED1,
	PF_Cmd_RESERVED2,
	PF_Cmd_RESERVED3,
	PF_Cmd_GET_FLATTENED_SEQUENCE_DATA,
	PF_Cmd_TRANSLATE_PARAMS_TO_PREFS,
	PF_Cmd_RESERVED4,
	PF_Cmd_SMART_RENDER_GPU,
	PF_Cmd_GPU_DEVICE_SETUP,
	PF_Cmd_GPU_DEVICE_SETDOWN,
	PF_Cmd_NUM_CMDS,
};

#endif
