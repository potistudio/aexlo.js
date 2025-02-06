#pragma once

#include <iostream>
#include <napi.h>

#include "./headers/common.hh"
#include "./headers/commands.hh"
#include "./headers/input_data.hh"
#include "./headers/output_data.hh"
#include "./headers/param_data.hh"
#include "./headers/layer_data.hh"
#include "./headers/smart_fx.hh"

#include "plugin_instance.hh"

class PluginInstanceWrapper : public Napi::ObjectWrap<PluginInstanceWrapper> {
	public:
		PluginInstanceWrapper (const Napi::CallbackInfo &info);
		~PluginInstanceWrapper();

		static Napi::Object Init (Napi::Env env, Napi::Object exports);

		Napi::Value LoadResources (const Napi::CallbackInfo &info);
		Napi::Value About (const Napi::CallbackInfo &info);
		Napi::Value SetupGlobal (const Napi::CallbackInfo &info);
		Napi::Value SetupSequence (const Napi::CallbackInfo &info);
		Napi::Value SetupParameters (const Napi::CallbackInfo &info);
		Napi::Value Render (const Napi::CallbackInfo &info);
		Napi::Value SmartPreRender (const Napi::CallbackInfo &info);
		Napi::Value SmartRender (const Napi::CallbackInfo &info);

	private:
		PluginInstance* plugin;
		AE_InData* in_data = new AE_InData();
		AE_OutData* out_data = new AE_OutData();
		AE_ParamDef* params[1] = {};
		AE_LayerParam* layer = new AE_LayerParam();
};
