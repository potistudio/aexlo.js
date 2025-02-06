#pragma once
#pragma pack (push, AE, 8)

#include "./common.hh"
#include "./parameters/point.hh"
#include "./out_flags.hh"
#include "./audio.hh"

/**
 * @brief Effect Parameter Blocks
 */
struct AE_OutData {
	// This is the version number of your plug-in effect, not to be confused with the version of the plug-in specification.
	// Please set this at AE_Cmd_GLOBAL_SETUP.
	unsigned int     my_version;

	// This lets you override the name of the effect in the Time Layout and in the Effect Controls windows when the effect is applied.
	// The name from the PiPL resource is always used in the Effect menu.
	// This field is checked after AE_Cmd_SEQUENCE_SETUP.
	// You will almost always leave this field empty.
	char             name[32];

	// This is a Handle that you can allocate at AE_Cmd_GLOBAL_SETUP time.
	// It will be passed back to you verbatim in the input parameter block for use later on.
	// In AE_Cmd_GLOBAL_SETUP, the global_data field in the Input Block may be set to a flattened version of your global data,
	// in which case you should unflatten it, free the flat version, and set this field to the unflattened new global data.
	// It will be locked & unlocked for you automatically like sequence_data.
	AE_Handle        global_data;

	// The calling application will sanity check the num_params field vs the times add_param is called.
	// The implicit main layer parameter MUST be included in the parameter count.
	// Use the num_params value in the in_data as a starting value (it will include the implicit layer parameter).
	// Set this field when you get AE_Cmd_PARAMS_SETUP.
	int              num_params;

	AE_Handle        sequence_data;   // 64
	int              flat_sdata_size; // 68
	AE_Handle        frame_data;      // 80
	int              width;           // 84
	int              height;          // 88
	AE_PointParam    origin;          // 108
	AE_OutFlag       out_flags;       // 112
	char             return_msg[32];  // 144
	int              start_sampL;     // 148
	int              dur_sampL;       // 152
	AE_SoundWorld    dest_snd;        // 160
	AE_OutFlag2      out_flags2;      // 192
};  // 200bytes

#pragma pack (pop, AE)
