#pragma once

#include <windows.h>
#include <string>
#include <math.h>

#include "headers/entry_point.hh"
#include "headers/smart_fx.hh"
#include "./factories/interact_callbacks_factory.hh"
#include "./factories/utility_callbacks_factory.hh"

#include "./headers/suites/ansi_callback_suite.hh"
#include "./headers/suites/iterate_8_suite_2.hh"
#include "./headers/suites/world_transform_suite_1.hh"
#include "./headers/suites/effect_ui_suite_1.hh"
#include "./headers/suites/handle_suite_1.hh"

#include "./headers/suites/channel_suite_1.hh"
#include "./factories/channel_suite_1_factory.cc"

#include "logger/logger.hh"

class PluginInstance {
	public:
		PluginInstance (std::string path);
		~PluginInstance();

		std::string ExtractResources();
		int Execute (AE_Command cmd, PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer, void *);
		int ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteSequenceSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		PF_PreRenderOutput ExecuteSmartPreRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteSmartRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);

		// "HINSTANCE" is the handle to the loaded library
		HINSTANCE module;
		EntryPointFunc entry;
};
