#pragma once
#pragma pack (push, AE, 8)

struct AE_FloatSliderParam {
	double value;
	double phase;
	char value_desc[32];

	float valid_min, valid_max;
	float slider_min, slider_max;
	float dephault;
	short precision;

	short display_flags;
	unsigned int fs_flags;
	float curve_tolerance;

	char useExponent;
	float exponent;
};

#pragma pack (pop, AE)
