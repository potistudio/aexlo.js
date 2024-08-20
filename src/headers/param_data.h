#ifndef AEXLO_PARAM_DATA_H_
#define AEXLO_PARAM_DATA_H_

#include "./basic.h"
#include "./parameters/union.h"

typedef struct {
	union {
		int    id;
		int    change_flags;
	} uu;

	int      ui_flags;
	short    ui_width;
	short    ui_height;

	int	    param_type;
	char    name[PF_MAX_EFFECT_PARAM_NAME_LEN + 1];
	int	    flags;

	int                 unused;
	PF_ParamDefUnion    u;
} PF_ParamDef, *PF_ParamDefPtr, **PF_ParamDefH;

#endif
