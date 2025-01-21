#ifndef AEXLO_UTILITY_CALLBACK_FACTORY_H_
#define AEXLO_UTILITY_CALLBACK_FACTORY_H_

#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "logger/logger.hh"
#include "./headers/input_data.hh"

class UtilityCallbackFactory {
	public:
		UtilityCallbackFactory();
		~UtilityCallbackFactory();

		_PF_UtilCallbacks * Create();
};

#endif
