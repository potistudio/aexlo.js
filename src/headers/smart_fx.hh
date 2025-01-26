#pragma once

#include <stdint.h>

#include "basic.hh"
#include "layer_data.hh"

enum {
	PF_ChannelMask_ALPHA = 0x1,
	PF_ChannelMask_RED   = 0x2,
	PF_ChannelMask_GREEN = 0x4,
	PF_ChannelMask_BLUE  = 0x8,
	PF_ChannelMask_ARGB  = 0xF,
};
typedef int32_t PF_ChannelMask;

enum {
	PF_RenderOutputFlag_RETURNS_EXTRA_PIXELS = 0x1,
	PF_RenderOutputFlag_GPU_RENDER_POSSIBLE  = 0x2,
	PF_RenderOutputFlag_RESERVED1            = 0x4,
};
typedef short PF_RenderOutputFlags;

enum {
	PF_GPU_Framework_NONE = 0,
	PF_GPU_Framework_OPENCL,
	PF_GPU_Framework_METAL,
	PF_GPU_Framework_CUDA,
};
typedef int32_t PF_GPU_Framework;

typedef void (*PF_DeletePreRenderDataFunc) (void *pre_render_data);

typedef struct {
	PF_LRect          rect;
	int32_t           field;
	PF_ChannelMask    channel_mask;
	bool              preserve_rgb_of_zero_alpha;
	char              unused[3];
	int32_t           reserved[4];
} PF_RenderRequest;

typedef struct {
	PF_LRect            result_rect;
	PF_LRect            max_result_rect;
	PF_RationalScale    par;
	bool                solid;
	bool                reservedB[3];
	int32_t             ref_width;
	int32_t             ref_height;
	int32_t             reserved[6];
} PF_CheckoutResult;

typedef struct {
	PF_RenderRequest    output_request;
	short               bitdepth;
	const void          *gpu_data;
	PF_GPU_Framework    what_gpu;
	uint32_t            device_index;
} PF_PreRenderInput;

typedef struct {
	PF_LRect                      result_rect;
	PF_LRect                      max_result_rect;
	bool                          solid;
	bool                          reserved;
	PF_RenderOutputFlags          flags;
	void                          *pre_render_data;
	PF_DeletePreRenderDataFunc    delete_pre_render_data_func;
} PF_PreRenderOutput;

typedef struct {
	int32_t (*checkout_layer) (
		ProgressInfoPtr           effect_ref,
		int32_t                   index,
		int32_t                   checkout_idL,
		const PF_RenderRequest    *req,
		int32_t                   what_time,
		int32_t                   time_step,
		uint32_t                  time_scale,
		PF_CheckoutResult         *checkout_result
	);

	int32_t (*GuidMixInPtr) (
		ProgressInfoPtr    effect_ref,
		uint32_t           buf_sizeLu,
		const void         *buf
	);
} PF_PreRenderCallbacks;

typedef struct {
	PF_PreRenderInput        *input;
	PF_PreRenderOutput       *output;
	PF_PreRenderCallbacks    *callbacks;
} PF_PreRenderExtra;

/** ---- Smart Render Extra ---- **/
typedef struct {
	PF_RenderRequest    output_request;
	short               bitdepth;
	void                *pre_render_data;
	const void			*gpu_data;
	PF_GPU_Framework    what_gpu;
	uint32_t            device_index;
} PF_SmartRenderInput;

typedef struct {
	int32_t (*checkout_layer_pixels) (
		ProgressInfoPtr    effect_ref,
		int32_t            checkout_idL,
		LayerParam         **pixels
	);

	int32_t (*checkin_layer_pixels) (
		ProgressInfoPtr    effect_ref,
		int32_t            checkout_idL
	);

	int32_t (*checkout_output) (
		ProgressInfoPtr    effect_ref,
		LayerParam         **output
	);
} PF_SmartRenderCallbacks;

typedef struct {
	PF_SmartRenderInput        *input;
 	PF_SmartRenderCallbacks    *callbacks;
} PF_SmartRenderExtra;
