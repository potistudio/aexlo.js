#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <math.h>
#include <chrono>

#include "./headers/common.hh"
#include "./headers/uncommon.hh"
#include "./headers/entry_point.hh"
#include "./headers/smart_fx.hh"
#include "./headers/basic_suite.hh"

#include "./factories/interact_callbacks_factory.hh"
#include "./factories/utility_callbacks_factory.hh"

#include "./factories/suite/ansi_callbacks_suite_factory.cc"
#include "./factories/suite/channel_suite_1_factory.cc"
#include "./factories/suite/effect_ui_suite_1_factory.cc"
#include "./factories/suite/handler_suite_1_factory.cc"
#include "./factories/suite/iterate_8_suite_2_factory.cc"
#include "./factories/suite/world_transform_suite_factory.cc"

#include "./logger/logger.hh"

class PluginInstance {
	public:
		PluginInstance (std::string path);
		~PluginInstance();

		std::string ExtractResources();
		AE_Error Execute (AE_Command cmd, AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer, void *);
		AE_Error ExecuteAbout (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);
		AE_Error ExecuteGlobalSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);
		AE_Error ExecuteSequenceSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);
		AE_Error ExecuteParamsSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);
		AE_Error ExecuteRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);
		AE_PreRenderOutput ExecuteSmartPreRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);
		AE_Error ExecuteSmartRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer);

		// "HINSTANCE" is the handle to the loaded library
		HINSTANCE module;
		EntryPointFunc entry;
};
