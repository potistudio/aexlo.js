#ifndef AEXLO_PLUGIN_INSTANCE_H_
#define AEXLO_PLUGIN_INSTANCE_H_

#include <windows.h>
#include <string>
#include <math.h>

#include "headers/suites.hh"
#include "headers/entry_point.hh"
#include "headers/smart_fx.hh"
#include "interact_callbacks_factory.hh"
#include "utility_callbacks_factory.hh"

#include "logger/logger.hh"

class PluginInstance {
	public:
		PluginInstance (std::string path);
		~PluginInstance();

		std::string ExtractResources();
		int Execute (PF_Cmd cmd, PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer, void *);
		int ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		PF_PreRenderOutput ExecuteSmartPreRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);
		int ExecuteSmartRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer);

		// "HINSTANCE" is the handle to the loaded library
		HINSTANCE module;
		EntryPointFunc entry;
};

#endif
