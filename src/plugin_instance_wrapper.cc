#include "plugin_instance_wrapper.hh"

Napi::Object PluginInstanceWrapper::Init (Napi::Env env, Napi::Object exports) {
	Napi::Function func = DefineClass (env, "PluginInstance", {
		InstanceMethod ("loadResources", &PluginInstanceWrapper::LoadResources),
		InstanceMethod ("about", &PluginInstanceWrapper::About),
		InstanceMethod ("setupGlobal", &PluginInstanceWrapper::SetupGlobal),
		InstanceMethod ("setupParameters", &PluginInstanceWrapper::SetupParameters),
		InstanceMethod ("render", &PluginInstanceWrapper::Render),
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
		Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return;
	}

	if (!info[0].IsString()) {
		Napi::TypeError::New (env, "Wrong argument type with arg 0").ThrowAsJavaScriptException();
		return;
	}

	std::string path = info[0].As<Napi::String>();

	this->plugin = new PluginInstance (path);
}

PluginInstanceWrapper::~PluginInstanceWrapper() {
	delete this->plugin;
}

Napi::Value PluginInstanceWrapper::LoadResources (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return env.Null();
	}

	std::string resources = this->plugin->ExtractResources ();
	return Napi::String::New (env, resources);
}

Napi::Value PluginInstanceWrapper::About (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	/* VALIDATE ARGUMENTS */
	if (info.Length() != 0) {
		Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return env.Null();
	}

	int error_code = 0;

	try {
		error_code = this->plugin->ExecuteAbout (this->in_data, this->out_data, this->params, this->layer);
	} catch (Napi::Error& exception) {
		Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
		return env.Null();
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::SetupGlobal (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return env.Null();
	}

	int error_code = 0;

	try {
		error_code = this->plugin->ExecuteGlobalSetup (this->in_data, this->out_data, this->params, this->layer);
	} catch (Napi::Error& exception) {
		Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
		return env.Null();
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::SetupParameters (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return env.Null();
	}

	int error_code = 0;

	try {
		error_code = this->plugin->ExecuteParamsSetup (this->in_data, this->out_data, this->params, this->layer);
	} catch (Napi::Error& exception) {
		Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
		return env.Null();
	}

	return Napi::Number::New (env, error_code);
}

Napi::Value PluginInstanceWrapper::Render (const Napi::CallbackInfo &info) {
	Napi::Env env = info.Env();

	if (info.Length() != 0) {
		Napi::TypeError::New (env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return env.Null();
	}

	int error_code = 0;

	try {
		error_code = this->plugin->ExecuteRender (this->in_data, this->out_data, this->params, this->layer);
	} catch (Napi::Error& exception) {
		Napi::Error::New (env, exception.Message()).ThrowAsJavaScriptException();
		return env.Null();
	}

	return Napi::Number::New (env, error_code);
}
