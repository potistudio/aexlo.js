/**
 * @file slider.hh
 * @brief Slider Parameter
 * @author potistudio
 */

#pragma once
#pragma pack (push, AE, 8)

/**
 * @struct AE_SliderParam
 * @brief Slider Parameter
 */
struct AE_SliderParam {
	long	value;
	char value_str[32];
	char value_desc[32];

	int	valid_min, valid_max;
	int	slider_min, slider_max;
	int	dephault;
};

#pragma pack (pop, AE)
