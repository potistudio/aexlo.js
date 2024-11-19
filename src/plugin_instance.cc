#include "plugin_instance.hh"

PluginInstance::PluginInstance (std::string path) {
	this->module = LoadLibrary (path.c_str());
	if (this->module == NULL) {
		throw std::runtime_error ("Failed to load AEX");
	}

	// Cast the exported function address "EffectMain" or "EntryPointFunc" to a function pointer
	this->entry = (EntryPointFunc)GetProcAddress (module, "EffectMain");
	if (this->entry == NULL) {
		this->entry = (EntryPointFunc)GetProcAddress (module, "EntryPointFunc");
		if (this->entry == NULL) {
			this->entry = (EntryPointFunc)GetProcAddress (module, "entryPointFunc");  //FIXME: Legacy Entry Point
			if (this->entry == NULL) {
				throw std::runtime_error ("Failed to cast entry point");
			}
		}
	}
}

PluginInstance::~PluginInstance () {
	if (this->module != NULL) {
		FreeLibrary (this->module);
	}
}

std::string PluginInstance::ExtractResources() {
	auto resource = FindResourceA (this->module, MAKEINTRESOURCEA(16000), TEXT("PiPL"));

	if (resource == NULL) {
		throw std::runtime_error ("Failed to locate resources");
	}

	auto handle = LoadResource (this->module, resource);

	if (handle == NULL) {
		throw std::runtime_error ("Failed to load resources");
	}

	auto lock = LockResource (handle);

	if (lock == NULL) {
		throw std::runtime_error ("Failed to lock resources");
	}

	char* buffer = static_cast<char*>(lock);
	auto size = SizeofResource (this->module, resource);
	std::string result (buffer, size);
	return result;
}

int PluginInstance::Execute (PF_Cmd cmd, PF_InData *in_data, PF_OutData *outData, PF_ParamDef *params[], LayerParam *layer) {
	int err = 0;

	in_data->pica_basicP = new SPBasicSuite();
	in_data->pica_basicP->AcquireSuite = [](const char *name, int version, const void **suite) -> int {
		std::cout << "---- Acquiring Suite: " << name << ", ver." << version << std::endl;

		if (strcmp(name, "PF ANSI Suite") == 0) {
			PF_ANSICallbacksSuite *ansi = new PF_ANSICallbacksSuite();

			ansi->sin = [](double x) -> double {
				return sin (x);
			};

			ansi->cos = [](double x) -> double {
				return cos (x);
			};

			ansi->tan = [](double x) -> double {
				return tan (x);
			};

			ansi->asin = [](double x) -> double {
				std::cout << "asin: " << x << std::endl;
				return 0;
			};

			ansi->acos = [](double x) -> double {
				std::cout << "acos: " << x << std::endl;
				return 0;
			};

			ansi->atan = [](double x) -> double {
				std::cout << "atan: " << x << std::endl;
				return 0;
			};

			ansi->atan2 = [](double y, double x) -> double {
				std::cout << "atan2: " << x << std::endl;
				return 0;
			};

			ansi->log = [](double x) -> double {
				std::cout << "log10: " << x << std::endl;
				return 0;
			};

			ansi->log10 = [](double x) -> double {
				std::cout << "log10: " << x << std::endl;
				return 0;
			};

			ansi->ceil = [](double x) -> double {
				std::cout << "ceil: " << x << std::endl;
				return 0;
			};

			ansi->exp = [](double x) -> double {
				std::cout << "exp: " << x << std::endl;
				return 0;
			};

			ansi->fabs = [](double x) -> double {
				std::cout << "fabs: " << x << std::endl;
				return 0;
			};

			ansi->floor = [](double x) -> double {
				std::cout << "floor: " << x << std::endl;
				return 0;
			};

			ansi->fmod = [](double x, double y) -> double {
				std::cout << "fmod: " << x << std::endl;
				return 0;
			};

			ansi->hypot = [](double x, double y) -> double {
				std::cout << "hypot: " << x << std::endl;
				return 0;
			};

			ansi->pow = [](double x, double y) -> double {
				std::cout << "pow: " << x << std::endl;
				return 0;
			};

			ansi->sqrt = [](double x) -> double {
				std::cout << "sqrt: " << x << std::endl;
				return 0;
			};

			ansi->sprintf = [](char *buffer, const char *format, ...) -> int {
				va_list args;
				va_start (args, format);

				vsnprintf (buffer, 1024, format, args);
				std::cout << buffer << std::endl;

				va_end (args);
				return 0;
			};

			ansi->strcpy = [](char *dest, const char *src) -> char * {
				strcpy (dest, src);
				std::cout << dest << std::endl;

				return 0;
			};

			*suite = ansi;

			return 0;
		} else if (strcmp(name, "PF Iterate8 Suite") == 0) {
			PF_Iterate8Suite2 *i8s = new PF_Iterate8Suite2();

			i8s->iterate = [](PF_InData *in_data, int progress_base, int progress_final, LayerParam *src, const PF_Rect *area, void *controller, int(*pix_fn)(void* controller, int x, int y, Pixel* in, Pixel* out), LayerParam *dts) -> int {
				Pixel inPixel;
				Pixel outPixel;

				for (int i = 0; i < 10; i++) {
					pix_fn (controller, i, 0, &inPixel, &outPixel);
					std::cout << "A: " << ((int)outPixel.alpha) << ", R: " << ((int)outPixel.red) << ", G: " << ((int)outPixel.green) << ", B: " << ((int)outPixel.blue) << std::endl;
				}

				return 0;
			};

			*suite = i8s;
			return 0;
		} else if (strcmp(name, "PF World Transform Suite") == 0) {
			PF_WorldTransformSuite1 *wts = new PF_WorldTransformSuite1();

			wts->copy = [](ProgressInfoPtr effect_ref, LayerParam *src, LayerParam *dst, PF_Rect *src_r, PF_Rect *dst_r) -> int {
				std::cout << "copy" << src << std::endl;
				return 0;
			};

			*suite = wts;
			return 0;
		} else if (strcmp(name, "PF Effect UI Suite") == 0) {
			PF_EffectUISuite1 *eui = new PF_EffectUISuite1();

			eui->PF_SetOptionsButtonName = [](void *effect_ref, const char *name) -> int {
				std::cout << "Set Options Button Name: " << name << std::endl;
				return 0;
			};

			*suite = eui;

			return 0;
		} else if (strcmp(name, "PF Handle Suite") == 0) {
			PF_HandleSuite1 *hs = new PF_HandleSuite1();

			hs->HostNewHandle = [](uint64_t size) -> void * {
				std::cout << "New Handle: " << size << std::endl;
				return 0;
			};

			hs->HostLockHandle = [](void *handle) -> void * {
				std::cout << "Lock Handle: " << handle << std::endl;
				return 0;
			};

			*suite = hs;

			return 0;
		}

		return -1; // Error
	};

	in_data->pica_basicP->ReleaseSuite = [](const char *name, int version) -> int {
		std::cout << "---- Releasing Suite: " << name << ", ver." << version << std::endl;
		return 0;
	};

	in_data->utils = ((new UtilityCallbackFactory())->Create());

	in_data->inter = (new InteractCallbackFactory())->Create();

	err = this->entry (cmd, in_data, outData, params, layer, NULL);

	return err;
}

int PluginInstance::ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
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

int PluginInstance::ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
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

int PluginInstance::ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	std::cout << "\n-------- begin Parameters Setup --------\n" << std::endl;

	const int CMD = PF_Cmd_PARAMS_SETUP;
	int error = 0;

	/* Execute */
	error = this->Execute (CMD, in_data, out_data, params, layer);

	std::cout << out_data->num_params << std::endl;

	std::cout << "\n-------- end Parameters Setup --------\n" << std::endl;
	return error;
}

int PluginInstance::ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	std::cout << "\n-------- begin Render --------\n" << std::endl;

	const int CMD = PF_Cmd_RENDER;
	int error = 0;

	std::cout << "\n-------- begin Render --------\n" << std::endl;

	error = this->Execute (CMD, in_data, out_data, params, layer);

	std::cout << "\n-------- end Render --------\n" << std::endl;
	return error;
}
