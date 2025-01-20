#include "plugin_instance.hh"

PluginInstance::PluginInstance (std::string path) {
	this->module = LoadLibraryA ((LPCSTR)path.c_str());
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
				this->entry = (EntryPointFunc)GetProcAddress (module, "EffectMainExtra");
				if (this->entry == NULL) {
					throw std::runtime_error ("Failed to cast entry point");
				}
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
	auto resource = FindResourceA (this->module, MAKEINTRESOURCEA(16000), (CHAR*)TEXT("PiPL"));

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

int PluginInstance::Execute (PF_Cmd cmd, PF_InData *in_data, PF_OutData *outData, PF_ParamDef *params[], LayerParam *layer, void *extra) {
	int err = 0;

	/** Initialize InData **/
	in_data->version = PF_SpecVersion();
	in_data->version.major = 13;
	in_data->version.minor = 28;

	in_data->serial_num = -2147483648;
	in_data->appl_id = 1180193859;

	in_data->what_cpu = 3;

	in_data->extent_hint = PF_LRect();
	in_data->extent_hint.left = 32760;
	in_data->extent_hint.top = -186403897;
	in_data->extent_hint.right = 32761;
	in_data->extent_hint.bottom = -417837312;

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

			// ansi->pow = [](double x, double y) -> double {
			// 	std::cout << "pow: " << x << std::endl;
			// 	return 0;
			// };

			// ansi->sqrt = [](double x) -> double {
			// 	std::cout << "sqrt: " << x << std::endl;
			// 	return 0;
			// };

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
				PF_Handle *handle = new PF_Handle();
				return handle;
			};

			hs->HostLockHandle = [](void *handle) -> void * {
				std::cout << "Lock Handle: " << handle << std::endl;
				return new PF_Handle();
			};

			hs->HostUnlockHandle = [](void *handle) -> void {
				std::cout << "Unlock Handle: " << handle << std::endl;
			};

			hs->HostDisposeHandle = [](void *handle) -> void {
				std::cout << "Dispose Handle: " << handle << std::endl;
			};

			hs->HostGetHandleSize = [](void *handle) -> uint64_t {
				std::cout << "Get Handle Size: " << handle << std::endl;
				return 0;
			};

			hs->HostResizeHandle = [](uint64_t size, void **handle) -> int {
				std::cout << "Resize Handle: " << size << std::endl;
				return 0;
			};

			*suite = hs;

			return 0;
		}

		return -1; // Error
	};

	in_data->pica_basicP->ReleaseSuite = [](const char *name, int version) -> int {
		std::cout << "Called ---- SPBasicSuite.ReleaseSuite (" << name << ", ver." << version << std::endl;
		return 0;
	};

	in_data->pica_basicP->IsEqual = [](const char *token1, const char *token2) -> int {
		std::cout << "Called ---- SPBasicSuite.IsEqual(" << token1 << ", " << token2 << ") ---- " << std::endl;
		return 0;
	};

	in_data->pica_basicP->AllocateBlock = [](size_t size, void **block) -> int {
		std::cout << "---- AllocateBlock: " << size << std::endl;
		return 0;
	};

	in_data->pica_basicP->FreeBlock = [](void *block) -> int {
		std::cout << "---- FreeBlock: " << block << std::endl;
		return 0;
	};

	in_data->pica_basicP->ReallocateBlock = [](void *block, size_t newSize, void **newblock) -> int {
		std::cout << "---- ReallocateBlock: " << block << ", " << newSize << std::endl;
		return 0;
	};

	in_data->pica_basicP->Undefined = [](void) -> int {
		std::cout << "---- Undefined" << std::endl;
		return 0;
	};

	in_data->utils = (new UtilityCallbackFactory())->Create();
	in_data->inter = (new InteractCallbackFactory())->Create();

	err = this->entry (cmd, in_data, outData, params, layer, extra);

	return err;
}

int PluginInstance::ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	std::cout << "\n-------- begin About --------\n" << std::endl;

	const int CMD = PF_Cmd_ABOUT;
	int error = 0;

	try {
		error = this->Execute (CMD, in_data, out_data, params, layer, NULL);
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

	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

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
	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

	std::cout << out_data->num_params << std::endl;

	std::cout << "\n-------- end Parameters Setup --------\n" << std::endl;
	return error;
}

int PluginInstance::ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	std::cout << "\n-------- begin Render --------\n" << std::endl;

	const int CMD = PF_Cmd_RENDER;
	int error = 0;

	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

	std::cout << "\n-------- end Render --------\n" << std::endl;
	return error;
}

PF_PreRenderOutput PluginInstance::ExecuteSmartPreRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	std::cout << "\n-------- begin Smart Pre Render --------\n" << std::endl;

	const int CMD = PF_Cmd_SMART_PRE_RENDER;
	int error = 0;

	PF_PreRenderExtra *extra = new PF_PreRenderExtra();
	extra->input = new PF_PreRenderInput();
	extra->output = new PF_PreRenderOutput();
	extra->callbacks = new PF_PreRenderCallbacks();

	// PF_PreRenderInput
	extra->input->output_request = PF_RenderRequest();
	extra->input->output_request.rect = PF_LRect();
	extra->input->output_request.rect.left = -192;
	extra->input->output_request.rect.top = -108;
	extra->input->output_request.rect.right = 2112;
	extra->input->output_request.rect.bottom = 1188;
	extra->input->output_request.channel_mask = 15;
	extra->input->bitdepth = 8;
	extra->input->device_index = 4294967295;

	// PF_PreRenderOutput
	extra->output->delete_pre_render_data_func = [](void *pre_render_data) -> void {
		std::cout << "---- delete_pre_render_data_func: " << pre_render_data << std::endl;
	};

	// PF_PreRenderCallbacks
	extra->callbacks->checkout_layer = [](
		ProgressInfoPtr           effect_ref,
		int32_t                   index,
		int32_t                   checkout_idL,
		const PF_RenderRequest    *req,
		int32_t                   what_time,
		int32_t                   time_step,
		uint32_t                  time_scale,
		PF_CheckoutResult         *checkout_result
	) -> int32_t {
		std::cout << "Called ---- PreRenderCallbacks.checkout_layer()" << std::endl;
		checkout_result->result_rect.left = 0;
		checkout_result->result_rect.top = 0;
		checkout_result->result_rect.right = 1920;
		checkout_result->result_rect.bottom = 1080;

		checkout_result->max_result_rect.left = 0;
		checkout_result->max_result_rect.top = 0;
		checkout_result->max_result_rect.right = 1920;
		checkout_result->max_result_rect.bottom = 1080;

		checkout_result->par.num = 1;
		checkout_result->par.den = 1;
		checkout_result->solid = 1;

		checkout_result->ref_width = 1920;
		checkout_result->ref_height = 1080;

		return 0;
	};

	extra->callbacks->GuidMixInPtr = [](
		ProgressInfoPtr    effect_ref,
		uint32_t           buf_sizeLu,
		const void         *buf
	) -> int32_t {
		std::cout << "Called ---- PreRenderCallbacks.GuidMixInPtr()" << std::endl;
		return 0;
	};

	error = this->Execute (CMD, in_data, out_data, params, layer, extra);

	std::cout << "\n-------- end Smart Pre Render --------\n" << std::endl;
	return *extra->output;
}

int PluginInstance::ExecuteSmartRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	std::cout << "\n-------- begin Smart Render --------\n" << std::endl;

	const int CMD = PF_Cmd_SMART_RENDER;
	int error = 0;

	PF_SmartRenderExtra *extra = new PF_SmartRenderExtra();
	extra->input = new PF_SmartRenderInput();
	extra->callbacks = new PF_SmartRenderCallbacks();


	extra->input->bitdepth = 8;
	extra->input->device_index = 4294967295;

	extra->callbacks->checkout_layer_pixels = [](
		ProgressInfoPtr    effect_ref,
		int32_t            checkout_idL,
		LayerParam         **pixels
	) -> int32_t {
		std::cout << "Called ---- SmartRenderCallbacks.checkout_layer_pixels()" << std::endl;
		return 0;
	};

	extra->callbacks->checkin_layer_pixels = [](
		ProgressInfoPtr    effect_ref,
		int32_t            checkout_idL
	) -> int32_t {
		std::cout << "Called ---- SmartRenderCallbacks.checkin_layer_pixels()" << std::endl;
		return 0;
	};

	extra->callbacks->checkout_output = [](
		ProgressInfoPtr    effect_ref,
		LayerParam         **output
	) -> int32_t {
		std::cout << "Called ---- SmartRenderCallbacks.checkout_output()" << std::endl;
		return 0;
	};

	error = this->Execute (CMD, in_data, out_data, params, layer, extra);

	std::cout << "\n-------- end Smart Render --------\n" << std::endl;
	return error;
}
