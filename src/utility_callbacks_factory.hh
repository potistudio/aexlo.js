#ifndef AEXLO_UTILITY_CALLBACK_FACTORY_H_
#define AEXLO_UTILITY_CALLBACK_FACTORY_H_

#include <stdarg.h>
#include <iostream>
#include "./headers/input_data.hh"

class UtilityCallbackFactory {
	public:
		UtilityCallbackFactory();
		~UtilityCallbackFactory();

		_PF_UtilCallbacks * Create();
};

#endif
