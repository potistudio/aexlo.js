#pragma once

#include "./basic.hh"
#include "./parameters/union.hh"

enum class ParamType : int {
	PF_Param_RESERVED = -1,
	PF_Param_LAYER = 0,
	PF_Param_SLIDER,
	PF_Param_FIX_SLIDER,
	PF_Param_ANGLE,
	PF_Param_CHECKBOX,
	PF_Param_COLOR,
	PF_Param_POINT,
	PF_Param_POPUP,
	PF_Param_CUSTOM,
	PF_Param_NO_DATA,
	PF_Param_FLOAT_SLIDER,
	PF_Param_ARBITRARY_DATA,
	PF_Param_PATH,
	PF_Param_GROUP_START,
	PF_Param_GROUP_END,
	PF_Param_BUTTON,
	PF_Param_RESERVED2,
	PF_Param_RESERVED3,
	PF_Param_POINT_3D
};

typedef struct {
	union {
		int    id;
		int    change_flags;
	} uu;

	int      ui_flags;
	short    ui_width;
	short    ui_height;

	ParamType	    param_type;
	char    name[PF_MAX_EFFECT_PARAM_NAME_LEN + 1];
	int	    flags;

	int                 unused;
	PF_ParamDefUnion    u;
} PF_ParamDef, *PF_ParamDefPtr, **PF_ParamDefH;
