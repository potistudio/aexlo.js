#pragma once
#pragma pack (push, AE, 8)

#include "../parameters/point.hh"

struct AE_Iterate8Suite2 {
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
		AE_InData        *in_data,
		int              progress_base,
		int              progress_final,
		AE_LayerParam    *src,
		const AE_Rect    *area,
		void             *refcon,
		int              (*pix_fn)(void* refcon, int x, int y, AE_Pixel* in, AE_Pixel* out),
		AE_LayerParam    *dst
	);

	int (*iterate_origin) (
		AE_InData              *in_data,
		int                    progress_base,
		int                    progress_final,
		AE_LayerParam          *src,
		const AE_Rect          *area,
		const AE_PointParam    *origin,
		void                   *refcon,
		int                    (*pix_fn)(void* refcon, int x, int y, AE_Pixel* in, AE_Pixel* out),
		AE_LayerParam          *dst
	);

	int (*iterate_lut) (
		AE_InData        *in_data,
		int              progress_base,
		int              progress_final,
		AE_LayerParam    *src,
		const AE_Rect    *area,
		unsigned char    *a_lut0,
		unsigned char    *r_lut0,
		unsigned char    *g_lut0,
		unsigned char    *b_lut0,
		AE_LayerParam    *dst
	);

	int (*iterate_origin_non_clip_src) (
		AE_InData              *in_data,
		int                    progress_base,
		int                    progress_final,
		AE_LayerParam          *src,
		const AE_Rect          *area,
		const AE_PointParam    *origin,
		void                   *refcon,
		int                    (*pix_fn)(void* refcon, int x, int y, AE_Pixel* in, AE_Pixel* out),
		AE_LayerParam          *dst
	);

	int (*iterate_generic) (
		int     iterationsL,
		void    *refconPV,
		int     (*fn_func)(void	*refconPV, int thread_indexL, int i, int iterationsL)
	);
};

#pragma pack (pop, AE)
