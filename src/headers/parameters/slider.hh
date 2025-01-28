/**
 * @file slider.hh
 * @brief Slider Parameter
 * @author potistudio
 */

#pragma once

/**
 * @struct AE_SliderParam
 * @brief Slider Parameter
 */
struct AE_SliderParam {
	/* PARAMETER VALUE */
	long	value;
	char value_str[32];  // string for value
	char value_desc[32];  // qualitative description

	/* PARAMETER DESCRIPTION */
	int	valid_min, valid_max;  // acceptable input range
	int	slider_min, slider_max;  // range represented by width of slider
	int	dephault;
};
