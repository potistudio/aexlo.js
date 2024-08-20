
#include <napi.h>
#include <iostream>
#include <windows.h>

#include "./headers/errors.h"
#include "./headers/commands.h"
#include "./headers/basic.h"
#include "./headers/suites.h"
#include "./headers/entry_point.h"

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

int addParam (ProgressInfoPtr effect_ref, int index, PF_ParamDefPtr def) {
	std::cout << "Param Type: " << def->param_type << std::endl;
	std::cout << "Param Name: " << def->name << std::endl;
	std::cout << "Valid Min: " << def->u.fs_d.valid_min << std::endl;
	std::cout << "Slider Min: " << def->u.fs_d.slider_min << std::endl;
	std::cout << "Valid Max: " << def->u.fs_d.valid_max << std::endl;
	std::cout << "Slider Max: " << def->u.fs_d.slider_max << std::endl;
	std::cout << "Value: " << def->u.fs_d.value << std::endl;
	std::cout << "Default: " << def->u.fs_d.dephault << std::endl;
	std::cout << "Precision: " << def->u.fs_d.precision << std::endl;
	std::cout << "Display Flags: " << def->u.fs_d.display_flags << std::endl;
	std::cout << "Flags: " << def->u.fs_d.fs_flags << std::endl;
	std::cout << "Curve Tolerance: " << def->u.fs_d.curve_tolerance << std::endl;
	std::cout << "ID: " << def->uu.id << std::endl;
	return 0;
}

typedef struct NoiseInfo{
	PF_FpLong	valF;
} NoiseInfo, *NoiseInfoP, **NoiseInfoH;

int iterate (PF_InData *in_data, int progress_base, int progress_final, LayerParam *src, const PF_Rect *area, void *controller, int(*pix_fn)(void* controller, int x, int y, Pixel* in, Pixel* out), LayerParam *dts) {
	Pixel inPixel;
	Pixel outPixel;

	for (int i = 0; i < 10; i++) {
		pix_fn (controller, i, 0, &inPixel, &outPixel);
		std::cout << "A: " << ((int)outPixel.alpha) << ", R: " << ((int)outPixel.red) << ", G: " << ((int)outPixel.green) << ", B: " << ((int)outPixel.blue) << std::endl;
	}

	return 0;
}

int copy (ProgressInfoPtr effect_ref, LayerParam *src, LayerParam *dst, PF_Rect *src_r, PF_Rect *dst_r) {
	std::cout << "copy" << src << std::endl;
	return 0;
}

int acquireSuite (const char *name, int version, const void **suite) {
	std::cout << "---- Acquiring Suite: " << name << ", ver." << version << std::endl;

	if (strcmp(name, "PF Iterate8 Suite") == 0) {
		PF_Iterate8Suite2 *i8s = new PF_Iterate8Suite2();
		i8s->iterate = &iterate;
		*suite = i8s;

		return 0;
	} else if (strcmp(name, "PF World Transform Suite") == 0) {
		PF_WorldTransformSuite1 *wts = new PF_WorldTransformSuite1();
		wts->copy = &copy;
		*suite = wts;

		return 0;
	}

	return -1; // Error
}

int releaseSuite (const char *name, int version) {
	std::cout << "---- Releasing Suite: " << name << ", ver." << version << std::endl;
	return 0;
}

class PluginInstance {
	public:
		// "HINSTANCE" is the handle to the loaded library
		HINSTANCE module;
		EntryPointFunc entry;

		PluginInstance (std::string path) {
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

		~PluginInstance () {
			if (this->module != NULL) {
				FreeLibrary (this->module);
			}
		}

		int Execute (PF_Cmd cmd, PF_InData *inData, PF_OutData *outData, PF_ParamDef *params[], LayerParam *layer) {
			int err = 0;

			err = this->entry (cmd, inData, outData, params, layer, NULL);

			return err;
		}

		int ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {

			std::cout << "\n-------- begin About --------\n" << std::endl;

			const int CMD = PF_Cmd_ABOUT;
			int error = 0;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "\n-------- end About --------\n" << std::endl;

			return error;
		}

		int ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			int error = 0;

			const int CMD = PF_Cmd_GLOBAL_SETUP;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "\n-------- begin Global Setup --------\n" << std::endl;

			std::cout << "Version: " << out_data->my_version << std::endl;
			std::cout << "Flags: " << out_data->out_flags << std::endl;
			std::cout << "Flags2: " << out_data->out_flags2 << std::endl;

			std::cout << "\n-------- end Global Setup --------\n" << std::endl;

			return error;
		}

		int ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			const int CMD = PF_Cmd_PARAMS_SETUP;
			int error = 0;

			/* Arguments Setup */
			in_data->inter = PF_InteractCallbacks();
			in_data->inter.add_param = &addParam;

			/* Execute */
			std::cout << "\n-------- begin Parameters Setup --------\n" << std::endl;

			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << out_data->num_params << std::endl;

			std::cout << "\n-------- end Parameters Setup --------\n" << std::endl;

			return error;
		}

		int ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			const int CMD = PF_Cmd_RENDER;
			int error = 0;

			std::cout << "\n-------- begin Render --------\n" << std::endl;

			in_data->pica_basicP = new SPBasicSuite();
			in_data->pica_basicP->AcquireSuite = &acquireSuite;
			in_data->pica_basicP->ReleaseSuite = &releaseSuite;

			params[1] = new PF_ParamDef();
			params[1]->u.fs_d.value = 100;
			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "\n-------- end Render --------\n" << std::endl;

			return error;
		}
};

int sprintf_m (char *buffer, const char *format, ...) {
	va_list args;
	va_start (args, format);

	vsnprintf (buffer, 1024, format, args); // format
	std::cout << buffer << std::endl; // content

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

				err = plugin->ExecuteGlobalSetup (inData, outData, params, layer);
				err = plugin->ExecuteParamsSetup (inData, outData, params, layer);

				err = plugin->Execute (PF_Cmd_FRAME_SETUP, inData, outData, params, layer);
				err = plugin->ExecuteRender (inData, outData, params, layer);
				err = plugin->Execute (PF_Cmd_FRAME_SETDOWN, inData, outData, params, layer);

				std::cout << err << std::endl; // Expect 0
			} catch (...) {
				Napi::Error::New (env, "Failed to execute AEX").ThrowAsJavaScriptException();
				return env.Null();
			}

			return env.Null();
		}
};

NODE_API_ADDON (Aexlo);
