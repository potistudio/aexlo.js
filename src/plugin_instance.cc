#include "plugin_instance.hh"

PluginInstance::PluginInstance (std::string path) {
	// AddDllDirectory (PCWSTR("C:\\Program Files\\Adobe\\Adobe After Effects 2025\\Support Files"));
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

		// TODO: Template
		if (strcmp(name, "PF ANSI Suite") == 0) {
			*suite = ANSICallbacksSuiteFactory::Create();
			return AE_Error::NONE;
		} else if (strcmp(name, "PF Iterate8 Suite") == 0) {
			*suite = Iterate8Suite2Factory::Create();
			return AE_Error::NONE;
		} else if (strcmp(name, "PF World Transform Suite") == 0) {
			*suite = WorldTransformSuiteFactory::Create();
			return AE_Error::NONE;
		} else if (strcmp(name, "PF Effect UI Suite") == 0) {
			*suite = EffectUISuite1Factory::Create();
			return AE_Error::NONE;
		} else if (strcmp(name, "PF Handle Suite") == 0) {
			*suite = HandlerSuite1Factory::Create();
			return AE_Error::NONE;
		} else if (strcmp(name, "PF AE Channel Suite") == 0) {
			*suite = ChannelSuite1Factory::Create();
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

	LOG_INFO ("-------- START CORE THREAD [" << NAMEOF_ENUM(cmd) << "] --------");
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	err = this->entry (cmd, in_data, outData, params, layer, extra);

	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	LOG_INFO ("-------- END CORE THREAD [" << NAMEOF_ENUM(cmd) << "] --------");
	LOG_INFO ("--> Time: " << elapsed_seconds.count() * 1000 << "ms");

	return err;
}

AE_Error PluginInstance::ExecuteAbout (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	AE_Error error = AE_Error::NONE;

	try {
		error = this->Execute (AE_Command::ABOUT, in_data, out_data, params, layer, NULL);
		LOG_INFO ("  ==> Message: \"" << out_data->return_msg << "\"");
	} catch (std::exception &e) {
		LOG_CRITICAL (e.what());
		throw std::runtime_error (e.what());
	}

	return error;
}

AE_Error PluginInstance::ExecuteGlobalSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	AE_Error error = AE_Error::NONE;

	error = this->Execute (AE_Command::GLOBAL_SETUP, in_data, out_data, params, layer, NULL);

	LOG_INFO ("  ==> Version: " << out_data->my_version);
	LOG_INFO ("  ==> Flags: " << NAMEOF_ENUM_FLAG(out_data->out_flags));
	LOG_INFO ("  ==> Flags2: " << NAMEOF_ENUM_FLAG(out_data->out_flags2));

	return error;
}

AE_Error PluginInstance::ExecuteSequenceSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	AE_Error error = AE_Error::NONE;

	error = this->Execute (AE_Command::SEQUENCE_SETUP, in_data, out_data, params, layer, NULL);

	LOG_INFO ("  ==> Version: " << out_data->my_version);
	LOG_INFO ("  ==> Flags: " << NAMEOF_ENUM_FLAG(out_data->out_flags));
	LOG_INFO ("  ==> Flags2: " << NAMEOF_ENUM_FLAG(out_data->out_flags2));

	return error;
}

AE_Error PluginInstance::ExecuteParamsSetup (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	AE_Error error = AE_Error::NONE;

	error = this->Execute (AE_Command::PARAMS_SETUP, in_data, out_data, params, layer, NULL);

	return error;
}

AE_Error PluginInstance::ExecuteRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
	AE_Error error = AE_Error::NONE;

	error = this->Execute (AE_Command::RENDER, in_data, out_data, params, layer, NULL);

	return error;
}

AE_PreRenderOutput PluginInstance::ExecuteSmartPreRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
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

	error = this->Execute (AE_Command::SMART_PRE_RENDER, in_data, out_data, params, layer, extra);

	return *extra->output;
}

AE_Error PluginInstance::ExecuteSmartRender (AE_InData *in_data, AE_OutData *out_data, AE_ParamDef *params[], AE_LayerParam *layer) {
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

	error = this->Execute (AE_Command::SMART_RENDER, in_data, out_data, params, layer, extra);

	return error;
}
