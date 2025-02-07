#include "plugin_instance.hh"

PluginInstance::PluginInstance (std::string path) {
	AddDllDirectory (PCWSTR("C:\\Program Files\\Adobe\\Adobe After Effects 2025\\Support Files"));
	this->module = LoadLibraryExA ((LPCSTR)path.c_str(), NULL, 0);

	if (this->module == NULL) {
		LOG_CRITICAL ("Failed to load library with code: " << GetLastError());
		throw std::exception ("Failed to load library");
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
					LOG_WARNING ("Cannot cast entry point as \"EffectMainExtra\"");
					LOG_INFO ("Trying \"FilterMain\"");

					this->entry = (EntryPointFunc)GetProcAddress (module, "FilterMain");

					if (this->entry == NULL) {
						LOG_CRITICAL ("Failed to cast entry point");
						throw std::runtime_error ("Failed to cast entry point");
					}
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

AE_Error PluginInstance::Execute (AE_Command cmd, AE_InData *in_data, AE_OutData *outData, AE_ParamDef *params[], AE_LayerParam *layer, void *extra) {
	AE_Error err = AE_Error::NONE;

	/** Initialize InData **/
	in_data->version = AE_SpecVersion();
	in_data->version.major = 13;
	in_data->version.minor = 28;

	in_data->serial_num = -2147483648;
	in_data->appl_id = 1180193859;

	in_data->what_cpu = 3;
	in_data->effect_ref = (AE_ProgressInfoPtr)this->entry;

	in_data->extent_hint = AE_LRect();
	in_data->extent_hint.left = 32760;
	in_data->extent_hint.top = -186403897;
	in_data->extent_hint.right = 32761;
	in_data->extent_hint.bottom = -417837312;

	in_data->pica_basicP = new SPBasicSuite();
	in_data->pica_basicP->AcquireSuite = [](const char *name, int version, const void **suite) -> AE_Error {
		LOG_INFO ("AcquireSuite: \"" << name << ", ver." << version << "\"");

		if (strcmp(name, "PF ANSI Suite") == 0) {
			AE_ANSICallbacksSuite *ansi = new AE_ANSICallbacksSuite();

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

			return AE_Error::NONE;
		} else if (strcmp(name, "PF Iterate8 Suite") == 0) {
			AE_Iterate8Suite2 *i8s = new AE_Iterate8Suite2();

			i8s->iterate = [](AE_InData *in_data, int progress_base, int progress_final, AE_LayerParam *src, const AE_Rect *area, void *controller, int(*pix_fn)(void* controller, int x, int y, AE_Pixel* in, AE_Pixel* out), AE_LayerParam *dts) -> int {
				AE_Pixel inPixel;
				AE_Pixel outPixel;

				for (int i = 0; i < 10; i++) {
					pix_fn (controller, i, 0, &inPixel, &outPixel);
					LOG_INFO ("A: " << ((int)outPixel.a) << ", R: " << ((int)outPixel.r) << ", G: " << ((int)outPixel.g) << ", B: " << ((int)outPixel.b));
				}

				return 0;
			};

			*suite = i8s;
			return AE_Error::NONE;
		} else if (strcmp(name, "PF World Transform Suite") == 0) {
			AE_WorldTransformSuite1 *wts = new AE_WorldTransformSuite1();

			wts->Copy = [] (
				AE_ProgressInfoPtr    effect_ref,
				AE_LayerParam         *src,
				AE_LayerParam         *dst,
				AE_Rect               *src_r,
				AE_Rect               *dst_r
			) -> AE_Error {
				AE_Error error = AE_Error::NONE;

				LOG_DEBUG ("Called: AE_WorldTransformSuite1::Copy (");
				LOG_DEBUG ("     from: 0x" << effect_ref);
				LOG_DEBUG ("      src: 0x" << src);
				LOG_DEBUG ("      dst: 0x" << dst);
				LOG_DEBUG ("    src_r: 0x" << src_r);
				LOG_DEBUG ("    dst_r: 0x" << dst_r);
				LOG_DEBUG (") -> AE_Error::" << NAMEOF_ENUM(error));

				return error;
			};

			*suite = wts;
			return AE_Error::NONE;
		} else if (strcmp(name, "PF Effect UI Suite") == 0) {
			AE_EffectUISuite1 *eui = new AE_EffectUISuite1();

			eui->SetOptionsButtonName = [] (
				AE_ProgressInfoPtr    effect_ref,
				const char            *name
			) -> AE_Error {
				AE_Error error = AE_Error::NONE;

				LOG_DEBUG ("Called: AE_EffectUISuite1::SetOptionsButtonName (");
				LOG_DEBUG ("    from: 0x" << effect_ref);
				LOG_DEBUG ("    name: \"" << *name << "\"");
				LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

				return error;
			};

			*suite = eui;

			return AE_Error::NONE;
		} else if (strcmp(name, "PF Handle Suite") == 0) {
			AE_HandleSuite1 *hs = new AE_HandleSuite1();

			hs->HostNewHandle = [](uint64_t size) -> void * {
				LOG_INFO ("New Handle: " << size);
				AE_Handle *handle = new AE_Handle();
				return handle;
			};

			hs->HostLockHandle = [](void *handle) -> void * {
				LOG_INFO ("Lock Handle: " << handle);
				return new AE_Handle();
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

			return AE_Error::NONE;
		} else if (strcmp(name, "PF AE Channel Suite") == 0) {
			LOG_DEBUG ("Acquire Suite Success as \"PF AE Channel Suite\"");
			LOG_DEBUG (" ==> AE_ChannelSuite1");

			*suite = (new ChannelSuite1Factory())->Create();
			return AE_Error::NONE;
		}

		return AE_Error::BAD_CALLBACK_PARAM;
	};

	in_data->pica_basicP->ReleaseSuite = [](const char *name, int version) -> AE_Error {
		LOG_INFO ("ReleaseSuite: \"" << name << ", ver." << version << "\"");
		return AE_Error::NONE;
	};

	in_data->pica_basicP->IsEqual = [](const char *token1, const char *token2) -> AE_Error {
		LOG_INFO ("Called ---- SPBasicSuite.IsEqual(" << token1 << ", " << token2 << ") ---- ");
		return AE_Error::NONE;
	};

	in_data->pica_basicP->AllocateBlock = [](size_t size, void **block) -> AE_Error {
		LOG_INFO ("---- AllocateBlock: " << size);
		return AE_Error::NONE;
	};

	in_data->pica_basicP->FreeBlock = [](void *block) -> AE_Error {
		LOG_INFO ("---- FreeBlock: " << block);
		return AE_Error::NONE;
	};

	in_data->pica_basicP->ReallocateBlock = [](void *block, size_t newSize, void **newblock) -> AE_Error {
		LOG_INFO ("---- ReallocateBlock: " << block << ", " << newSize);
		return AE_Error::NONE;
	};

	in_data->pica_basicP->Undefined = [](void) -> AE_Error {
		LOG_INFO ("---- Undefined");
		return AE_Error::NONE;
	};

	in_data->utils = (new UtilityCallbackFactory())->Create();
	in_data->inter = (new InteractCallbackFactory())->Create();

	err = this->entry (cmd, in_data, outData, params, layer, extra);

	return err;
}

AE_Error PluginInstance::ExecuteAbout (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin About --------");

	const AE_Command CMD = AE_Command::ABOUT;
	AE_Error error = AE_Error::NONE;

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

AE_Error PluginInstance::ExecuteGlobalSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin Global Setup --------");

	AE_Error error = AE_Error::NONE;
	const AE_Command CMD = AE_Command::GLOBAL_SETUP;

	LOG_DEBUG ("Execute Plugin with Code: " << NAMEOF_ENUM(CMD));
	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);
	LOG_DEBUG ("Execute Successful\n");

	LOG_INFO ("  ==> Version: " << out_data->my_version);
	LOG_INFO ("  ==> Flags: " << NAMEOF_ENUM_FLAG(out_data->out_flags));
	LOG_INFO ("  ==> Flags2: " << NAMEOF_ENUM_FLAG(out_data->out_flags2));

	LOG_INFO ("-------- end Global Setup --------");

	return error;
}

AE_Error PluginInstance::ExecuteSequenceSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin Global Setup --------");

	AE_Error error = AE_Error::NONE;
	const AE_Command CMD = AE_Command::SEQUENCE_SETUP;

	LOG_DEBUG ("Execute Plugin with Code: " << NAMEOF_ENUM(CMD));
	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);
	LOG_DEBUG ("Execute Successful\n");

	LOG_INFO ("  ==> Version: " << out_data->my_version);
	LOG_INFO ("  ==> Flags: " << NAMEOF_ENUM_FLAG(out_data->out_flags));
	LOG_INFO ("  ==> Flags2: " << NAMEOF_ENUM_FLAG(out_data->out_flags2));

	LOG_INFO ("-------- end Global Setup --------");

	return error;
}

AE_Error PluginInstance::ExecuteParamsSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin Parameters Setup --------");

	const AE_Command CMD = AE_Command::PARAMS_SETUP;
	AE_Error error = AE_Error::NONE;

	/* Execute */
	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

	LOG_INFO ("  ==> Parameters: " << out_data->num_params);
	LOG_INFO ("-------- end Parameters Setup --------");

	return error;
}

AE_Error PluginInstance::ExecuteRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin Render --------");

	const AE_Command CMD = AE_Command::RENDER;
	AE_Error error = AE_Error::NONE;

	error = this->Execute (CMD, in_data, out_data, params, layer, NULL);

	LOG_INFO ("-------- end Render --------");

	return error;
}

AE_PreRenderOutput PluginInstance::ExecuteSmartPreRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin Smart PreRender --------");

	const AE_Command CMD = AE_Command::SMART_PRE_RENDER;
	AE_Error error = AE_Error::NONE;

	AE_PreRenderExtra *extra = new AE_PreRenderExtra();
	extra->input = new AE_PreRenderInput();
	extra->output = new AE_PreRenderOutput();
	extra->callbacks = new AE_PreRenderCallbacks();

	// AE_PreRenderInput
	extra->input->output_request = AE_RenderRequest();
	extra->input->output_request.rect = AE_LRect();
	extra->input->output_request.rect.left = -192;
	extra->input->output_request.rect.top = -108;
	extra->input->output_request.rect.right = 2112;
	extra->input->output_request.rect.bottom = 1188;
	extra->input->output_request.channel_mask = AE_ChannelMask::ARGB;
	extra->input->bitdepth = 8;
	extra->input->device_index = 4294967295;

	// AE_PreRenderOutput
	extra->output->delete_pre_render_data_func = [](void *pre_render_data) -> void {
		LOG_INFO ("Called: delete_pre_render_data_func (" << pre_render_data << ")");
	};

	// AE_PreRenderCallbacks
	extra->callbacks->checkout_layer = [](
		AE_ProgressInfoPtr           effect_ref,
		int                   index,
		int                   checkout_idL,
		const AE_RenderRequest    *req,
		int                   what_time,
		int                   time_step,
		unsigned int                  time_scale,
		AE_CheckoutResult         *checkout_result
	) -> int {
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
		AE_ProgressInfoPtr    effect_ref,
		unsigned int           buf_sizeLu,
		const void         *buf
	) -> int {
		LOG_INFO ("Called: PreRenderCallbacks.GuidMixInPtr()");
		return 0;
	};

	error = this->Execute (CMD, in_data, out_data, params, layer, extra);

	LOG_INFO ("-------- end Smart Pre Render --------");
	return *extra->output;
}

AE_Error PluginInstance::ExecuteSmartRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	LOG_INFO ("-------- begin Smart Render --------");

	const AE_Command CMD = AE_Command::SMART_RENDER;
	AE_Error error = AE_Error::NONE;

	AE_SmartRenderExtra *extra = new AE_SmartRenderExtra();
	extra->input = new AE_SmartRenderInput();
	extra->callbacks = new AE_SmartRenderCallbacks();


	extra->input->bitdepth = 8;
	extra->input->device_index = 4294967295;

	extra->callbacks->checkout_layer_pixels = [](
		AE_ProgressInfoPtr    effect_ref,
		int            checkout_idL,
		AE_LayerParam         **pixels
	) -> int {
		LOG_INFO ("Called: SmartRenderCallbacks.checkout_layer_pixels()");
		return 0;
	};

	extra->callbacks->checkin_layer_pixels = [](
		AE_ProgressInfoPtr    effect_ref,
		int            checkout_idL
	) -> int {
		LOG_INFO ("Called: SmartRenderCallbacks.checkin_layer_pixels()");
		return 0;
	};

	extra->callbacks->checkout_output = [](
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         **output
	) -> int {
		LOG_INFO ("Called: SmartRenderCallbacks.checkout_output()");
		return 0;
	};

	error = this->Execute (CMD, in_data, out_data, params, layer, extra);

	LOG_INFO ("-------- end Smart Render --------");
	return error;
}
