#include "plugin_instance_wrapper.hh"

Napi::Object PluginInstanceWrapper::Init (Napi::Env env, Napi::Object exports) {
	Napi::Function func = DefineClass (env, "PluginInstance", {
		InstanceMethod ("loadResources", &PluginInstanceWrapper::LoadResources),
		InstanceMethod ("about", &PluginInstanceWrapper::About),
		InstanceMethod ("setupGlobal", &PluginInstanceWrapper::SetupGlobal),
		InstanceMethod ("setupParameters", &PluginInstanceWrapper::SetupParameters),
		InstanceMethod ("render", &PluginInstanceWrapper::Render),
		InstanceMethod ("smartPreRender", &PluginInstanceWrapper::SmartPreRender),
		InstanceMethod ("smartRender", &PluginInstanceWrapper::SmartRender),
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
		error_code = this->plugin->ExecuteAbout (this->in_data, this->out_data, this->params, this->layer);
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
		error_code = this->plugin->ExecuteGlobalSetup (this->in_data, this->out_data, this->params, this->layer);
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
		error_code = this->plugin->ExecuteParamsSetup (this->in_data, this->out_data, this->params, this->layer);
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::Render (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = this->plugin->ExecuteRender (this->in_data, this->out_data, this->params, this->layer);
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::SmartPreRender (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;
	Napi::Object result = Napi::Object::New (env);
	PF_PreRenderOutput output;

	try {
		output = this->plugin->ExecuteSmartPreRender (this->in_data, this->out_data, this->params, this->layer);
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	Napi::Object result_rect = Napi::Object::New (env);
	result.Set ("rect", result_rect);
	result_rect.Set ("left", output.result_rect.left);
	result_rect.Set ("top", output.result_rect.top);
	result_rect.Set ("right", output.result_rect.right);
	result_rect.Set ("bottom", output.result_rect.bottom);

	Napi::Object max_rect = Napi::Object::New (env);
	result.Set ("maxRect", max_rect);
	max_rect.Set ("left", output.max_result_rect.left);
	max_rect.Set ("top", output.max_result_rect.top);
	max_rect.Set ("right", output.max_result_rect.right);
	max_rect.Set ("bottom", output.max_result_rect.bottom);

	result.Set ("solid", output.solid);
	result.Set ("reserved", output.reserved);
	result.Set ("flags", output.flags);

	return result;
}

Napi::Value PluginInstanceWrapper::SmartRender (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		throw Napi::TypeError::New (env, "Wrong number of arguments");
	}

	int error_code = 0;

	try {
		error_code = this->plugin->ExecuteSmartRender (this->in_data, this->out_data, this->params, this->layer);
	} catch (std::runtime_error& exception) {
		throw Napi::Error::New (env, exception.what());
	}

	return Napi::Number::New (env, error_code);
}
