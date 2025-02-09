#pragma once
#pragma pack (push, AE, 8)

#include "./parameters/union.hh"

enum class AE_ParamType : int {
	RESERVED = -1,
	LAYER    = 0,
	SLIDER,
	FIX_SLIDER,
	ANGLE,
	CHECKBOX,
	COLOR,
	POINT,
	POPUP,
	CUSTOM,
	_NO_DATA,
	FLOAT_SLIDER,
	ARBITRARY_DATA,
	PATH,
	GROUP_START,
	GROUP_END,
	BUTTON,
	RESERVED2,
	RESERVED3,
	POINT_3D
};

struct AE_ParamDef {
	union {
		int             id;
		int             change_flags;
	} uu;

	int                 ui_flags;
	short               ui_width;
	short               ui_height;

	AE_ParamType        param_type;
	char                name[32];
	int	                flags;

	int                 unused;
	AE_ParamDefUnion    u;
};

typedef AE_ParamDef *AE_ParamDefPtr, **AE_ParamDefH;
typedef AE_ParamDef **AE_ParamList;

#pragma pack (pop, AE)
