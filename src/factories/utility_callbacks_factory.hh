#pragma once

#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "../../lib/nameof/nameof.hpp"

#include "../logger/logger.hh"
#include "../headers/input_data.hh"
#include "../headers/parameters/point.hh"

class UtilityCallbackFactory {
	public:
		UtilityCallbackFactory();
		~UtilityCallbackFactory();

		_AE_UtilCallbacks * Create();
};
