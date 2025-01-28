#pragma once

/**
 * @struct AE_AngleParam
 * @brief Angle Parameter
 */
struct AE_AngleParam {
	/**
	 * @brief degrees with fixed point accuracy;
	 * @warning this is NOT limited in range to 0 to 360.
	 */
	int value;

	/**
	 * @brief default value
	 */
	int dephault;

	/**
	 * @brief Min and max values.
	 * @note Note!! Not supported for effect plugins.
	 */
	int valid_min, valid_max;
};
