#pragma once
#pragma pack (push, AE, 8)

#include "./common.hh"

struct AE_LayerParam {
	void                *reserved0;
	void                *reserved1;
	AE_WorldFlags                 world_flags;
	AE_PixelPtr         data;
	int                 rowbytes;
	int                 width;
	int                 height;
	AE_UnionableRect    extent_hint;
	void                *platform_ref;
	int                 reserved_long1;
	void                *reserved_long4;
	AE_RationalScale    pix_aspect_ratio;
	void                *reserved_long2;
	int                 origin_x;
	int                 origin_y;
	int                 reserved_long3;
	int                 dephault;
};

typedef AE_LayerParam AE_EffectWorld;

#pragma pack (pop, AE)
