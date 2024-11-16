#ifndef AEXLO_PLUGIN_INSTANCE_WRAPPER_H_
#define AEXLO_PLUGIN_INSTANCE_WRAPPER_H_

#include <iostream>

#include "./headers/basic.h"
#include "./headers/commands.h"
#include "./headers/input_data.h"
#include "./headers/output_data.h"
#include "./headers/param_data.h"
#include "./headers/layer_data.h"

#include "plugin_instance.hh"

class PluginInstanceWrapper : public Napi::ObjectWrap<PluginInstanceWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "PluginInstance", {
				InstanceMethod ("loadResources", &PluginInstanceWrapper::LoadResources),
				InstanceMethod ("about", &PluginInstanceWrapper::About),
				InstanceMethod ("setupGlobal", &PluginInstanceWrapper::SetupGlobal),
				InstanceMethod ("setupParameters", &PluginInstanceWrapper::SetupParameters),
				InstanceMethod ("render", &PluginInstanceWrapper::Render),
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
		Napi::Value LoadResources (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			if (info.Length() != 0) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			std::string resources = this->plugin->ExtractResources ();
			return Napi::String::New (env, resources);
		}

		Napi::Value About (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			/* VALIDATE ARGUMENTS */
			if (info.Length() != 0) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			int error_code = 0;

			try {
				error_code = this->plugin->ExecuteAbout (this->in_data, this->out_data, this->params, this->layer);
			} catch (Napi::Error& exception) {
				Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
				return env.Null();
			}

			return Napi::Number::New (env, error_code);
		}

		Napi::Value SetupGlobal (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			if (info.Length() != 0) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			int error_code = 0;

			try {
				error_code = this->plugin->ExecuteGlobalSetup (this->in_data, this->out_data, this->params, this->layer);
			} catch (Napi::Error& exception) {
				Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
				return env.Null();
			}

			return Napi::Number::New (env, error_code);
		}

		Napi::Value SetupParameters (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			if (info.Length() != 0) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			int error_code = 0;

			try {
				error_code = this->plugin->ExecuteParamsSetup (this->in_data, this->out_data, this->params, this->layer);
			} catch (Napi::Error& exception) {
				Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
				return env.Null();
			}

			return Napi::Number::New (env, error_code);
		}

		Napi::Value Render (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			if (info.Length() != 0) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			int error_code = 0;

			try {
				error_code = this->plugin->ExecuteRender (this->in_data, this->out_data, this->params, this->layer);
			} catch (Napi::Error& exception) {
				Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
				return env.Null();
			}

			return Napi::Number::New (env, error_code);
		}

		PluginInstance* plugin;
		PF_InData* in_data = new PF_InData();
		PF_OutData* out_data = new PF_OutData();
		PF_ParamDef* params[1] = {};
		LayerParam* layer = new LayerParam();
};

#endif
