#ifndef AEXLO_INTERACT_CALLBACKS_FACTORY_H_
#define AEXLO_INTERACT_CALLBACKS_FACTORY_H_

#include <iostream>

#include "logger/logger.hh"
#include "./headers/input_data.hh"

// #### Factory Process ####
//
// 1. Define Class with Function Pointers
// -> "input_data.h"
//
// 2. Instantiate Class
// in_data->inter = PF_InteractCallbacks();
//
// 3. Attach Function to Pointer (or with Lambda)
// in_data->inter.add_param = &addParam;
//
// #########################

class InteractCallbackFactory {
	public:
		InteractCallbackFactory();
		~InteractCallbackFactory();

		PF_InteractCallbacks Create();
};

#endif
