#pragma once
#pragma pack (push, AE, 8)

#include "../common.hh"

/**
 * @struct AE_ColorParam
 * @brief Color Parameter
 */
struct AE_ColorParam {
	/**
	 * @brief Parameter Value
	 */
	AE_Pixel value;

	/**
	 * @brief Parameter Description
	 */
	AE_Pixel dephault;
};

#pragma pack (pop, AE)
