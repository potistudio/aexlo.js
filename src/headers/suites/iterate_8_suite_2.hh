#pragma once

typedef struct PF_Iterate8Suite2 {
	/**
	 * @brief iterate
	 *
	 * @param in_data in
	 * @param progress_base in
	 * @param progress_final in
	 * @param src in - source image
	 * @param area in - area to iterate over (pass NULL for all pixels)
	 * @param refcon in - parameter to pass to pix_fn
	 * @param pix_fn in - function to call for each pixel
	 * @param dst out - destination image
	 *
	 * @return Error code
	 */
	int (*iterate) (
		PF_InData     *in_data,
		int           progress_base,
		int           progress_final,
		LayerParam    *src,
		const PF_Rect *area,  // pass NULL for all pixels
		void          *refcon,
		int           (*pix_fn)(void* refcon, int x, int y, Pixel* in, Pixel* out),
		LayerParam    *dst
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
