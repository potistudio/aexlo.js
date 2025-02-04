#pragma once

#include <iostream>
#include "../lib/nameof/nameof.hpp"

#include "logger/logger.hh"
#include "./headers/input_data.hh"

// #### Factory Process ####
//
// 1. Define Class with Function Pointers
// -> "input_data.h"
//
// 2. Instantiate Class
// in_data->inter = AE_InteractCallbacks();
//
// 3. Attach Function to Pointer (or with Lambda)
// in_data->inter.add_param = &addParam;
//
// #########################

class InteractCallbackFactory {
	public:
		InteractCallbackFactory();
		~InteractCallbackFactory();

		AE_InteractCallbacks Create();
};
