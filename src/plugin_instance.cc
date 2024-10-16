#ifndef AEXLO_PLUGIN_INSTANCE_H_
#define AEXLO_PLUGIN_INSTANCE_H_

#include <windows.h>

#include "./global_functions.cc"
#include "./headers/entry_point.h"

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

		int Execute (PF_Cmd cmd, PF_InData *in_data, PF_OutData *outData, PF_ParamDef *params[], LayerParam *layer) {
			int err = 0;

			in_data->pica_basicP = new SPBasicSuite();
			in_data->pica_basicP->AcquireSuite = [](const char *name, int version, const void **suite) -> int {
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
			};

			in_data->pica_basicP->ReleaseSuite = [](const char *name, int version) -> int {
				std::cout << "---- Releasing Suite: " << name << ", ver." << version << std::endl;
				return 0;
			};

			in_data->utils = new _PF_UtilCallbacks();
			in_data->utils->ansi = PF_ANSICallbacks();

			in_data->utils->ansi.sprintf = [](char *buffer, const char *format, ...) -> int {
				va_list args;
				va_start (args, format);

				vsnprintf (buffer, 1024, format, args);
				std::cout << buffer << std::endl;

				va_end (args);
				return 0;
			};

			err = this->entry (cmd, in_data, outData, params, layer, NULL);

			return err;
		}

		int ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			std::cout << "\n-------- begin About --------\n" << std::endl;

			const int CMD = PF_Cmd_ABOUT;
			int error = 0;

			try {
				error = this->Execute (CMD, in_data, out_data, params, layer);
			} catch (std::exception &e) {
				throw std::runtime_error (e.what());
			}

			std::cout << "\n-------- end About --------\n" << std::endl;
			return error;
		}

		int ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			std::cout << "\n-------- begin Global Setup --------\n" << std::endl;

			int error = 0;
			const int CMD = PF_Cmd_GLOBAL_SETUP;

			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "Version: " << out_data->my_version << std::endl;
			std::cout << "Flags: " << out_data->out_flags << std::endl;
			std::cout << "Flags2: " << out_data->out_flags2 << std::endl;

			std::cout << "\n-------- end Global Setup --------\n" << std::endl;
			return error;
		}

		int ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			std::cout << "\n-------- begin Parameters Setup --------\n" << std::endl;

			const int CMD = PF_Cmd_PARAMS_SETUP;
			int error = 0;

			/* Arguments Setup */
			in_data->inter = PF_InteractCallbacks();
			in_data->inter.add_param = &addParam;

			/* Execute */
			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << out_data->num_params << std::endl;

			std::cout << "\n-------- end Parameters Setup --------\n" << std::endl;
			return error;
		}

		int ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
			std::cout << "\n-------- begin Render --------\n" << std::endl;

			const int CMD = PF_Cmd_RENDER;
			int error = 0;

			params[1] = new PF_ParamDef();
			params[1]->u.fs_d.value = 100;

			error = this->Execute (CMD, in_data, out_data, params, layer);

			std::cout << "\n-------- end Render --------\n" << std::endl;
			return error;
		}
};

#endif
