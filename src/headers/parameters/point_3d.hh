/**
 * @file point_3d.hh
 * @brief 3D Point Parameter
 * @author potistudio
 */

#pragma once
#pragma pack (push, AE, 8)

/**
 * @struct AE_Point3DParam
 * @brief 3D Point Parameter
 * @note Just like POINT, with an extra dimension. Supported in AE starting with version 10.5 (CS 5.5).
 */
struct AE_Point3DParam {
	float    x_value;
	float    y_value;
	float    z_value;
	float    x_dephault;
	float    y_dephault;
	float    z_dephault;

	char     reserved[16];
};

#pragma pack (pop, AE)
