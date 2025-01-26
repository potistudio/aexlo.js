#pragma once

#include "./basic.hh"

typedef struct LayerParam {
	void                *reserved0;
	void                *reserved1;
	int                 world_flags;
	PF_PixelPtr         data;
	int                 rowbytes;
	int                 width;
	int                 height;
	PF_UnionableRect    extent_hint;
	void                *platform_ref;
	int                 reserved_long1;
	void                *reserved_long4;
	PF_RationalScale    pix_aspect_ratio;
	void                *reserved_long2;
	int                 origin_x;
	int                 origin_y;
	int                 reserved_long3;
	int                 dephault;
} LayerParam;
