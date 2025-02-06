#pragma once
#pragma pack (push, AE, 8)

#include "../common.hh"

struct AE_PopupParam {
	/* PARAMETER VALUE */
	AE_ParamValue	value;

	/* PARAMETER DESCRIPTION */
	short		num_choices;
	short		dephault;
	union {
		const char	*namesptr; /*  menu manager standard, '|' separator */
	} u;
};

#pragma pack (pop, AE)
