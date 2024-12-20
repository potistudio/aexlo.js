#ifndef AEXLO_Suites_H_
#define AEXLO_Suites_H_

#include "./basic.h"
#include "./input_data.h"
#include "./param_data.h"
#include "./basic.h"

typedef struct PF_Iterate8Suite2 {
	int (*iterate) (
		PF_InData      *in_data,
		int         progress_base,
		int         progress_final,
		LayerParam *src,
		const PF_Rect  *area, // pass NULL for all pixels
		void           *refcon,
		int (*pix_fn)(void* refcon, int x, int y, Pixel* in, Pixel* out),
		LayerParam *dst
	);

	int (*iterate_origin) (
		PF_InData      *in_data,
		int         progress_base,
		int         progress_final,
		LayerParam *src,
		const PF_Rect  *area, // pass NULL for all pixels
		const PF_Point *origin,
		void           *refcon,
		int (*pix_fn)(void* refcon, int x, int y, Pixel* in, Pixel* out),
		LayerParam *dst
	);

	int (*iterate_lut) (
		PF_InData      *in_data,
		int         progress_base,
		int         progress_final,
		LayerParam *src,
		const PF_Rect  *area,			/* pass NULL for all pixels */
		unsigned char       *a_lut0,		/* pass NULL for identity */
		unsigned char       *r_lut0,		/* pass NULL for identity */
		unsigned char       *g_lut0,		/* pass NULL for identity */
		unsigned char       *b_lut0,		/* pass NULL for identity */
		LayerParam *dst
	);

	int(*iterate_origin_non_clip_src)(
		PF_InData		*in_data,
		int			progress_base,
		int			progress_final,
		LayerParam	*src,
		const PF_Rect	*area,
		const PF_Point	*origin,
		void			*refcon,
		int(*pix_fn)(void* refcon, int x, int y, Pixel* in, Pixel* out),
		LayerParam	*dst);

	int(*iterate_generic)(
		int			iterationsL,	/* >> */		// can be PF_Iterations_ONCE_PER_PROCESSOR
		void			*refconPV,		/* >> */
		int(*fn_func)(
			void	*refconPV,			/* >> */
			int	thread_indexL,		// only call abort and progress from thread_indexL == 0.
			int	i,
			int	iterationsL));		// never sends PF_Iterations_ONCE_PER_PROCESSOR

} PF_Iterate8Suite2;

typedef struct PF_WorldTransformSuite1 {
	int (*composite_rect) (
		ProgressInfoPtr     effect_ref,  /* from in_data */
		PF_Rect        *src_rect,   /* rectangle in source image */
		int         src_opacity, /* opacity of src */
		LayerParam *source_wld, /* src PF world */
		int         dest_x,      /* upper left-hand corner of src rect...*/
		int         dest_y,      /* ... in composite image */
		int       field_rdr,   /* which scanlines to render (all, upper, lower) */
		int    xfer_mode,   /* Copy, Composite Behind, Composite In Front */
		LayerParam *dest_wld   /* Destination buffer. Already filled */
	);

	int (*blend) (
		ProgressInfoPtr           effect_ref,		/* reference from in_data */
		const LayerParam *src1,
		const LayerParam *src2,
		int             ratio,			/* 0 == full src1, 0x00010000 == full src2 */
		LayerParam       *dst
	);

	int (*convolve) (
		ProgressInfoPtr     effect_ref,  /* reference from in_data */
		LayerParam *src,
		const PF_Rect  *area,       /* pass NULL for all pixels */
		unsigned int flags,
		int         kernel_size,
		void           *a_kernel,
		void           *r_kernel,
		void           *g_kernel,
		void           *b_kernel,
		LayerParam *dst
	);

	int (*copy) (
		ProgressInfoPtr     effect_ref, /* reference from in_data */
		LayerParam *src,
		LayerParam *dst,
		PF_Rect        *src_r,     /* pass NULL for whole world */
		PF_Rect        *dst_r     /* pass NULL for whole world */
	);

	int (*copy_hq) (
		ProgressInfoPtr     effect_ref, /* reference from in_data */
		LayerParam *src,
		LayerParam *dst,
		PF_Rect        *src_r,     /* pass NULL for whole world */
		PF_Rect        *dst_r     /* pass NULL for whole world */
	);


	 int	(*transfer_rect)(
		ProgressInfoPtr				effect_ref,
		int				quality,
		int			m_flags,
		int				field,
		const PF_Rect			*src_rec,
		const LayerParam	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		int					dest_x,
		int					dest_y,
		LayerParam			*dst_world);

	 int	(*transform_world)(
		ProgressInfoPtr				effect_ref,
		int				quality,
		int			m_flags,
		int				field,
		const LayerParam	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		const PF_FloatMatrix	*matrices,
		int					num_matrices,
		char				src2dst_matrix,
		const PF_Rect			*dest_rect,
		LayerParam			*dst_world);
} PF_WorldTransformSuite1;

#endif
