#include "utility_callbacks_factory.hh"

UtilityCallbackFactory::UtilityCallbackFactory() {}
UtilityCallbackFactory::~UtilityCallbackFactory() {}

_PF_UtilCallbacks * UtilityCallbackFactory::Create() {
	_PF_UtilCallbacks *product = new _PF_UtilCallbacks();

	product->begin_sampling = [](
		ProgressInfoPtr effect_ref,
		int qual,
		PF_ModeFlags mf,
		PF_SampPB *params
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.begin_sampling\"" << std::endl;
		return 0;
	};

	product->subpixel_sample = [](
		ProgressInfoPtr effect_ref,
		PF_Fixed x,
		PF_Fixed y,
		const PF_SampPB *params,
		Pixel *dst_pixel
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.subpixel_sample\"" << std::endl;
		return 0;
	};

	product->area_sample = [](
		ProgressInfoPtr effect_ref,
		PF_Fixed x,
		PF_Fixed y,
		const PF_SampPB *params,
		Pixel *dst_pixel
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.area_sample\"" << std::endl;
		return 0;
	};

	product->end_sampling = [](
		ProgressInfoPtr effect_ref,
		int qual,
		PF_ModeFlags mf,
		PF_SampPB *params
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.end_sampling\"" << std::endl;
		return 0;
	};

	product->composite_rect = [](
		ProgressInfoPtr effect_ref,
		PF_Rect *src_rect,
		int src_opacity,
		LayerParam *source_wld,
		int dest_x,
		int dest_y,
		int field_rdr,
		PF_XferMode xfer_mode,
		LayerParam *dest_wld
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.composite_rect\"" << std::endl;
		return 0;
	};

	product->blend = [](
		ProgressInfoPtr effect_ref,
		const LayerParam *src1,
		const LayerParam *src2,
		PF_Fixed ratio,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.blend\"" << std::endl;
		return 0;
	};

	product->convolve = [](
		ProgressInfoPtr effect_ref,
		LayerParam *src,
		const PF_Rect *area,
		PF_KernelFlags flags,
		int kernel_size,
		void *a_kernel,
		void *r_kernel,
		void *g_kernel,
		void *b_kernel,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.convolve\"" << std::endl;
		return 0;
	};

	product->copy = [](
		ProgressInfoPtr effect_ref,
		LayerParam *src,
		LayerParam *dst,
		PF_Rect *src_rect,
		PF_Rect *dst_rect
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.copy\"" << std::endl;
		return 0;
	};

	product->fill = [](
		ProgressInfoPtr effect_ref,
		const Pixel *color,
		const PF_Rect *destination_rect,
		LayerParam *world
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.fill\"" << std::endl;
		return 0;
	};

	product->gaussian_kernel = [](
		ProgressInfoPtr effect_ref,
		double kRadius,
		PF_KernelFlags flags,
		double multiplier,
		int *diameter,
		void *kernel
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.gaussian_kernel\"" << std::endl;
		return 0;
	};

	product->iterate = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area,
		void *refcon,
		PF_IteratePixel8Func pixel_function,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.iterate\"" << std::endl;
		return 0;
	};

	product->premultiply = [](
		ProgressInfoPtr effect_ref,
		int forward,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.premultiply\"" << std::endl;
		return 0;
	};

	product->premultiply_color = [](
		ProgressInfoPtr effect_ref,
		LayerParam *src,
		const Pixel *color,
		int forward,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.premultiply_color\"" << std::endl;
		return 0;
	};

	product->new_world = [](
		ProgressInfoPtr effect_ref,
		int width,
		int height,
		PF_NewWorldFlags flags,
		LayerParam *world
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.new_world\"" << std::endl;
		return 0;
	};

	product->dispose_world = [](
		ProgressInfoPtr effect_ref,
		LayerParam *world
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.dispose_world\"" << std::endl;
		return 0;
	};

	product->iterate_origin = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area,
		const PF_Point *origin,
		void *refcon,
		PF_IteratePixel8Func pix_fn,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.iterate_origin\"" << std::endl;
		return 0;
	};

	product->iterate_lut = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area,
		unsigned char *a_lut0,
		unsigned char *r_lut0,
		unsigned char *g_lut0,
		unsigned char *b_lut0,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.iterate_lut\"" << std::endl;
		return 0;
	};

	product->transfer_rect = [](
		ProgressInfoPtr effect_ref,
		int quality,
		PF_ModeFlags m_flags,
		int field,
		const PF_Rect *src_rec,
		const LayerParam *src_world,
		const PF_CompositeMode *comp_mode,
		const PF_MaskWorld *mask_world0,
		int dest_x,
		int dest_y,
		LayerParam *dst_world
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.transfer_rect\"" << std::endl;
		return 0;
	};

	product->transform_world = [](
		ProgressInfoPtr effect_ref,
		int quality,
		PF_ModeFlags m_flags,
		int field,
		const LayerParam *src_world,
		const PF_CompositeMode *comp_mode,
		const PF_MaskWorld *mask_world0,
		const PF_FloatMatrix *matrices,
		int num_matrices,
		PF_Boolean src2dst_matrix,
		const PF_Rect *dest_rect,
		LayerParam *dst_world
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.transform_world\"" << std::endl;
		return 0;
	};

	product->host_new_handle = [](
		A_u_longlong size
	) -> PF_Handle {
		std::cout << "Called \"_PF_UtilCallbacks.host_new_handle\"" << std::endl;
		return NULL;
	};

	product->host_lock_handle = [](
		PF_Handle pf_handle
	) -> void * {
		std::cout << "Called \"_PF_UtilCallbacks.host_lock_handle\"" << std::endl;
		return NULL;
	};

	product->host_unlock_handle = [](
		PF_Handle pf_handle
	) -> void {
		std::cout << "Called \"_PF_UtilCallbacks.host_lock_handle\"" << std::endl;
	};

	product->host_dispose_handle = [](
		PF_Handle pf_handle
	) -> void {
		std::cout << "Called \"_PF_UtilCallbacks.host_lock_handle\"" << std::endl;
	};

	product->get_callback_addr = [](
		ProgressInfoPtr effect_ref,
		int quality,
		PF_ModeFlags mode_flags,
		PF_CallbackID which_callback,
		PF_CallbackFunc *fn_ptr
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.get_callback_addr\"" << std::endl;
		return 0;
	};

	product->app = [](
		ProgressInfoPtr,
		int,
		...
	) -> int {
		std::cout << "Called \"_PF_UtilCallbacks.app\"" << std::endl;
		return 0;
	};

	product->ansi = PF_ANSICallbacks();

	product->ansi.sin = [](double x) -> double {
		return sin (x);
	};

	product->ansi.cos = [](double x) -> double {
		return cos (x);
	};

	product->ansi.tan = [](double x) -> double {
		return tan (x);
	};

	product->ansi.asin = [](double x) -> double {
		std::cout << "asin: " << x << std::endl;
		return 0;
	};

	product->ansi.acos = [](double x) -> double {
		std::cout << "acos: " << x << std::endl;
		return 0;
	};

	product->ansi.atan = [](double x) -> double {
		std::cout << "atan: " << x << std::endl;
		return 0;
	};

	product->ansi.atan2 = [](double y, double x) -> double {
		std::cout << "atan2: " << x << std::endl;
		return 0;
	};

	product->ansi.log = [](double x) -> double {
		std::cout << "log10: " << x << std::endl;
		return 0;
	};

	product->ansi.log10 = [](double x) -> double {
		std::cout << "log10: " << x << std::endl;
		return 0;
	};

	product->ansi.ceil = [](double x) -> double {
		std::cout << "ceil: " << x << std::endl;
		return 0;
	};

	product->ansi.exp = [](double x) -> double {
		std::cout << "exp: " << x << std::endl;
		return 0;
	};

	product->ansi.fabs = [](double x) -> double {
		std::cout << "fabs: " << x << std::endl;
		return 0;
	};

	product->ansi.floor = [](double x) -> double {
		std::cout << "floor: " << x << std::endl;
		return 0;
	};

	product->ansi.fmod = [](double x, double y) -> double {
		std::cout << "fmod: " << x << std::endl;
		return 0;
	};

	product->ansi.hypot = [](double x, double y) -> double {
		std::cout << "hypot: " << x << std::endl;
		return 0;
	};

	product->ansi.pow = [](double x, double y) -> double {
		std::cout << "pow: " << x << ", " << y << std::endl;
		return pow (x, y);
	};

	product->ansi.sqrt = [](double x) -> double {
		std::cout << "sqrt: " << x << std::endl;
		return 0;
	};

	product->ansi.sprintf = [](char *buffer, const char *format, ...) -> int {
		va_list args;
		va_start (args, format);

		vsnprintf (buffer, 1024, format, args);
		std::cout << buffer << std::endl;

		va_end (args);
		return 0;
	};

	product->ansi.strcpy = [](char *dest, const char *src) -> char * {
		strcpy (dest, src);
		std::cout << dest << std::endl;

		return 0;
	};

	product->colorCB = PF_ColorCallbacks();

	product->colorCB.RGBtoHLS = [](
		ProgressInfoPtr effect_ref,
		Pixel *rgb,
		PF_HLS_Pixel hls
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.RGBtoHLS\"" << std::endl;
		return 0;
	};

	product->colorCB.HLStoRGB = [](
		ProgressInfoPtr effect_ref,
		PF_HLS_Pixel hls,
		Pixel *rgb
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.HLStoRGB\"" << std::endl;
		return 0;
	};

	product->colorCB.RGBtoYIQ = [](
		ProgressInfoPtr effect_ref,
		Pixel *rgb,
		PF_YIQ_Pixel yiq
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.RGBtoYIQ\"" << std::endl;
		return 0;
	};

	product->colorCB.YIQtoRGB = [](
		ProgressInfoPtr effect_ref,
		PF_YIQ_Pixel yiq,
		Pixel *rgb
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.YIQtoRGB\"" << std::endl;
		return 0;
	};

	product->colorCB.Luminance = [](
		ProgressInfoPtr effect_ref,
		Pixel *rgb,
		int *lum100
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.Luminance\"" << std::endl;
		return 0;
	};

	product->colorCB.Hue = [](
		ProgressInfoPtr effect_ref,
		Pixel *rgb,
		int *hue
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.Hue\"" << std::endl;
		return 0;
	};

	product->colorCB.Lightness = [](
		ProgressInfoPtr effect_ref,
		Pixel *rgb,
		int *lightness
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.Lightness\"" << std::endl;
		return 0;
	};

	product->colorCB.Saturation = [](
		ProgressInfoPtr effect_ref,
		Pixel *rgb,
		int *saturation
	) -> int {
		std::cout << "Called \"PF_ColorCallbacks.Saturation\"" << std::endl;
		return 0;
	};

	product->get_platform_data = [](
		ProgressInfoPtr effect_ref,
		PF_PlatDataID which,
		void *data
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.get_platform_data\"" << std::endl;
		return 0;
	};

	product->host_get_handle_size = [](
		PF_Handle pf_handle
	) -> A_u_longlong {
		std::cout << "Called \"PF_InteractCallbacks.host_get_handle_size\"" << std::endl;
		return 0;
	};

	product->iterate_origin_non_clip_src = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area,
		const PF_Point *origin,
		void *refcon,
		PF_IteratePixel8Func pix_fn,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.iterate_origin_non_clip_src\"" << std::endl;
		return 0;
	};

	product->iterate_generic = [](
		int iterationsL, /* >> */		  // can be PF_Iterations_ONCE_PER_PROCESSOR
		void *refconPV,					  /* >> */
		int (*fn_func)(void *refconPV,	  /* >> */
					   int thread_indexL, // only call abort and progress from thread_indexL == 0.
					   int i,
					   int iterationsL)
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.iterate_generic\"" << std::endl;
		return 0;
	};

	product->host_resize_handle = [](
		A_u_longlong new_sizeL, /* >> */
		PF_Handle *handlePH
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.host_resize_handle\"" << std::endl;
		return 0;
	};

	product->subpixel_sample16 = [](
		ProgressInfoPtr effect_ref, /* reference from in_data */
		PF_Fixed x,
		PF_Fixed y,
		const PF_SampPB *params,
		PF_Pixel16 *dst_pixel
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.subpixel_sample16\"" << std::endl;
		return 0;
	};

	product->area_sample16 = [](
		ProgressInfoPtr effect_ref, /* reference from in_data */
		PF_Fixed x,
		PF_Fixed y,
		const PF_SampPB *params,
		PF_Pixel16 *dst_pixel
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.area_sample16\"" << std::endl;
		return 0;
	};

	product->fill16 = [](
		ProgressInfoPtr effect_ref, /* reference from in_data	*/
		const PF_Pixel16 *color,
		const PF_Rect *dst_rect, /* pass NULL for whole world */
		LayerParam *world
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.fill16\"" << std::endl;
		return 0;
	};

	product->premultiply_color16 = [](
		ProgressInfoPtr effect_ref, /* reference from in_data */
		LayerParam *src,
		const PF_Pixel16 *color, /* color to premultiply/unmultiply with */
		int forward,			 /* TRUE means convert non-premul to premul, FALSE mean reverse */
		LayerParam *dst
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.premultiply_color16\"" << std::endl;
		return 0;
	};

	product->iterate16 = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area, /* pass NULL for all pixels */
		void *refcon,
		PF_IteratePixel16Func pix_fn,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.iterate16\"" << std::endl;
		return 0;
	};

	product->iterate_origin16 = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area, /* pass NULL for all pixels */
		const PF_Point *origin,
		void *refcon,
		PF_IteratePixel16Func pix_fn,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.iterate_origin16\"" << std::endl;
		return 0;
	};

	product->iterate_origin_non_clip_src16 = [](
		PF_InData *in_data,
		int progress_base,
		int progress_final,
		LayerParam *src,
		const PF_Rect *area,
		const PF_Point *origin,
		void *refcon,
		PF_IteratePixel16Func pix_fn,
		LayerParam *dst
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.iterate_origin_non_clip_src16\"" << std::endl;
		return 0;
	};

	product->get_pixel_data8 = [](
		LayerParam *worldP,
		PF_PixelPtr pixelsP0, // NULL to use data in LayerParam
		Pixel **pixPP
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.get_pixel_data8\"" << std::endl;
		return 0;
	};

	product->get_pixel_data16 = [](
		LayerParam *worldP,
		PF_PixelPtr pixelsP0, // NULL to use data in LayerParam
		PF_Pixel16 **pixPP
	) -> int {
		std::cout << "Called \"PF_InteractCallbacks.get_pixel_data16\"" << std::endl;
		return 0;
	};

	return product;
}
