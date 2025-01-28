#pragma once

/**
 * @struct AE_PointParam
 * @brief The values for the point use the source's coordinate system, with the
	origin at the top left. The values are expressed in fixed point, with
	16 bits of fractional precision (out of a total of 32 bits).
	@brief The dephaults (sorry) are expressed as percentages (with 16 bits of
	fraction) with the origin at the top left. The percent can be negative,
	but should not be smaller than -600%. It should not be greater than 600%.
 */
struct AE_PointParam {
	/**
	 * @brief Parameter Value (x)
	 */
	int x_value;

	/**
	 * @brief Parameter Value (y)
	 */
	int y_value;

	char reserved[3];

	/**
	 * @brief If restrict_bounds is TRUE, the user will not be allowed to specify points outside the bounds of the layer to which they are applying the effect.
	 * If this is TRUE, the dephaults should be between 0.0 and 100.0.
	 */
	bool restrict_bounds;

	int x_dephault;
	int y_dephault;
};
