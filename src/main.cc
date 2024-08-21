
#include <napi.h>
#include <iostream>
#include <windows.h>

#include "./headers/errors.h"
#include "./headers/commands.h"
#include "./headers/basic.h"
#include "./headers/suites.h"
#include "./headers/entry_point.h"

#include "./plugin_instance.cc"
#include "./plugin_instance_wrapper.cc"

// Main
class Aexlo : public Napi::Addon<Aexlo> {
	public:
		Aexlo (Napi::Env env, Napi::Object exports) {
			DefineAddon (exports, {
				InstanceMethod ("loadAEX", &Aexlo::LoadAEX)
			});

			PluginInstanceWrapper::Init (env, exports);
		}

	private:
		Napi::Value LoadAEX (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();

			//* Validate Arguments
			if (info.Length() != 1) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			if (!info[0].IsString()) {
				Napi::TypeError::New (env, "Wrong argument type").ThrowAsJavaScriptException();
				return env.Null();
			}

			std::string path = info[0].As<Napi::String>();

			//* Initialize Data
			PF_Cmd cmd = PF_Cmd_GLOBAL_SETUP;
			PF_InData* inData = new PF_InData();
			PF_OutData* outData = new PF_OutData();
			PF_ParamDef* params[1] = {};
			LayerParam* layer = new LayerParam();

			inData->utils = new _PF_UtilCallbacks();
			inData->utils->ansi = PF_ANSICallbacks();
			inData->utils->ansi.sprintf = &sprintf_m;

			//* Load Plugin
			PluginInstance* plugin;
			try {
				plugin = new PluginInstance (path);
			} catch (...) {
				Napi::Error::New (env, "Failed to load AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			//* Execute Plugin (test)
			try {
				int err = 0;

				err = plugin->ExecuteAbout (inData, outData, params, layer);
				// err = plugin->ExecuteGlobalSetup (inData, outData, params, layer);
				// err = plugin->ExecuteParamsSetup (inData, outData, params, layer);

				// err = plugin->Execute (PF_Cmd_FRAME_SETUP, inData, outData, params, layer);
				// err = plugin->ExecuteRender (inData, outData, params, layer);
				// err = plugin->Execute (PF_Cmd_FRAME_SETDOWN, inData, outData, params, layer);

				std::cout << err << std::endl; // Expect 0
			} catch (...) {
				Napi::Error::New (env, "Failed to execute AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			return env.Null();
		}
};

NODE_API_ADDON (Aexlo);
