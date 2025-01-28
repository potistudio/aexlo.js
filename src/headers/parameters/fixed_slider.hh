/**
 * @file fixed_slider.hh
 * @brief Fixed Slider Parameter
 * @author potistudio
 */

#pragma once

/**
 * @struct AE_FixedSliderParam
 * @brief Fixed Point Slider Parameter
 */
struct AE_FixedSliderParam {
	/**
	 * @brief Parameter Value
	 */
	int value;

	char value_str[32]; /* string for value */
	char value_desc[32]; /* qualitative descr */

	/* PARAMETER DESCRIPTION */
	int valid_min, valid_max;  // acceptable input range
	int slider_min, slider_max;  // range represented by width of slider
	int dephault;
	short precision;  // decimal places to display
	short display_flags;  // set bit to 1 to enable special display: --> bit 0 == append percent sign
};
