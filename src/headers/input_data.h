#ifndef AEXLO_INPUT_DATA_H_
#define AEXLO_INPUT_DATA_H_

#include "./common.h"
#include "./basic.h"
#include "./layer_data.h"
#include "./param_data.h"
#include "./basic_suite.h"
#include "./parameters/union.h"

typedef struct {
	int (*checkout_param) (
		ProgressInfoPtr    effect_ref,
		int                index,
		int                what_time,
		int                time_step,
		unsigned int       time_scale,
		PF_ParamDef        *param
	);

	int (*checkin_param) (
		ProgressInfoPtr    effect_ref,
		PF_ParamDef        *param
	);

	int (*add_param) (
		ProgressInfoPtr    effect_ref,
		int                index,
		PF_ParamDefPtr     def
	);

	int (*abort) (
		ProgressInfoPtr    effect_ref
	);

	int (*progress) (
		ProgressInfoPtr    effect_ref,
		int                current,
		int                total
	);

	int (*register_ui) (
		ProgressInfoPtr    effect_ref,
		PF_CustomUIInfo    *cust_info
	);

	int (*checkout_layer_audio) (
		ProgressInfoPtr    effect_ref,
		int                index,
		int                start_time,
		int                duration,
		unsigned int       time_scale,
		unsigned int       rate,
		int                bytes_per_sample,
		int                num_channels,
		int                fmt_signed,
		PF_LayerAudio      *audio
	);

	int (*checkin_layer_audio) (
		ProgressInfoPtr    effect_ref,
		PF_LayerAudio      audio
	);

	int (*get_audio_data) (
		ProgressInfoPtr    effect_ref,
		PF_LayerAudio      audio,
		PF_SndSamplePtr    *data0,
		int                *num_samples0,
		unsigned int       *rate0,
		int                *bytes_per_sample0,
		int                *num_channels0,
		int                *fmt_signed0
	);

	void    *reserved_str[3];
	void    *reserved[10];
} PF_InteractCallbacks;

typedef struct {
	double				rateF;
	PF_SoundChannels		num_channels;
	PF_SoundFormat			format;
	PF_SoundSampleSize		sample_size;
} PF_SoundFormatInfo;

typedef struct {
	PF_SoundFormatInfo		fi;
	int					num_samples;
	void					*dataP;
} PF_SoundWorld;

typedef struct {
	PF_InteractCallbacks        inter;
	struct _PF_UtilCallbacks    *utils;
	ProgressInfoPtr             effect_ref;
	int                         quality;
	PF_SpecVersion              version;
	int                         serial_num;
	int                         appl_id;
	int                         num_params;
	int                         reserved;
	int                         what_cpu;
	int                         what_fpu;
	int                         current_time;
	int                         time_step;
	int                         total_time;
	int                         local_time_step;
	unsigned int                time_scale;
	int                         field;
	int                         shutter_angle;
	int                         width;
	int                         height;
	PF_Rect                     extent_hint;
	int                         output_origin_x;
	int                         output_origin_y;
	PF_RationalScale            downsample_x;
	PF_RationalScale            downsample_y;
	PF_RationalScale            pixel_aspect_ratio;
	int                         in_flags;
	PF_Handle                   global_data;
	PF_Handle                   sequence_data;
	PF_Handle                   frame_data;
	int                      start_sampL;
	int                      dur_sampL;
	int                      total_sampL;
	PF_SoundWorld               src_snd;
	SPBasicSuite                *pica_basicP;
	int                      pre_effect_source_origin_x;
	int                      pre_effect_source_origin_y;
	int                    shutter_phase;
} PF_InData;

typedef struct _PF_UtilCallbacks {
	int (*begin_sampling)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		int		qual,
		PF_ModeFlags	mf,
		PF_SampPB		*params);

	int (*subpixel_sample)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		Pixel		*dst_pixel);

	int (*area_sample)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		Pixel		*dst_pixel);

	void *get_batch_func_is_deprecated;

	int (*end_sampling)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		int		qual,
		PF_ModeFlags	mf,
		PF_SampPB		*params);

	int (*composite_rect)(
		ProgressInfoPtr		effect_ref,		/* from in_data */
		PF_Rect			*src_rect,		/* rectangle in source image */
		int			src_opacity,	/* opacity of src */
		LayerParam	*source_wld,	/* src PF world */
		int			dest_x,			/* upper left-hand corner of src rect...*/
		int			dest_y,			/* ... in composite image */
		int		field_rdr,		/* which scanlines to render (all, upper, lower) */
		PF_XferMode		xfer_mode,		/* Copy, Composite Behind, Composite In Front */
		LayerParam	*dest_wld);		/* Destination buffer. Already filled */

	int (*blend)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		const LayerParam	*src1,
		const LayerParam	*src2,
		PF_Fixed		ratio,			/* 0 == full src1, 0x00010000 == full src2 */
		LayerParam	*dst);

	int (*convolve)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		LayerParam	*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		PF_KernelFlags	flags,
		int			kernel_size,
		void			*a_kernel,
		void			*r_kernel,
		void			*g_kernel,
		void			*b_kernel,
		LayerParam	*dst);

	int (*copy)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data	*/
		LayerParam	*src,
		LayerParam	*dst,
		PF_Rect 		*src_r,			/* pass NULL for whole world */
		PF_Rect			*dst_r);		/* pass NULL for whole world */

	int (*fill)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data	*/
		const Pixel	*color,
		const PF_Rect	*dst_rect,		/* pass NULL for whole world */
		LayerParam	*world);

	int (*gaussian_kernel)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		double			kRadius,		/* desired gaussian radius */
		PF_KernelFlags	flags,			/* see kernel flags commented above */
		double			multiplier,
		int			*diameter,
		void			*kernel);

	int (*iterate)(
		PF_InData				*in_data,
		int					progress_base,
		int					progress_final,
		LayerParam			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		void*					refcon,
		PF_IteratePixel8Func	pix_fn,
		LayerParam			*dst);

	int (*premultiply)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		int			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
		LayerParam	*dst);

	int (*premultiply_color)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		LayerParam	*src,
		const Pixel	*color,			/* color to premultiply/unmultiply with */
		int			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
		LayerParam	*dst);

	int (*new_world)(
		ProgressInfoPtr			effect_ref,		/* reference from in_data */
		int				width,
		int				height,
		PF_NewWorldFlags	flags,			/* should would be pre-cleared to zeroes */
		LayerParam		*world);		/* always 32 bit */

	int (*dispose_world)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		LayerParam		*world);

	int (*iterate_origin)(
		PF_InData				*in_data,
		int					progress_base,
		int					progress_final,
		LayerParam			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		const PF_Point			*origin,
		void*					refcon,
		PF_IteratePixel8Func	pix_fn,
		LayerParam			*dst);

	int (*iterate_lut)(
		PF_InData		*in_data,
		int			progress_base,
		int			progress_final,
		LayerParam		*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		unsigned char	*a_lut0,		/* pass NULL for identity */
		unsigned char	*r_lut0,		/* pass NULL for identity */
		unsigned char	*g_lut0,		/* pass NULL for identity */
		unsigned char	*b_lut0,		/* pass NULL for identity */
		LayerParam		*dst);


	int	(*transfer_rect)(
		ProgressInfoPtr				effect_ref,
		int				quality,
		PF_ModeFlags			m_flags,
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
		PF_ModeFlags			m_flags,
		int				field,
		const LayerParam	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		const PF_FloatMatrix	*matrices,
		int					num_matrices,
		PF_Boolean				src2dst_matrix,
		const PF_Rect			*dest_rect,
		LayerParam			*dst_world);

	PF_Handle (*host_new_handle)(
		A_u_longlong			size);

	void * (*host_lock_handle)(
		PF_Handle				pf_handle);

	void (*host_unlock_handle)(
		PF_Handle				pf_handle);

	void (*host_dispose_handle)(
		PF_Handle				pf_handle);

	int (*get_callback_addr)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		int		quality,
		PF_ModeFlags	mode_flags,
		PF_CallbackID	which_callback,
		PF_CallbackFunc	*fn_ptr);

	int (*app)(ProgressInfoPtr, int, ...);	/* application specific callback */

	PF_ANSICallbacks	ansi;			/* ANSI callback block, see above */
	PF_ColorCallbacks	colorCB;		/* colorspace conversion callbacks */

	int (*get_platform_data)(
		ProgressInfoPtr		effect_ref,
		PF_PlatDataID	which,
		void			*data);

	A_u_longlong (*host_get_handle_size)(
		PF_Handle				pf_handle);

	int	(*iterate_origin_non_clip_src)(
		PF_InData				*in_data,
		int					progress_base,
		int					progress_final,
		LayerParam			*src,
		const PF_Rect			*area,
		const PF_Point			*origin,
		void*					refcon,
		PF_IteratePixel8Func	pix_fn,
		LayerParam			*dst);

	int (*iterate_generic)(
		int			iterationsL,						/* >> */		// can be PF_Iterations_ONCE_PER_PROCESSOR
		void			*refconPV,							/* >> */
		int			(*fn_func)(	void *refconPV,			/* >> */
									int thread_indexL,		// only call abort and progress from thread_indexL == 0.
									int i,
									int iterationsL));		// never sends PF_Iterations_ONCE_PER_PROCESSOR

	int (*host_resize_handle)(
		A_u_longlong		new_sizeL,		/* >> */
		PF_Handle			*handlePH);		/* <> Handle Value May Change */


	int (*subpixel_sample16)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		PF_Pixel16		*dst_pixel);

	int (*area_sample16)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		PF_Pixel16		*dst_pixel);

	int (*fill16)(
		ProgressInfoPtr			effect_ref,		/* reference from in_data	*/
		const PF_Pixel16	*color,
		const PF_Rect		*dst_rect,		/* pass NULL for whole world */
		LayerParam		*world);

	int (*premultiply_color16)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		LayerParam	*src,
		const PF_Pixel16 *color,			/* color to premultiply/unmultiply with */
		int			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
		LayerParam	*dst);

	int (*iterate16)(
		PF_InData				*in_data,
		int					progress_base,
		int					progress_final,
		LayerParam			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		void*					refcon,
		PF_IteratePixel16Func	pix_fn,
		LayerParam			*dst);

	int (*iterate_origin16)(
		PF_InData				*in_data,
		int					progress_base,
		int					progress_final,
		LayerParam			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		const PF_Point			*origin,
		void*					refcon,
		PF_IteratePixel16Func	pix_fn,
		LayerParam			*dst);

	int	(*iterate_origin_non_clip_src16)(
		PF_InData				*in_data,
		int					progress_base,
		int					progress_final,
		LayerParam				*src,
		const PF_Rect			*area,
		const PF_Point			*origin,
		void*				refcon,
		PF_IteratePixel16Func	pix_fn,
		LayerParam				*dst);

	int	(*get_pixel_data8)(
		LayerParam	*worldP,
		PF_PixelPtr		pixelsP0,		// NULL to use data in LayerParam
		Pixel		**pixPP);		// will return NULL if depth mismatch

	int	(*get_pixel_data16)(
		LayerParam	*worldP,
		PF_PixelPtr		pixelsP0,		// NULL to use data in LayerParam
		PF_Pixel16		**pixPP);		// will return NULL if depth mismatch


										// and we're done. all future expansion
										// is thru suite mechanism. (for example,
										// this is where you'll find the floating
										// pt pixel callbacks)
	int				reserved[1];

} PF_UtilCallbacks;

#endif
