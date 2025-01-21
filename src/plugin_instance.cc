#include "plugin_instance.hh"

PluginInstance::PluginInstance (std::string path) {
	this->module = LoadLibraryA ((LPCSTR)path.c_str());
	if (this->module == NULL) {
		throw std::runtime_error ("Failed to load AEX");
	}

	// Cast the exported function address "EffectMain" or "EntryPointFunc" to a function pointer
	LOG_INFO ("Trying cast as \"EffectMain\"");
	this->entry = (EntryPointFunc)GetProcAddress (module, "EffectMain");

	if (this->entry == NULL) {
		LOG_WARNING ("Cannot cast entry point as \"EffectMain\"");
		LOG_INFO ("Trying \"EntryPointFunc\"");

		this->entry = (EntryPointFunc)GetProcAddress (module, "EntryPointFunc");

		if (this->entry == NULL) {
			LOG_WARNING ("Cannot cast entry point as \"EntryPointFunc\"");
			LOG_INFO ("Trying \"entryPointFunc\"");

			this->entry = (EntryPointFunc)GetProcAddress (module, "entryPointFunc");  //FIXME: Legacy Entry Point

			if (this->entry == NULL) {
				LOG_WARNING ("Cannot cast entry point as \"entryPointFunc\"");
				LOG_INFO ("Trying \"EffectMainExtra\"");

				this->entry = (EntryPointFunc)GetProcAddress (module, "EffectMainExtra");

				if (this->entry == NULL) {
					LOG_CRITICAL ("Failed to cast entry point");
					throw std::runtime_error ("Failed to cast entry point");
				}
			}
		}
	}

	LOG_INFO ("Cast complete");
}

PluginInstance::~PluginInstance () {
	if (this->module != NULL) {
		LOG_DEBUG ("Freeing library");
		FreeLibrary (this->module);
	}
}

std::string PluginInstance::ExtractResources() {
	LOG_INFO ("Extracting resources");
	auto resource = FindResourceA (this->module, MAKEINTRESOURCEA(16000), (CHAR*)TEXT("PiPL"));

	if (resource == NULL) {
		LOG_CRITICAL ("Failed to locate resources");
		throw std::runtime_error ("Failed to locate resources");
	}

	auto handle = LoadResource (this->module, resource);

	if (handle == NULL) {
		LOG_CRITICAL ("Failed to load resources");
		throw std::runtime_error ("Failed to load resources");
	}

	auto lock = LockResource (handle);

	if (lock == NULL) {
		LOG_CRITICAL ("Failed to lock resources");
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
		LOG_INFO ("AcquireSuite: \"" << name << ", ver." << version << "\"");

		if (strcmp(name, "PF ANSI Suite") == 0) {
			PF_ANSICallbacksSuite *ansi = new PF_ANSICallbacksSuite();

			ansi->sin = [](double x) -> double {
				double result = sin (x);
				LOG_INFO ("Called: ANSICallbacksSuite::sin (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->cos = [](double x) -> double {
				double result = cos (x);
				LOG_INFO ("Called: ANSICallbacksSuite::cos (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->tan = [](double x) -> double {
				double result = tan (x);
				LOG_INFO ("Called: ANSICallbacksSuite::tan (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->asin = [](double x) -> double {
				double result = asin (x);
				LOG_INFO ("Called: ANSICallbacksSuite::asin (" << x << ")" << "  ==> " << result);
				return 0;
			};

			ansi->acos = [](double x) -> double {
				double result = acos (x);
				LOG_INFO ("Called: ANSICallbacksSuite::acos (" << x << ")" << "  ==> " << result);
				return 0;
			};

			ansi->atan = [](double x) -> double {
				double result = atan (x);
				LOG_INFO ("Called: ANSICallbacksSuite::atan (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->atan2 = [](double y, double x) -> double {
				double result = atan2 (y, x);
				LOG_INFO ("Called: ANSICallbacksSuite::atan2 (" << y << ", " << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->log = [](double x) -> double {
				double result = log (x);
				LOG_INFO ("Called: ANSICallbacksSuite::log (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->log10 = [](double x) -> double {
				double result = log10 (x);
				LOG_INFO ("Called: ANSICallbacksSuite::log10 (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->ceil = [](double x) -> double {
				LOG_INFO ("ceil: " << x);
				return 0;
			};

			ansi->exp = [](double x) -> double {
				LOG_INFO ("exp: " << x);
				return 0;
			};

			ansi->fabs = [](double x) -> double {
				double result = abs (x);
				LOG_INFO ("Called: ANSICallbacksSuite::fabs (" << x << ")" << "  ==> " << result);
				return result;
			};

			ansi->floor = [](double x) -> double {
				LOG_INFO ("floor: " << x);
				return 0;
			};

			ansi->fmod = [](double x, double y) -> double {
				LOG_INFO ("fmod: " << x);
				return 0;
			};

			ansi->hypot = [](double x, double y) -> double {
				LOG_INFO ("hypot: " << x);
				return 0;
			};

			ansi->pow = [](double x, double y) -> double {
				double result = pow (x, y);

				LOG_INFO ("Called: ANSICallbacksSuite::pow (" << x << ", " << y << ")" << "  ==> " << result);

				return result;
			};

			ansi->sqrt = [](double x) -> double {
				LOG_INFO ("sqrt: " << x);
				return 0;
			};

			ansi->sprintf = [](char *buffer, const char *format, ...) -> int {
				va_list args;
				va_start (args, format);

				vsnprintf (buffer, 1024, format, args);

				LOG_INFO ("Called: ANSICallbacksSuite::sprintf (" << format << args << ")");
				LOG_INFO ("  ==> \"" << buffer << "\"");

				va_end (args);

				return 0;
			};

			ansi->strcpy = [](char *dest, const char *src) -> char * {
				strcpy (dest, src);
				LOG_INFO (dest);

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
					LOG_INFO ("A: " << ((int)outPixel.alpha) << ", R: " << ((int)outPixel.red) << ", G: " << ((int)outPixel.green) << ", B: " << ((int)outPixel.blue));
				}

				return 0;
			};

			*suite = i8s;
			return 0;
		} else if (strcmp(name, "PF World Transform Suite") == 0) {
			PF_WorldTransformSuite1 *wts = new PF_WorldTransformSuite1();

			wts->copy = [](ProgressInfoPtr effect_ref, LayerParam *src, LayerParam *dst, PF_Rect *src_r, PF_Rect *dst_r) -> int {
				LOG_INFO ("copy" << src);
				return 0;
			};

			*suite = wts;
			return 0;
		} else if (strcmp(name, "PF Effect UI Suite") == 0) {
			PF_EffectUISuite1 *eui = new PF_EffectUISuite1();

			eui->PF_SetOptionsButtonName = [](void *effect_ref, const char *name) -> int {
				LOG_INFO ("Set Options Button Name: " << name);
				return 0;
			};

			*suite = eui;

			return 0;
		} else if (strcmp(name, "PF Handle Suite") == 0) {
			PF_HandleSuite1 *hs = new PF_HandleSuite1();

			hs->HostNewHandle = [](uint64_t size) -> void * {
				LOG_INFO ("New Handle: " << size);
				PF_Handle *handle = new PF_Handle();
				return handle;
			};

			hs->HostLockHandle = [](void *handle) -> void * {
				LOG_INFO ("Lock Handle: " << handle);
				return new PF_Handle();
			};

			hs->HostUnlockHandle = [](void *handle) -> void {
				LOG_INFO ("Unlock Handle: " << handle);
			};

			hs->HostDisposeHandle = [](void *handle) -> void {
				LOG_INFO ("Dispose Handle: " << handle);
			};

			hs->HostGetHandleSize = [](void *handle) -> uint64_t {
				LOG_INFO ("Get Handle Size: " << handle);
				return 0;
			};

			hs->HostResizeHandle = [](uint64_t size, void **handle) -> int {
				LOG_INFO ("Resize Handle: " << size);
				return 0;
			};

			*suite = hs;

			return 0;
		}

		return -1; // Error
	};

	in_data->pica_basicP->ReleaseSuite = [](const char *name, int version) -> int {
		LOG_INFO ("ReleaseSuite: \"" << name << ", ver." << version << "\"");
		return 0;
	};

	in_data->pica_basicP->IsEqual = [](const char *token1, const char *token2) -> int {
		LOG_INFO ("Called ---- SPBasicSuite.IsEqual(" << token1 << ", " << token2 << ") ---- ");
		return 0;
	};

	in_data->pica_basicP->AllocateBlock = [](size_t size, void **block) -> int {
		LOG_INFO ("---- AllocateBlock: " << size);
		return 0;
	};

	in_data->pica_basicP->FreeBlock = [](void *block) -> int {
		LOG_INFO ("---- FreeBlock: " << block);
		return 0;
	};

	in_data->pica_basicP->ReallocateBlock = [](void *block, size_t newSize, void **newblock) -> int {
		LOG_INFO ("---- ReallocateBlock: " << block << ", " << newSize);
		return 0;
	};

	in_data->pica_basicP->Undefined = [](void) -> int {
		LOG_INFO ("---- Undefined");
		return 0;
	};

	in_data->utils = (new UtilityCallbackFactory())->Create();
	in_data->inter = (new InteractCallbackFactory())->Create();

	err = this->entry (cmd, in_data, outData, params, layer, extra);

	return err;
}

int PluginInstance::ExecuteAbout (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	LOG_INFO ("-------- begin About --------");

	const int CMD = PF_Cmd_ABOUT;
	int error = 0;

	try {
		error = this->Execute (CMD, in_data, out_data, params, layer, NULL);
		LOG_INFO ("  ==> Message: \"" << out_data->return_msg << "\"");
	} catch (std::exception &e) {
		LOG_CRITICAL (e.what());
		throw std::runtime_error (e.what());
	}

	LOG_INFO ("-------- end About --------");

	return error;
}

int PluginInstance::ExecuteGlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	LOG_INFO ("-------- begin Global Setup --------");

	int error = 0;
	const int CMD = PF_Cmd_GLOBAL_SETUP;

	LOG_DEBUG ("Execute Plugin with Code: " << CMD);
	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);
	LOG_DEBUG ("Execute Successful\n");

	LOG_INFO ("  ==> Version: " << out_data->my_version);
	LOG_INFO ("  ==> Flags: " << out_data->out_flags);
	LOG_INFO ("  ==> Flags2: " << out_data->out_flags2);

	LOG_INFO ("-------- end Global Setup --------");

	return error;
}

int PluginInstance::ExecuteParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	LOG_INFO ("-------- begin Parameters Setup --------");

	const int CMD = PF_Cmd_PARAMS_SETUP;
	int error = 0;

	/* Execute */
	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

	LOG_INFO ("  ==> Parameters: " << out_data->num_params);
	LOG_INFO ("-------- end Parameters Setup --------");

	return error;
}

int PluginInstance::ExecuteRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	LOG_INFO ("-------- begin Render --------");

	const int CMD = PF_Cmd_RENDER;
	int error = 0;

	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

	LOG_INFO ("-------- end Render --------");

	return error;
}

PF_PreRenderOutput PluginInstance::ExecuteSmartPreRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	LOG_INFO ("-------- begin Smart PreRender --------");

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
		LOG_INFO ("Called: delete_pre_render_data_func (" << pre_render_data << ")");
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
		LOG_INFO ("Called: PreRenderCallbacks.checkout_layer()");

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
		LOG_INFO ("Called: PreRenderCallbacks.GuidMixInPtr()");
		return 0;
	};

	error = this->Execute (CMD, in_data, out_data, params, layer, extra);

	LOG_INFO ("-------- end Smart Pre Render --------");
	return *extra->output;
}

int PluginInstance::ExecuteSmartRender (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], LayerParam *layer) {
	LOG_INFO ("-------- begin Smart Render --------");

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
		LOG_INFO ("Called: SmartRenderCallbacks.checkout_layer_pixels()");
		return 0;
	};

	extra->callbacks->checkin_layer_pixels = [](
		ProgressInfoPtr    effect_ref,
		int32_t            checkout_idL
	) -> int32_t {
		LOG_INFO ("Called: SmartRenderCallbacks.checkin_layer_pixels()");
		return 0;
	};

	extra->callbacks->checkout_output = [](
		ProgressInfoPtr    effect_ref,
		LayerParam         **output
	) -> int32_t {
		LOG_INFO ("Called: SmartRenderCallbacks.checkout_output()");
		return 0;
	};

	error = this->Execute (CMD, in_data, out_data, params, layer, extra);

	LOG_INFO ("-------- end Smart Render --------");
	return error;
}
