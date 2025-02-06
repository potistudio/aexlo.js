#pragma once
#pragma pack (push, AE, 8)

#include "./common.hh"
#include "layer_data.hh"

enum class AE_ChannelMask : int {
	ALPHA = 0x1,
	RED   = 0x2,
	GREEN = 0x4,
	BLUE  = 0x8,
	ARGB  = 0xF,
};

enum class AE_RenderOutputFlags : short {
	RETURNS_EXTRA_PIXELS = 0x1,
	GPU_RENDER_POSSIBLE  = 0x2,
	RESERVED1            = 0x4,
};

enum class AE_GPU_Framework : int {
	NONE   = 0,
	OPENCL,
	METAL,
	CUDA,
};

typedef void (*AE_DeletePreRenderDataFunc) (void *pre_render_data);

struct AE_RenderRequest {
	AE_LRect          rect;
	int               field;
	AE_ChannelMask    channel_mask;
	bool              preserve_rgb_of_zero_alpha;
	char              unused[3];
	int               reserved[4];
};

struct AE_CheckoutResult {
	AE_LRect            result_rect;
	AE_LRect            max_result_rect;
	AE_RationalScale    par;
	bool                solid;
	bool                reservedB[3];
	int                 ref_width;
	int                 ref_height;
	int                 reserved[6];
};

struct AE_PreRenderInput {
	AE_RenderRequest    output_request;
	short               bitdepth;
	const void          *gpu_data;
	AE_GPU_Framework    what_gpu;
	unsigned int        device_index;
};

struct AE_PreRenderOutput {
	AE_LRect                      result_rect;
	AE_LRect                      max_result_rect;
	bool                          solid;
	bool                          reserved;
	AE_RenderOutputFlags          flags;
	void                          *pre_render_data;
	AE_DeletePreRenderDataFunc    delete_pre_render_data_func;
};

struct AE_PreRenderCallbacks {
	int (*checkout_layer) (
		AE_ProgressInfoPtr        effect_ref,
		int                       index,
		int                       checkout_idL,
		const AE_RenderRequest    *req,
		int                       what_time,
		int                       time_step,
		unsigned int              time_scale,
		AE_CheckoutResult         *checkout_result
	);

	int (*GuidMixInPtr) (
		AE_ProgressInfoPtr    effect_ref,
		unsigned int          buf_sizeLu,
		const void            *buf
	);
};

struct AE_PreRenderExtra {
	AE_PreRenderInput        *input;
	AE_PreRenderOutput       *output;
	AE_PreRenderCallbacks    *callbacks;
};


/* ---------------- Smart Render Extra ---------------- */

struct AE_SmartRenderInput {
	AE_RenderRequest    output_request;
	short               bitdepth;
	void                *pre_render_data;
	const void			*gpu_data;
	AE_GPU_Framework    what_gpu;
	unsigned int        device_index;
};

struct AE_SmartRenderCallbacks {
	int (*checkout_layer_pixels) (
		AE_ProgressInfoPtr    effect_ref,
		int                   checkout_idL,
		AE_LayerParam         **pixels
	);

	int (*checkin_layer_pixels) (
		AE_ProgressInfoPtr    effect_ref,
		int                   checkout_idL
	);

	int (*checkout_output) (
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         **output
	);
};

struct AE_SmartRenderExtra {
	AE_SmartRenderInput        *input;
 	AE_SmartRenderCallbacks    *callbacks;
};

#pragma pack (pop, AE)
