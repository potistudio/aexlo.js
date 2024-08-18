
#include <napi.h>
#include <iostream>
#include <windows.h>
#include "AEXDef.h"

class AEXLoaderWrapper : public Napi::ObjectWrap<AEXLoaderWrapper> {
	public:
		static Napi::Object Init (Napi::Env env, Napi::Object exports) {
			Napi::Function func = DefineClass (env, "AEXLoader", {
				InstanceMethod ("load", &AEXLoaderWrapper::Load)
			});
			Napi::FunctionReference *constructor = new Napi::FunctionReference();
			*constructor = Napi::Persistent (func);

			env.SetInstanceData<Napi::FunctionReference>(constructor);
			exports.Set ("AEXLoader", func);

			return exports;
		}

		AEXLoaderWrapper (const Napi::CallbackInfo &info) : Napi::ObjectWrap<AEXLoaderWrapper> (info) {
			// Constructor
			Napi::Env env = info.Env();
		}

	private:
		Napi::Value Load (const Napi::CallbackInfo &info) {
			Napi::Env env = info.Env();
			return env.Null();
		}
};

class AEXPlugin {
	public:
		// "HINSTANCE" is the handle to the loaded library
		HINSTANCE module;
		EntryPointFunc entry;

		AEXPlugin (std::string path) {
			this->module = LoadLibrary (path.c_str());
			if (this->module == NULL) {
				throw std::runtime_error ("Failed to load AEX");
			}

			// Cast the exported function address "EffectMain" or "EntryPointFunc" to a function pointer
			this->entry = (EntryPointFunc)GetProcAddress (module, "EffectMain");
			if (this->entry == NULL) {
				this->entry = (EntryPointFunc)GetProcAddress (module, "EntryPointFunc");
				if (this->entry == NULL)
					throw std::runtime_error ("Failed to load AEX");
			}
		}

		~AEXPlugin () {
			if (this->module != NULL) {
				FreeLibrary (this->module);
			}
		}

		PF_Err Execute (PF_Cmd cmd, PF_InData *inData, PF_OutData *outData, PF_ParamDef *params, PF_LayerDef *layer) {
			PF_Err err = PF_Err_NONE;

			err = this->entry (cmd, inData, outData, params, layer, NULL);

			return err;
		}

		PF_Err ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params, PF_LayerDef *layer) {
			PF_Err error = PF_Err_NONE;

			const int CMD = PF_Cmd_ABOUT;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			return error;
		}

		PF_Err ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params, PF_LayerDef *layer) {
			PF_Err error = PF_Err_NONE;

			const int CMD = PF_Cmd_GLOBAL_SETUP;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "\n-------- begin Global Setup --------\n" << std::endl;

			std::cout << "Version: " << out_data->my_version << std::endl;
			std::cout << "Flags: " << out_data->out_flags << std::endl;
			std::cout << "Flags2: " << out_data->out_flags2 << std::endl;

			std::cout << "\n-------- end Global Setup --------\n" << std::endl;

			return error;
		}
};

SPErr AcquireSuite (const char *name, int32 version, const void **suite) {
	return 0;
}

int sprintf_m (A_char *buffer, const A_char *format, ...) {
	va_list args;
	va_start (args, format);

	std::cout << "\n-------- begin About --------\n" << std::endl;

	vsnprintf (buffer, 1024, format, args); // format
	std::cout << buffer << std::endl; // content

	std::cout << "\n-------- end About --------\n" << std::endl;

	va_end (args);
	return 0;
};

// Main
class Aexlo : public Napi::Addon<Aexlo> {
	public:
		Aexlo (Napi::Env env, Napi::Object exports) {
			DefineAddon (exports, {
				InstanceMethod ("loadAEX", &Aexlo::LoadAEX)
			});

			AEXLoaderWrapper::Init (env, exports);
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
			PF_ParamDef* params = new PF_ParamDef();
			PF_LayerDef* layer = new PF_LayerDef();

			inData->utils = new _PF_UtilCallbacks();
			inData->utils->ansi = PF_ANSICallbacks();
			inData->utils->ansi.sprintf = &sprintf_m;
			// inData->pica_basicP = new SPBasicSuite();
			// inData->pica_basicP->AcquireSuite = &AcquireSuite;

			//* Load Plugin
			AEXPlugin* plugin;
			try {
				plugin = new AEXPlugin (path);
			} catch (...) {
				Napi::Error::New (env, "Failed to load AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			//* Execute Plugin (test)
			try {
				PF_Err err = plugin->ExecuteGlobalSetup (inData, outData, params, layer);
				std::cout << err << std::endl; // Expect 0
			} catch (...) {
				Napi::Error::New (env, "Failed to execute AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			return env.Null();
		}
};

NODE_API_ADDON (Aexlo);
