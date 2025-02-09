#pragma once
#pragma pack (push, AE, 8)

enum class AE_CustomEventFlags : int {
	NONE       = 0,
	COMP       = 1L << 0,
	LAYER      = 1L << 1,
	EFFECT     = 1L << 2,
	PREVIEW    = 1L << 3
};

enum class AE_UIAlignment : int {
	NONE   = 0,
	TOP    = 1L << 0,
	LEFT   = 1L << 1,
	BOTTOM = 1L << 2,
	RIGHT  = 1L << 3
};

struct _AE_CustomUIInfo {
	int                    reserved;
	AE_CustomEventFlags    events;

	int                    comp_ui_width;
	int                    comp_ui_height;
	AE_UIAlignment         comp_ui_alignment;

	int                    layer_ui_width;
	int                    layer_ui_height;
	AE_UIAlignment         layer_ui_alignment;

	int                    preview_ui_width;
	int                    preview_ui_height;
	AE_UIAlignment         preview_ui_alignment;
};

typedef struct _AE_CustomUIInfo AE_CustomUIInfo;

#pragma pack (pop, AE)
