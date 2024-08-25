#ifndef AEXLO_PLUGIN_INSTANCE_WRAPPER_H_
#define AEXLO_PLUGIN_INSTANCE_WRAPPER_H_

#include <iostream>

#include "./headers/basic.h"
#include "./headers/commands.h"
#include "./headers/input_data.h"
#include "./headers/output_data.h"
#include "./headers/param_data.h"
#include "./headers/layer_data.h"

#include "./global_functions.cc"
#include "./plugin_instance.cc"

class PluginInstanceWrapper : public Napi::ObjectWrap<PluginInstanceWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "PluginInstance", {
				InstanceMethod ("about", &PluginInstanceWrapper::About)
			});
			Napi::FunctionReference *constructor = new Napi::FunctionReference();
			*constructor = Napi::Persistent (func);

			env.SetInstanceData<Napi::FunctionReference>(constructor);
			exports.Set ("PluginInstance", func);

			return exports;
		}

		PluginInstanceWrapper (const Napi::CallbackInfo &info) : Napi::ObjectWrap<PluginInstanceWrapper> (info) {
			Napi::Env env = info.Env();

			/* VALIDATE ARGUMENTS */
			if (info.Length() != 1) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return;
			}

			if (!info[0].IsString()) {
				Napi::TypeError::New (env, "Wrong argument type with arg 0").ThrowAsJavaScriptException();
				return;
			}

			std::string path = info[0].As<Napi::String>();

			this->plugin = new PluginInstance (path);
		}

		~PluginInstanceWrapper() {
			delete this->plugin;
		}

	private:
		Napi::Value About (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			/* VALIDATE ARGUMENTS */
			if (info.Length() != 0) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			PF_InData* inData = new PF_InData();
			PF_OutData* outData = new PF_OutData();
			PF_ParamDef* params[1] = {};
			LayerParam* layer = new LayerParam();

			int error = 0;

			try {
				error = this->plugin->ExecuteAbout (inData, outData, params, layer);
			} catch (Napi::Error& error) {
				Napi::Error::New (env, error.Message()).ThrowAsJavaScriptException();
				return env.Null();
			}

			return Napi::Number::New (env, error);
		}

		PluginInstance* plugin;
};

#endif
