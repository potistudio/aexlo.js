#ifndef AEXLO_Suites_H_
#define AEXLO_Suites_H_

#include <stdint.h>

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

typedef struct PF_ANSICallbacksSuite {
	double (*sin)(double);
	double (*cos)(double);
	double (*tan)(double);

	double (*asin)(double);
	double (*acos)(double);
	double (*atan)(double);
	double (*atan2)(double y, double x);

	double (*log)(double);
	double (*log10)(double);

	double (*ceil)(double);
	double (*exp)(double);
	double (*fabs)(double);
	double (*floor)(double);
	double (*fmod)(double x, double y);
	double (*hypot)(double x, double y);
	double (*pow)(double x, double y);
	double (*sqrt)(double);

	int (*sprintf)(char *, const char *, ...);
	char * (*strcpy)(char *, const char *);
} PF_ANSICallbacksSuite;

typedef struct PF_EffectUISuite1 {
	int (*PF_SetOptionsButtonName)(void *, const char *);
} PF_EffectUISuite1;

typedef struct PF_HandleSuite1 {
	void * (*HostNewHandle)(uint64_t);
	void * (*HostLockHandle)(void *);
	void (*HostUnlockHandle)(void *);
	void (*HostDisposeHandle)(void *);
	uint64_t (*HostGetHandleSize)(void *);
	int (*HostResizeHandle)(uint64_t, void **);
} PF_HandleSuite1;

#endif
