
#include <napi.h>
#include <iostream>
#include <windows.h>
#include "AEXDef.cpp"

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

			if (info.Length() != 1) {
				Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
				return env.Null();
			}

			if (!info[0].IsString()) {
				Napi::TypeError::New (env, "Wrong argument type").ThrowAsJavaScriptException();
				return env.Null();
			}

			std::string path = info[0].As<Napi::String>();

			HINSTANCE module = LoadLibrary ("D:\\Library\\After Effects Plugins & Scripts\\F's Plugins\\F's Max.aex");
			if (module == NULL) {
				Napi::Error::New (env, "Failed to load AEX").ThrowAsJavaScriptException();
				return env.Null();
			}
			EntryPointFunc entry = (EntryPointFunc)GetProcAddress (module, "EntryPointFunc");
			if (entry == NULL) {
				Napi::Error::New (env, "Failed to load AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			PF_Cmd cmd = PF_Cmd_ABOUT;
			PF_InData* inData = new PF_InData();
			PF_OutData* outData = new PF_OutData();
			PF_ParamDef* params = new PF_ParamDef();
			PF_LayerDef* layer = new PF_LayerDef();

			PF_Err err = entry (cmd, inData, outData, params, layer, NULL);
			std::cout << err << std::endl;

			return env.Null();
		}
};

NODE_API_ADDON (Aexlo);
