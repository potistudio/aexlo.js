/**
 * @file point_3d.hh
 * @brief 3D Point Parameter
 * @author potistudio
 */

#pragma once

/**
 * @struct AE_Point3DParam
 * @brief 3D Point Parameter
 * @note Just like POINT, with an extra dimension. Supported in AE starting with version 10.5 (CS 5.5).
 */
struct AE_Point3DParam {
	PF_FpLong			x_value;
	PF_FpLong			y_value;
	PF_FpLong			z_value;
	PF_FpLong			x_dephault;				/* percentage of layer width; note: use 50 for halfway, not 0.5; this matches the old PF_PointDef behavior */
	PF_FpLong			y_dephault;				/* percentage of layer height */
	PF_FpLong			z_dephault;				/* percentage of layer _height_ (since typical layers are zero depth) */

	char				reserved[16];			/* set to zeros */
};
