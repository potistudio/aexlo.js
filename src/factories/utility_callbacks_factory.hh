#pragma once

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
