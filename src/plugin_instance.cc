#ifndef AEXLO_PLUGIN_INSTANCE_H_
#define AEXLO_PLUGIN_INSTANCE_H_

#include "./global_functions.cc"

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

			in_data->pica_basicP = new SPBasicSuite();
			in_data->pica_basicP->AcquireSuite = &acquireSuite;
			in_data->pica_basicP->ReleaseSuite = &releaseSuite;

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

#endif
