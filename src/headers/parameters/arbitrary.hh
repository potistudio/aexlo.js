/**
 * @file arbitrary.hh
 * @brief Arbitrary Parameter
 * @author potistudio
 */

#pragma once
#pragma pack (push, AE, 8)

#include <stdint.h>

/**
 * @brief new arbitrary data type - you supply functions for various activities
 *        needed by After Effects to manipulate your arbitrary data.
 */
struct AE_ArbitraryParam {
	/**
	 * @brief for effect use: lets effect distinguish between
	 *        different arbitrary data param types in the same effect
	 */
	int16_t id;

	/**
	 * @brief padding, set to zero
	 */
	int16_t pad;

	/**
	 * @brief becomes owned by host at ADD_PARAM time
	 */
	void *dephault;

	/**
	 * pass NULL at ADD_PARAM time; owned by host at render time
	 */
	void *value;

	/**
	 * @brief passed into all callbacks, for effect use
	 */
	void *refconPV;
};

#pragma pack (pop, AE)
