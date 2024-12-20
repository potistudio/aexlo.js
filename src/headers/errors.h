#ifndef AEXLO_ERROR_H_
#define AEXLO_ERROR_H_

#include "./macros.h"

enum {
	Err_NONE = 0,
	Err_OUT_OF_MEMORY = 4,
	Err_INTERNAL_STRUCT_DAMAGED = 512,
	Err_INVALID_INDEX,
	Err_UNRECOGNIZED_PARAM_TYPE,
	Err_INVALID_CALLBACK,
	Err_BAD_CALLBACK_PARAM,
	Err_Interrupt_CANCEL,
	Err_CANNOT_PARSE_KEYFRAME_TEXT
};

#endif
