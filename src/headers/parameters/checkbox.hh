#pragma once

#include <stdint.h>

struct AE_CheckBoxParam {
	/**
	 * @brief Parameter value
	 */
	int32_t value;

	/**
	 * @brief Default value
	 */
	bool dephault;

	/**
	 * @brief padding
	 */
	char reserved;
	short reserved1;

	union {
		const char *nameptr;
	} u;
};
