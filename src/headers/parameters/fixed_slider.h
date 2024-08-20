#ifndef AEXLO_PARAM_FIXED_SLIDER_H_
#define AEXLO_PARAM_FIXED_SLIDER_H_

typedef struct {
	/* PARAMETER VALUE */
	int value;
	char value_str[PF_MAX_PARAM_VALUE_LEN + 1]; /* string for value */
	char value_desc[PF_MAX_PARAM_DESCRIPTION_LEN + 1]; /* qualitative descr */

	/* PARAMETER DESCRIPTION */
	int valid_min, valid_max;  // acceptable input range
	int slider_min, slider_max;  // range represented by width of slider
	int dephault;
	short precision;  // decimal places to display
	short display_flags;  // set bit to 1 to enable special display: --> bit 0 == append percent sign
} PF_FixedSliderDef;

#endif
