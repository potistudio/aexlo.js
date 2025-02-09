#pragma once
#pragma pack (push, AE, 8)

#include "../errors.hh"
#include "../common.hh"
#include "../uncommon.hh"
#include "../layer_data.hh"

struct AE_WorldTransformSuite1 {
	AE_Error (*CompositeRect) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Rect               *src_rect,
		int                   src_opacity,
		AE_EffectWorld        *source_wld,
		int                   dest_x,
		int                   dest_y,
		AE_Field              field_rdr,
		AE_XferMode           xfer_mode,
		AE_LayerParam         *dest_wld
	);

	AE_Error (*Blend) (
		AE_ProgressInfoPtr      effect_ref,
		const AE_EffectWorld    *src1,
		const AE_EffectWorld    *src2,
		AE_Fixed                ratio,
		AE_EffectWorld          *dst
	);

	AE_Error (*Convolve) (
		AE_ProgressInfoPtr    effect_ref,
		AE_EffectWorld        *src,
		const AE_Rect         *area,
		AE_KernelFlags        flags,
		int                   kernel_size,
		void                  *a_kernel,
		void                  *r_kernel,
		void                  *g_kernel,
		void                  *b_kernel,
		AE_EffectWorld        *dst
	);

	AE_Error (*Copy) (
		AE_ProgressInfoPtr    effect_ref,
		AE_EffectWorld        *src,
		AE_EffectWorld        *dst,
		AE_Rect               *src_r,
		AE_Rect               *dst_r
	);

	AE_Error (*CopyHQ) (
		AE_ProgressInfoPtr    effect_ref,
		AE_EffectWorld        *src,
		AE_EffectWorld        *dst,
		AE_Rect               *src_r,
		AE_Rect               *dst_r
	);

	AE_Error (*TransferRect) (
		AE_ProgressInfoPtr        effect_ref,
		AE_Quality                quality,
		AE_ModeFlags              m_flags,
		AE_Field                  field,
		const AE_Rect             *src_rec,
		const AE_EffectWorld      *src_world,
		const AE_CompositeMode    *comp_mode,
		const AE_MaskWorld        *mask_world0,
		int                       dest_x,
		int                       dest_y,
		AE_EffectWorld            *dst_world
	);

	AE_Error (*TransformWorld) (
		AE_ProgressInfoPtr        effect_ref,
		AE_Quality                quality,
		AE_ModeFlags              m_flags,
		AE_Field                  field,
		const AE_EffectWorld      *src_world,
		const AE_CompositeMode    *comp_mode,
		const AE_MaskWorld        *mask_world0,
		const AE_FloatMatrix      *matrices,
		int                       num_matrices,
		AE_Boolean                src2dst_matrix,
		const AE_Rect             *dest_rect,
		AE_EffectWorld            *dst_world
	);
};

#pragma pack (pop, AE)
