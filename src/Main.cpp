
#include <napi.h>

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
			AEXLoaderWrapper::Init (env, exports);
		}
};

NODE_API_ADDON (Aexlo);
