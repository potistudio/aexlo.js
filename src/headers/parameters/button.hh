/**
 * @file button.hh
 * @brief Button Parameter
 * @author potistudio
 */

#pragma once

/**
 * @struct AE_ButtonParam
 * @brief Momentary Button Parameter
 * @note supported by AE starting with CS 5.5 (AE 10.5); may be supported in other hosts
 */
struct AE_ButtonParam {
	long value;
	union {
		const char *nameptr;
	} u;
};
