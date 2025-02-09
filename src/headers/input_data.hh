#pragma once
#pragma pack (push, AE, 8)

#include "./common.hh"
#include "./uncommon.hh"
#include "./in_flags.hh"
#include "./interact_callbacks.hh"
#include "./audio.hh"

struct AE_InData {
	AE_InteractCallbacks        inter;             // *0-176
	struct _AE_UtilCallbacks    *utils;            // *176-552
	AE_ProgressInfoPtr          effect_ref;        // *552-8
	AE_Quality                  quality;           //  560-4
	AE_SpecVersion              version;           // *568-8
	int                         serial_num;        //  576-4
	int                         appl_id;           // *580-4
	int                         num_params;        //  584-4
	int                         reserved;          // *588-4
	int                         what_cpu;          //  592-4
	int                         what_fpu;          // *596-4
	int                         current_time;      //  600-4
	int                         time_step;         // *604-4
	int                         total_time;        //  608-4
	int                         local_time_step;   // *612-4
	unsigned int                time_scale;        //  616-4
	AE_Field                    field;             // *620-4
	AE_Fixed                    shutter_angle;     //  624-4
	int                         width;             // *628-4
	int                         height;            //  632-4 + 4
	AE_Rect                     extent_hint;       // *640-8
	int                         output_origin_x;
	int                         output_origin_y;
	AE_RationalScale            downsample_x;
	AE_RationalScale            downsample_y;
	AE_RationalScale            pixel_aspect_ratio;
	AE_InFlags                  in_flags;
	AE_Handle                   global_data;
	AE_Handle                   sequence_data;
	AE_Handle                   frame_data;
	int                         start_sampL;
	int                         dur_sampL;
	int                         total_sampL;
	AE_SoundWorld               src_snd;
	struct SPBasicSuite         *pica_basicP;
	int                         pre_effect_source_origin_x;
	int                         pre_effect_source_origin_y;
	AE_Fixed                    shutter_phase;
};

struct _AE_UtilCallbacks {
	AE_Error (*BeginSampling) (
		AE_ProgressInfoPtr    effect_ref,
		int                   qual,
		AE_ModeFlags          mf,
		AE_SamplePB           *params
	);

	AE_Error (*SubpixelSample) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Fixed              x,
		AE_Fixed              y,
		const AE_SamplePB     *params,
		AE_Pixel              *dst_pixel
	);

	AE_Error (*AreaSample) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Fixed              x,
		AE_Fixed              y,
		const AE_SamplePB     *params,
		AE_Pixel              *dst_pixel
	);

	void *get_batch_func_is_deprecated;

	AE_Error (*EndSampling) (
		AE_ProgressInfoPtr    effect_ref,
		int                   qual,
		AE_ModeFlags          mf,
		AE_SamplePB           *params
	);

	AE_Error (*CompositeRect) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Rect               *src_rect,
		int                   src_opacity,
		AE_LayerParam         *source_wld,
		int                   dest_x,
		int                   dest_y,
		int                   field_rdr,
		AE_XferMode           xfer_mode,
		AE_LayerParam         *dest_wld
	);

	AE_Error (*Blend) (
		AE_ProgressInfoPtr     effect_ref,
		const AE_LayerParam    *src1,
		const AE_LayerParam    *src2,
		AE_Fixed               ratio,
		AE_LayerParam          *dst
	);

	AE_Error (*Convolve) (
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         *src,
		const AE_Rect         *area,
		AE_KernelFlags        flags,
		int                   kernel_size,
		void                  *a_kernel,
		void                  *r_kernel,
		void                  *g_kernel,
		void                  *b_kernel,
		AE_LayerParam         *dst
	);

	AE_Error (*Copy) (
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         *src,
		AE_LayerParam         *dst,
		AE_Rect               *src_r,
		AE_Rect               *dst_r
	);

	AE_Error (*Fill) (
		AE_ProgressInfoPtr    effect_ref,
		const AE_Pixel        *color,
		const AE_Rect         *dst_rect,
		AE_LayerParam         *world
	);

	AE_Error (*GaussianKernel) (
		AE_ProgressInfoPtr    effect_ref,
		double                kRadius,
		AE_KernelFlags        flags,
		double                multiplier,
		int                   *diameter,
		void                  *kernel
	);

	AE_Error (*Iterate) (
		AE_InData               *in_data,
		int                     progress_base,
		int                     progress_final,
		AE_LayerParam			*src,
		const AE_Rect           *area,
		void                    *refcon,
		AE_IteratePixel8Func    pix_fn,
		AE_LayerParam           *dst
	);

	AE_Error (*Premultiply) (
		AE_ProgressInfoPtr    effect_ref,
		int                   forward,
		AE_LayerParam         *dst
	);

	AE_Error (*PremultiplyColor) (
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         *src,
		const AE_Pixel        *color,
		int                   forward,
		AE_LayerParam         *dst
	);

	AE_Error (*NewWorld) (
		AE_ProgressInfoPtr    effect_ref,
		int                   width,
		int                   height,
		AE_NewWorldFlags      flags,
		AE_LayerParam         *world
	);

	AE_Error (*DisposeWorld) (
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         *world
	);

	AE_Error (*IterateOrigin) (
		AE_InData               *in_data,
		int                     progress_base,
		int                     progress_final,
		AE_LayerParam           *src,
		const AE_Rect           *area,
		const AE_PointParam     *origin,
		void                    *refcon,
		AE_IteratePixel8Func    pix_fn,
		AE_LayerParam           *dst
	);

	AE_Error (*IterateLUT) (
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

	AE_Error (*TransferRect) (
		AE_ProgressInfoPtr        effect_ref,
		int                       quality,
		AE_ModeFlags              m_flags,
		int                       field,
		const AE_Rect             *src_rec,
		const AE_LayerParam       *src_world,
		const AE_CompositeMode    *comp_mode,
		const AE_MaskWorld        *mask_world0,
		int                       dest_x,
		int                       dest_y,
		AE_LayerParam             *dst_world
	);

	AE_Error (*TransformWorld) (
		AE_ProgressInfoPtr        effect_ref,
		int                       quality,
		AE_ModeFlags              m_flags,
		int                       field,
		const AE_LayerParam       *src_world,
		const AE_CompositeMode    *comp_mode,
		const AE_MaskWorld        *mask_world0,
		const AE_FloatMatrix      *matrices,
		int                       num_matrices,
		AE_Boolean                src2dst_matrix,
		const AE_Rect             *dest_rect,
		AE_LayerParam             *dst_world
	);

	AE_Handle (*HostNewHandle) (
		unsigned long long    size
	);

	void * (*HostLockHandle) (
		AE_Handle    handle
	);

	void (*HostUnlockHandle) (
		AE_Handle    handle
	);

	void (*HostDisposeHandle) (
		AE_Handle    handle
	);

	AE_Error (*GetCallbackAddress) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Quality            quality,
		AE_ModeFlags          mode_flags,
		AE_CallbackID         which_callback,
		AE_CallbackFunc       *fn_ptr
	);

	AE_Error (*App) (AE_ProgressInfoPtr, int, ...);  // 200-8*

	AE_ANSICallbacks     ansi;  // 208-160*
	AE_ColorCallbacks    colorCB;  // 368-64*

	AE_Error (*GetPlatformData) (
		AE_ProgressInfoPtr    effect_ref,
		AE_PlatDataID         which,
		void                  *data
	);

	unsigned long long (*HostGetHandleSize) (
		AE_Handle    handle
	);

	AE_Error (*IterateOriginNonClipSource) (
		AE_InData               *in_data,
		int                     progress_base,
		int                     progress_final,
		AE_LayerParam           *src,
		const AE_Rect           *area,
		const AE_PointParam     *origin,
		void                    *refcon,
		AE_IteratePixel8Func    pix_fn,
		AE_LayerParam           *dst
	);

	AE_Error (*IterateGeneric) (
		int     iterationsL,
		void    *refconPV,
		int     (*fn_func) (
			void *refconPV,
			int  thread_indexL,
			int  i,
			int  iterationsL
		)
	);

	AE_Error (*HostResizeHandle) (
		unsigned long long    new_sizeL,
		AE_Handle             *handlePH
	);

	AE_Error (*SubpixelSample16) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Fixed              x,
		AE_Fixed              y,
		const AE_SamplePB     *params,
		AE_Pixel16            *dst_pixel
	);

	AE_Error (*AreaSample16) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Fixed              x,
		AE_Fixed              y,
		const AE_SamplePB     *params,
		AE_Pixel16            *dst_pixel
	);

	AE_Error (*Fill16) (
		AE_ProgressInfoPtr    effect_ref,
		const AE_Pixel16      *color,
		const AE_Rect         *dst_rect,
		AE_LayerParam         *world
	);

	AE_Error (*PremultiplyColor16) (
		AE_ProgressInfoPtr    effect_ref,
		AE_LayerParam         *src,
		const AE_Pixel16      *color,
		int                   forward,
		AE_LayerParam         *dst
	);

	AE_Error (*Iterate16) (
		AE_InData                *in_data,
		int                      progress_base,
		int                      progress_final,
		AE_LayerParam            *src,
		const AE_Rect            *area,
		void                     *refcon,
		AE_IteratePixel16Func    pix_fn,
		AE_LayerParam            *dst
	);

	AE_Error (*IterateOrigin16) (
		AE_InData                *in_data,
		int                      progress_base,
		int                      progress_final,
		AE_LayerParam            *src,
		const AE_Rect            *area,
		const AE_PointParam      *origin,
		void                     *refcon,
		AE_IteratePixel16Func    pix_fn,
		AE_LayerParam            *dst
	);

	AE_Error (*IterateOriginNonClipSource16) (
		AE_InData                *in_data,
		int                      progress_base,
		int                      progress_final,
		AE_LayerParam            *src,
		const AE_Rect            *area,
		const AE_PointParam      *origin,
		void                     *refcon,
		AE_IteratePixel16Func    pix_fn,
		AE_LayerParam            *dst
	);

	AE_Error (*GetPixelData8) (
		AE_LayerParam    *worldP,
		AE_PixelPtr      pixelsP0,
		AE_Pixel         **pixPP
	);

	AE_Error (*GetPixelData16) (
		AE_LayerParam    *worldP,
		AE_PixelPtr      pixelsP0,
		AE_Pixel16       **pixPP
	);

	int				reserved[1];  // 544-4
};  // 552bytes

#pragma pack (pop, AE)
