/**
 * @file main.cc
 * @brief Main addon entry point
 * @author potistudio
 */

//                                                               //
//   █████  ███████ ██   ██ ██       ██████          ██ ███████  //
//  ██   ██ ██       ██ ██  ██      ██    ██         ██ ██       //
//  ███████ █████     ███   ██      ██    ██         ██ ███████  //
//  ██   ██ ██       ██ ██  ██      ██    ██    ██   ██      ██  //
//  ██   ██ ███████ ██   ██ ███████  ██████  ██  █████  ███████  //
//                                                               //

#include <napi.h>

#include "plugin_instance_wrapper.hh"

class Aexlo : public Napi::Addon<Aexlo> {
	public:
		Aexlo (Napi::Env env, Napi::Object exports) {
			PluginInstanceWrapper::Init (env, exports);
		}
};

NODE_API_ADDON (Aexlo);
