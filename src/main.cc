/**
 * @file main.cc
 * @brief Main addon entry point
 * @author potistudio
 */

//                                                                                        //
//   ________  _______      ___    ___ ___       ________            ___  ________        //
//  |\   __  \|\  ___ \    |\  \  /  /|\  \     |\   __  \          |\  \|\   ____\       //
//  \ \  \|\  \ \   __/|   \ \  \/  / | \  \    \ \  \|\  \         \ \  \ \  \___|_      //
//   \ \   __  \ \  \_|/__  \ \    / / \ \  \    \ \  \\\  \      __ \ \  \ \_____  \     //
//    \ \  \ \  \ \  \_|\ \  /     \/   \ \  \____\ \  \\\  \ ___|\  \\_\  \|____|\  \    //
//     \ \__\ \__\ \_______\/  /\   \    \ \_______\ \_______\\__\ \________\____\_\  \   //
//      \|__|\|__|\|_______/__/ /\ __\    \|_______|\|_______\|__|\|________|\_________\  //
//                         |__|/ \|__|                                      \|_________|  //
//                                                                                        //

#include <napi.h>

#include "plugin_instance_wrapper.hh"

class Aexlo : public Napi::Addon<Aexlo> {
	public:
		Aexlo (Napi::Env env, Napi::Object exports) {
			PluginInstanceWrapper::Init (env, exports);
		}
};

NODE_API_ADDON (Aexlo);
