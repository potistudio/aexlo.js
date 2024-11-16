#ifndef AEXLO_PLUGIN_INSTANCE_WRAPPER_H_
#define AEXLO_PLUGIN_INSTANCE_WRAPPER_H_

#include <iostream>
#include <napi.h>

#include "./headers/basic.h"
#include "./headers/commands.h"
#include "./headers/input_data.h"
#include "./headers/output_data.h"
#include "./headers/param_data.h"
#include "./headers/layer_data.h"

#include "plugin_instance.hh"

class PluginInstanceWrapper : public Napi::ObjectWrap<PluginInstanceWrapper> {
	public:
		PluginInstanceWrapper (const Napi::CallbackInfo &info);
		~PluginInstanceWrapper();

		static Napi::Object Init (Napi::Env env, Napi::Object exports);

		Napi::Value LoadResources (const Napi::CallbackInfo &info);
		Napi::Value About (const Napi::CallbackInfo &info);
		Napi::Value SetupGlobal (const Napi::CallbackInfo &info);
		Napi::Value SetupParameters (const Napi::CallbackInfo &info);
		Napi::Value Render (const Napi::CallbackInfo &info);

	private:
		PluginInstance* plugin;
		PF_InData* in_data = new PF_InData();
		PF_OutData* out_data = new PF_OutData();
		PF_ParamDef* params[1] = {};
		LayerParam* layer = new LayerParam();
};

#endif
