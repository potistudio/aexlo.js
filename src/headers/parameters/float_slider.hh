#pragma once

struct AE_FloatSliderParam {
	double value;
	double phase;
	char value_desc[PF_MAX_PARAM_DESCRIPTION_LEN + 1];

	float valid_min, valid_max;
	float slider_min, slider_max;
	float dephault;
	short precision;

	short display_flags;
	unsigned int fs_flags;
	float curve_tolerance;

	//* for Pr
	// char useExponent;
	// float exponent;
};
