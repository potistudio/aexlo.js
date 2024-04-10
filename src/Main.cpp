
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
		HINSTANCE module;
		EntryPointFunc entry;

		AEXPlugin (std::string path) {
			this->module = LoadLibrary (path.c_str());
			if (this->module == NULL) {
				throw std::runtime_error ("Failed to load AEX");
			}

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

			err = entry (cmd, inData, outData, params, layer, NULL);

			return err;
		}
};

SPErr AcquireSuite (const char *name, int32 version, const void **suite) {
	return 0;
}

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
			PF_Cmd cmd = PF_Cmd_ABOUT;
			PF_InData* inData = new PF_InData();
			PF_OutData* outData = new PF_OutData();
			PF_ParamDef* params = new PF_ParamDef();
			PF_LayerDef* layer = new PF_LayerDef();
			inData->pica_basicP = new SPBasicSuite();
			inData->pica_basicP->AcquireSuite = &AcquireSuite;

			//* Load Plugin
			AEXPlugin* plugin;
			try {
				plugin = new AEXPlugin (path);
			} catch (...) {
				Napi::Error::New (env, "Failed to load AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			//* Execute Plugin
			PF_Err err = plugin->Execute (cmd, inData, outData, params, layer);
			std::cout << err << std::endl; // Expect 0

			return env.Null();
		}
};

NODE_API_ADDON (Aexlo);
