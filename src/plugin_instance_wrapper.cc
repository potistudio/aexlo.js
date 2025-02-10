#include "plugin_instance_wrapper.hh"

Napi::Object PluginInstanceWrapper::Init (Napi::Env env, Napi::Object exports) {
	Napi::Function func = DefineClass (env, "PluginInstance", {
		InstanceMethod ("loadResources", &PluginInstanceWrapper::LoadResources),
		InstanceMethod ("about", &PluginInstanceWrapper::About),
		InstanceMethod ("setupGlobal", &PluginInstanceWrapper::SetupGlobal),
		InstanceMethod ("setupSequence", &PluginInstanceWrapper::SetupSequence),
		InstanceMethod ("setupParameters", &PluginInstanceWrapper::SetupParameters),
		InstanceMethod ("render", &PluginInstanceWrapper::Render),
		InstanceMethod ("smartPreRender", &PluginInstanceWrapper::SmartPreRender),
		InstanceMethod ("smartRender", &PluginInstanceWrapper::SmartRender),
		InstanceMethod ("getParameters", &PluginInstanceWrapper::GetParameters),
	});

	Napi::FunctionReference *constructor = new Napi::FunctionReference();
	*constructor = Napi::Persistent (func);

	env.SetInstanceData<Napi::FunctionReference>(constructor);
	exports.Set ("PluginInstance", func);

	return exports;
}

PluginInstanceWrapper::PluginInstanceWrapper (const Napi::CallbackInfo &info) : Napi::ObjectWrap<PluginInstanceWrapper> (info) {
	Napi::Env env = info.Env();

	/* VALIDATE ARGUMENTS */
	if (info.Length() != 1) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	if (!info[0].IsString()) {
		throw Napi::TypeError::New (env, "Wrong argument type with arg 0");
	}

	std::string path = info[0].As<Napi::String>();

	try {
		this->plugin = new PluginInstance (path);
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}
}

PluginInstanceWrapper::~PluginInstanceWrapper() {
	delete this->plugin;
}

Napi::Value PluginInstanceWrapper::LoadResources (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();
	std::string resources;

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	try {
		resources = this->plugin->ExtractResources();
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::String::New (env, resources);
}

Napi::Value PluginInstanceWrapper::About (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	/* VALIDATE ARGUMENTS */
	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = static_cast<int>(this->plugin->ExecuteAbout (this->in_data, this->out_data, this->params, this->layer));
	} catch (std::runtime_error& exception) {
		Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::SetupGlobal (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = static_cast<int>(this->plugin->ExecuteGlobalSetup (this->in_data, this->out_data, this->params, this->layer));
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::SetupSequence (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = static_cast<int>(this->plugin->ExecuteSequenceSetup (this->in_data, this->out_data, this->params, this->layer));
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::SetupParameters (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = static_cast<int>(this->plugin->ExecuteParamsSetup (this->in_data, this->out_data, this->params, this->layer));
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::Render (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	// Argument validation
	if (info.Length() < 2) {
		throw Napi::TypeError::New (env, "Too few arguments");
	}

	if (!info[0].IsObject() || !info[1].IsArray()) {
		throw Napi::TypeError::New (env, "Wrong argument type");
	}

	if (info.Length() > 2) {
		throw Napi::TypeError::New (env, "Too many arguments");
	}

	// Parse arguments
	Napi::Object in_data_arg = info[0].As<Napi::Object>();
	Napi::Array params_arg = info[1].As<Napi::Array>();

	// Parse parameters
	std::vector<AE_ParamDef> params;

	for (uint32_t i = 0; i < params_arg.Length(); i++) {
		Napi::Object param = params_arg.Get(i).As<Napi::Object>();

		if (!param.IsObject()) {
			throw Napi::TypeError::New (env, "Wrong argument type");
		}

		params.push_back (ParamParser::ParseParam(param, ParamManager::GetParamsByRef((AE_ProgressInfoPtr)this->plugin->entry)));
	}

	AE_ParamDef *params_raw = new AE_ParamDef[params.size()];

	for (int i = 0; i < params.size(); i++) {
		params_raw[i] = params[i];
	}

	const int WIDTH = 10;
	const int HEIGHT = 10;

	this->in_data->width = WIDTH;
	this->in_data->height = HEIGHT;

	// Invoke
	int error_code = 0;

	try {
		error_code = static_cast<int>(this->plugin->ExecuteRender(this->in_data, this->out_data, &params_raw, this->layer));
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	Napi::Array result = Napi::Array::New (env);

	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		AE_Pixel pixel = this->layer->data[i];

		result[i] = this->CreatePixelObject (env, pixel);
	}

	return result;
}

Napi::Value PluginInstanceWrapper::SmartPreRender (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;
	Napi::Object result = Napi::Object::New (env);
	AE_PreRenderOutput output;

	try {
		output = this->plugin->ExecuteSmartPreRender (this->in_data, this->out_data, this->params, this->layer);
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	Napi::Object result_rect = Napi::Object::New (env);
	result.Set ("rect", result_rect);

	result_rect.Set ("left",   output.result_rect.left);
	result_rect.Set ("top",    output.result_rect.top);
	result_rect.Set ("right",  output.result_rect.right);
	result_rect.Set ("bottom", output.result_rect.bottom);

	Napi::Object max_rect = Napi::Object::New (env);
	result.Set ("maxRect", max_rect);

	max_rect.Set ("left",   output.max_result_rect.left);
	max_rect.Set ("top",    output.max_result_rect.top);
	max_rect.Set ("right",  output.max_result_rect.right);
	max_rect.Set ("bottom", output.max_result_rect.bottom);

	result.Set ("solid",    output.solid);
	result.Set ("reserved", output.reserved);
	result.Set ("flags",    static_cast<short>(output.flags));

	return result;
}

Napi::Value PluginInstanceWrapper::SmartRender (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = static_cast<int>(this->plugin->ExecuteSmartRender(this->in_data, this->out_data, this->params, this->layer));
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::GetParameters (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	Napi::Array result = Napi::Array::New (env);
	std::vector<AE_ParamDef> params = ParamManager::GetParamsByRef ((AE_ProgressInfoPtr)this->plugin->entry);

	for (int i = 0; i < params.size(); i++) {
		Napi::Object param = Napi::Object::New (env);

		param.Set ("id", Napi::Number::New(env, params[i].uu.id));
		param.Set ("name", Napi::String::New(env, params[i].name));
		param.Set ("type", Napi::Number::New(env, static_cast<int>(params[i].param_type)));
		param.Set ("flagsUI", Napi::Number::New(env, static_cast<int>(params[i].ui_flags)));
		param.Set ("flags", Napi::Number::New(env, static_cast<int>(params[i].flags)));

		switch (params[i].param_type) {
			case AE_ParamType::LAYER:
				param.Set ("default", Napi::Number::New(env, params[i].u.ld.dephault));

				break;

			case AE_ParamType::SLIDER:
				// Valid
				param.Set ("validMin", Napi::Number::New(env, params[i].u.sd.valid_min));
				param.Set ("validMax", Napi::Number::New(env, params[i].u.sd.valid_max));

				// Slider
				param.Set ("sliderMin", Napi::Number::New(env, params[i].u.sd.slider_min));
				param.Set ("sliderMax", Napi::Number::New(env, params[i].u.sd.slider_max));

				// Value
				param.Set ("value", Napi::Number::New(env, params[i].u.sd.value));
				param.Set ("default", Napi::Number::New(env, params[i].u.sd.dephault));

				break;

			case AE_ParamType::CHECKBOX:
				param.Set ("value", Napi::Boolean::New(env, params[i].u.bd.value));
				param.Set ("default", Napi::Boolean::New(env, params[i].u.bd.dephault));

				break;

			case AE_ParamType::POINT:
				// Value
				param.Set ("valueX", Napi::Number::New(env, params[i].u.td.x_value));
				param.Set ("valueY", Napi::Number::New(env, params[i].u.td.y_value));

				// Default
				param.Set ("defaultX", Napi::Number::New(env, params[i].u.td.x_dephault));
				param.Set ("defaultY", Napi::Number::New(env, params[i].u.td.y_dephault));

				// Options
				param.Set ("restrict", Napi::Boolean::New(env, params[i].u.td.restrict_bounds));

				break;

			case AE_ParamType::COLOR:
				param.Set ("value", CreatePixelObject(env, params[i].u.cd.value));
				param.Set ("default", CreatePixelObject(env, params[i].u.cd.dephault));

				break;

			case AE_ParamType::FLOAT_SLIDER:
				// Valid
				param.Set ("validMin", Napi::Number::New(env, params[i].u.fs_d.valid_min));
				param.Set ("validMax", Napi::Number::New(env, params[i].u.fs_d.valid_max));

				// Slider
				param.Set ("sliderMin", Napi::Number::New(env, params[i].u.fs_d.slider_min));
				param.Set ("sliderMax", Napi::Number::New(env, params[i].u.fs_d.slider_max));

				// Value
				param.Set ("value", Napi::Number::New(env, params[i].u.fs_d.value));
				param.Set ("default", Napi::Number::New(env, params[i].u.fs_d.dephault));

				// Options
				param.Set ("precision", Napi::Number::New(env, params[i].u.fs_d.precision));
				param.Set ("curveTolerance", Napi::Number::New(env, params[i].u.fs_d.curve_tolerance));

				// Flags
				param.Set ("displayFlags", Napi::Number::New(env, params[i].u.fs_d.display_flags));
				param.Set ("sliderFlags", Napi::Number::New(env, params[i].u.fs_d.fs_flags));

				break;


			case AE_ParamType::GROUP_END:
				param.Delete ("name");

				break;
		}

		result.Set (i, param);
	}

	return result;
}

Napi::Object PluginInstanceWrapper::CreatePixelObject (Napi::Env env, AE_Pixel pixel) {
	Napi::Object result = Napi::Object::New (env);

	result.Set ("alpha", Napi::Number::New (env, pixel.alpha));
	result.Set ("red", Napi::Number::New (env, pixel.red));
	result.Set ("green", Napi::Number::New (env, pixel.green));
	result.Set ("blue", Napi::Number::New (env, pixel.blue));

	return result;
}
