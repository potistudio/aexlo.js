#pragma once

struct AE_PopupParam {
	/* PARAMETER VALUE */
	PF_ParamValue	value;

	/* PARAMETER DESCRIPTION */
	short		num_choices;
	short		dephault;
	union {
		const char	*namesptr; /*  menu manager standard, '|' separator */
	} u;
};
