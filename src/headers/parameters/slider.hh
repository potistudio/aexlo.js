#pragma once

typedef struct {
	/* PARAMETER VALUE */
	int	value;
	char value_str[PF_MAX_PARAM_VALUE_LEN + 1];  // string for value
	char value_desc[PF_MAX_PARAM_DESCRIPTION_LEN + 1];  // qualitative description

	/* PARAMETER DESCRIPTION */
	int	valid_min, valid_max;  // acceptable input range
	int	slider_min, slider_max;  // range represented by width of slider
	int	dephault;
} PF_SliderDef;
