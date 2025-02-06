#include "utility_callbacks_factory.hh"

UtilityCallbackFactory::UtilityCallbackFactory() {}
UtilityCallbackFactory::~UtilityCallbackFactory() {}

_AE_UtilCallbacks * UtilityCallbackFactory::Create() {
	_AE_UtilCallbacks *product = new _AE_UtilCallbacks();

	//* Call this routine before you plan to perform a large number of image resamplings.
	//* Depending on platform, this routine could start up the DSP chip, compute an index table to each scanline of the buffer, or whatever might be needed to speed up image resampling.
	product->BeginSampling = [](
		AE_ProgressInfoPtr effect_ref,
		int qual,
		AE_ModeFlags mf,
		AE_SamplePB *params
	) -> AE_Error {
		AE_Error error = AE_Error::NONE;
		AE_SamplePB *pb = new AE_SamplePB();

		LOG_DEBUG ("Called: UtilityCallbacks::BeginSampling (");
		LOG_DEBUG ("    from: 0x" << effect_ref);
		LOG_DEBUG ("    qual: " << qual);
		LOG_DEBUG ("    mf: " << NAMEOF_ENUM(mf));
		LOG_DEBUG (") => (");
		LOG_DEBUG ("    params: " << pb);
		LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

		params = pb;

		return error;
	};

	//* Use this to interpolate the appropriate alpha weighted mix of colors at a non-integral point in a source image, in high quality.
	//*	Nearest neighbor sample is used in low quality.
	product->SubpixelSample = [](
		AE_ProgressInfoPtr    effect_ref,
		AE_Fixed              x,
		AE_Fixed              y,
		const AE_SamplePB     *params,
		AE_Pixel              *dst_pixel
	) -> AE_Error {
		AE_Error error = AE_Error::NONE;

		AE_SamplePB *pb    = new AE_SamplePB();
		AE_Pixel    *pixel = new AE_Pixel();

		LOG_DEBUG ("Called: _AE_UtilCallbacks::SubpixelSample (");
		LOG_DEBUG ("    from: 0x" << effect_ref);
		LOG_DEBUG ("    x: " << x);
		LOG_DEBUG ("    y: " << y);
		LOG_DEBUG (") => (");
		LOG_DEBUG ("    params: " << params);
		LOG_DEBUG ("    dst_pixel: " << dst_pixel);
		LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

		return error;
	};

	//* Use this to calculate the appropriate alpha weighted average of an axis-aligned non-integral rectangle of color in a source image, in high quality.
	//* Nearest neighbor in low quality.
	//* Because of overflow issues, this can only average a maximum of a 256 pixel by 256 pixel area (ie. x and y range < 128 pixels).
	product->AreaSample = [] (
		AE_ProgressInfoPtr    effect_ref,
		AE_Fixed              x,
		AE_Fixed              y,
		const AE_SamplePB     *params,
		AE_Pixel              *dst_pixel
	) -> AE_Error {
		AE_Error error = AE_Error::NONE;

		AE_SamplePB *param = new AE_SamplePB();
		AE_Pixel    *pixel = new AE_Pixel();

		LOG_DEBUG ("Called: UtilityCallbacks::AreaSample (");
		LOG_DEBUG ("    from: 0x" << effect_ref);
		LOG_DEBUG ("    x: " << x);
		LOG_DEBUG ("    y: " << y);
		LOG_DEBUG (") => (");
		LOG_DEBUG ("    params: " << param);
		LOG_DEBUG ("    dst_pixel: " << pixel);
		LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

		return error;
	};

	product->EndSampling = [] (
		AE_ProgressInfoPtr effect_ref,
		int qual,
		AE_ModeFlags mf,
		AE_SamplePB *params
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.end_sampling\"");
		return AE_Error::NONE;
	};

	product->CompositeRect = [] (
		AE_ProgressInfoPtr effect_ref,
		AE_Rect *src_rect,
		int src_opacity,
		AE_LayerParam *source_wld,
		int dest_x,
		int dest_y,
		int field_rdr,
		AE_XferMode xfer_mode,
		AE_LayerParam *dest_wld
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.composite_rect\"");
		return AE_Error::NONE;
	};

	product->Blend = [](
		AE_ProgressInfoPtr effect_ref,
		const AE_LayerParam *src1,
		const AE_LayerParam *src2,
		AE_Fixed ratio,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.blend\"");
		return AE_Error::NONE;
	};

	product->Convolve = [](
		AE_ProgressInfoPtr effect_ref,
		AE_LayerParam *src,
		const AE_Rect *area,
		AE_KernelFlags flags,
		int kernel_size,
		void *a_kernel,
		void *r_kernel,
		void *g_kernel,
		void *b_kernel,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.convolve\"");
		return AE_Error::NONE;
	};

	product->Copy = [](
		AE_ProgressInfoPtr effect_ref,
		AE_LayerParam *src,
		AE_LayerParam *dst,
		AE_Rect *src_rect,
		AE_Rect *dst_rect
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.copy\"");
		return AE_Error::NONE;
	};

	product->Fill = [](
		AE_ProgressInfoPtr effect_ref,
		const AE_Pixel *color,
		const AE_Rect *destination_rect,
		AE_LayerParam *world
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.fill\"");
		return AE_Error::NONE;
	};

	product->GaussianKernel = [](
		AE_ProgressInfoPtr effect_ref,
		double kRadius,
		AE_KernelFlags flags,
		double multiplier,
		int *diameter,
		void *kernel
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.gaussian_kernel\"");
		return AE_Error::NONE;
	};

	product->Iterate = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		void *refcon,
		AE_IteratePixel8Func pixel_function,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.iterate\"");
		return AE_Error::NONE;
	};

	product->Premultiply = [](
		AE_ProgressInfoPtr effect_ref,
		int forward,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.premultiply\"");
		return AE_Error::NONE;
	};

	product->PremultiplyColor = [](
		AE_ProgressInfoPtr effect_ref,
		AE_LayerParam *src,
		const AE_Pixel *color,
		int forward,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.premultiply_color\"");
		return AE_Error::NONE;
	};

	product->NewWorld = [](
		AE_ProgressInfoPtr effect_ref,
		int width,
		int height,
		AE_NewWorldFlags flags,
		AE_LayerParam *world
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.new_world\"");
		return AE_Error::NONE;
	};

	product->DisposeWorld = [](
		AE_ProgressInfoPtr effect_ref,
		AE_LayerParam *world
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.dispose_world\"");
		return AE_Error::NONE;
	};

	product->IterateOrigin = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		const AE_PointParam *origin,
		void *refcon,
		AE_IteratePixel8Func pix_fn,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.iterate_origin\"");
		return AE_Error::NONE;
	};

	product->IterateLUT = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		unsigned char *a_lut0,
		unsigned char *r_lut0,
		unsigned char *g_lut0,
		unsigned char *b_lut0,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.iterate_lut\"");
		return AE_Error::NONE;
	};

	product->TransferRect = [](
		AE_ProgressInfoPtr effect_ref,
		int quality,
		AE_ModeFlags m_flags,
		int field,
		const AE_Rect *src_rec,
		const AE_LayerParam *src_world,
		const AE_CompositeMode *comp_mode,
		const AE_MaskWorld *mask_world0,
		int dest_x,
		int dest_y,
		AE_LayerParam *dst_world
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.transfer_rect\"");
		return AE_Error::NONE;
	};

	product->TransformWorld = [](
		AE_ProgressInfoPtr effect_ref,
		int quality,
		AE_ModeFlags m_flags,
		int field,
		const AE_LayerParam *src_world,
		const AE_CompositeMode *comp_mode,
		const AE_MaskWorld *mask_world0,
		const AE_FloatMatrix *matrices,
		int num_matrices,
		AE_Boolean src2dst_matrix,
		const AE_Rect *dest_rect,
		AE_LayerParam *dst_world
	) -> AE_Error {
		LOG_INFO ("Called \"_AE_UtilCallbacks.transform_world\"");
		return AE_Error::NONE;
	};

	product->HostNewHandle = [](
		unsigned long long size
	) -> AE_Handle {
		LOG_INFO ("Called \"_AE_UtilCallbacks.host_new_handle\"");
		return NULL;
	};

	product->HostLockHandle = [](
		AE_Handle handle
	) -> void * {
		LOG_INFO ("Called \"_AE_UtilCallbacks.host_lock_handle\"");
		return NULL;
	};

	product->HostUnlockHandle = [](
		AE_Handle handle
	) -> void {
		LOG_INFO ("Called \"_AE_UtilCallbacks.host_lock_handle\"");
	};

	product->HostDisposeHandle = [](
		AE_Handle handle
	) -> void {
		LOG_INFO ("Called \"_AE_UtilCallbacks.host_lock_handle\"");
	};

	product->GetCallbackAddress = [] (
		AE_ProgressInfoPtr    effect_ref,
		AE_Quality            quality,
		AE_ModeFlags          mode_flags,
		AE_CallbackID         which_callback,
		AE_CallbackFunc       *fn_ptr
	) -> AE_Error {
		AE_Error error = AE_Error::NONE;

		LOG_DEBUG ("Called: _AE_UtilCallbacks::GetCallbackAddress");
		LOG_DEBUG ("    from: 0x"         << effect_ref);
		LOG_DEBUG ("    quality: "        << NAMEOF_ENUM(quality));
		LOG_DEBUG ("    mode_flags: "     << NAMEOF_ENUM_FLAG(mode_flags));
		LOG_DEBUG ("    which_callback: " << NAMEOF_ENUM(which_callback));
		LOG_DEBUG ("    fn_ptr: "         << fn_ptr);
		LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

		return error;
	};

	product->App = [] (
		AE_ProgressInfoPtr effect_ref,
		int args,
		...
	) -> AE_Error {
		AE_Error error = AE_Error::NONE;

		LOG_DEBUG ("Called _AE_UtilCallbacks::App (");
		LOG_DEBUG ("    from: " << effect_ref);
		LOG_DEBUG ("    args: " << args);
		LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

		return error;
	};

	product->ansi = AE_ANSICallbacks();

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
		LOG_INFO ("asin: " << x);
		return 0;
	};

	product->ansi.acos = [](double x) -> double {
		LOG_INFO ("acos: " << x);
		return 0;
	};

	product->ansi.atan = [](double x) -> double {
		LOG_INFO ("atan: " << x);
		return 0;
	};

	product->ansi.atan2 = [](double y, double x) -> double {
		LOG_INFO ("atan2: " << x);
		return 0;
	};

	product->ansi.log = [](double x) -> double {
		LOG_INFO ("log10: " << x);
		return 0;
	};

	product->ansi.log10 = [](double x) -> double {
		LOG_INFO ("log10: " << x);
		return 0;
	};

	product->ansi.ceil = [](double x) -> double {
		LOG_INFO ("ceil: " << x);
		return 0;
	};

	product->ansi.exp = [](double x) -> double {
		LOG_INFO ("exp: " << x);
		return 0;
	};

	product->ansi.fabs = [](double x) -> double {
		LOG_INFO ("fabs: " << x);
		return 0;
	};

	product->ansi.floor = [](double x) -> double {
		LOG_INFO ("floor: " << x);
		return 0;
	};

	product->ansi.fmod = [](double x, double y) -> double {
		LOG_INFO ("fmod: " << x);
		return 0;
	};

	product->ansi.hypot = [](double x, double y) -> double {
		LOG_INFO ("hypot: " << x);
		return 0;
	};

	product->ansi.pow = [](double x, double y) -> double {
		LOG_INFO ("pow: " << x << ", " << y);
		return pow (x, y);
	};

	product->ansi.sqrt = [](double x) -> double {
		LOG_INFO ("sqrt: " << x);
		return 0;
	};

	product->ansi.sprintf = [](char *buffer, const char *format, ...) -> int {
		va_list args;
		va_start (args, format);

		vsnprintf (buffer, 1024, format, args);
		LOG_INFO (buffer);

		va_end (args);
		return 0;
	};

	product->ansi.strcpy = [](char *dest, const char *src) -> char * {
		strcpy (dest, src);
		LOG_INFO (dest);

		return 0;
	};

	product->colorCB = AE_ColorCallbacks();

	product->colorCB.RGBtoHLS = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Pixel *rgb,
		AE_HLS_Pixel hls
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.RGBtoHLS\"");
		return AE_Error::NONE;
	};

	product->colorCB.HLStoRGB = [](
		AE_ProgressInfoPtr effect_ref,
		AE_HLS_Pixel hls,
		AE_Pixel *rgb
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.HLStoRGB\"");
		return AE_Error::NONE;
	};

	product->colorCB.RGBtoYIQ = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Pixel *rgb,
		AE_YIQ_Pixel yiq
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.RGBtoYIQ\"");
		return AE_Error::NONE;
	};

	product->colorCB.YIQtoRGB = [](
		AE_ProgressInfoPtr effect_ref,
		AE_YIQ_Pixel yiq,
		AE_Pixel *rgb
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.YIQtoRGB\"");
		return AE_Error::NONE;
	};

	product->colorCB.Luminance = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Pixel *rgb,
		int *lum100
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.Luminance\"");
		return AE_Error::NONE;
	};

	product->colorCB.Hue = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Pixel *rgb,
		int *hue
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.Hue\"");
		return AE_Error::NONE;
	};

	product->colorCB.Lightness = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Pixel *rgb,
		int *lightness
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.Lightness\"");
		return AE_Error::NONE;
	};

	product->colorCB.Saturation = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Pixel *rgb,
		int *saturation
	) -> AE_Error {
		LOG_INFO ("Called \"AE_ColorCallbacks.Saturation\"");
		return AE_Error::NONE;
	};

	product->GetPlatformData = [] (
		AE_ProgressInfoPtr    effect_ref,
		AE_PlatDataID         which,
		void                  *data
	) -> AE_Error {
		AE_Error error = AE_Error::NONE;

		void *result = (void *)"D:/Projects/Development/Node/aexlo.js/test/plugins/DeepGlow2.aex";

		LOG_DEBUG ("Called: AE_InteractCallbacks::GetPlatformData (");
		LOG_DEBUG ("    from: 0x" << effect_ref);
		LOG_DEBUG ("    which: " << NAMEOF_ENUM(which));
		LOG_DEBUG (") => (");
		LOG_DEBUG ("    data: " << data);
		LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

		data = result;

		return error;
	};

	product->HostGetHandleSize = [](
		AE_Handle handle
	) -> unsigned long long {
		LOG_INFO ("Called \"AE_InteractCallbacks.host_get_handle_size\"");
		return 0;
	};

	product->IterateOriginNonClipSource = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		const AE_PointParam *origin,
		void *refcon,
		AE_IteratePixel8Func pix_fn,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.iterate_origin_non_clip_src\"");
		return AE_Error::NONE;
	};

	product->IterateGeneric = [](
		int iterationsL,
		void *refconPV,
		int (*fn_func) (
			void *refconPV,
			int thread_indexL,
			int i,
			int iterationsL
		)
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.iterate_generic\"");
		return AE_Error::NONE;
	};

	product->HostResizeHandle = [](
		unsigned long long new_sizeL,
		AE_Handle *handlePH
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.host_resize_handle\"");
		return AE_Error::NONE;
	};

	product->SubpixelSample16 = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Fixed x,
		AE_Fixed y,
		const AE_SamplePB *params,
		AE_Pixel16 *dst_pixel
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.subpixel_sample16\"");
		return AE_Error::NONE;
	};

	product->AreaSample16 = [](
		AE_ProgressInfoPtr effect_ref,
		AE_Fixed x,
		AE_Fixed y,
		const AE_SamplePB *params,
		AE_Pixel16 *dst_pixel
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.area_sample16\"");
		return AE_Error::NONE;
	};

	product->Fill16 = [](
		AE_ProgressInfoPtr effect_ref,
		const AE_Pixel16 *color,
		const AE_Rect *dst_rect,
		AE_LayerParam *world
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.fill16\"");
		return AE_Error::NONE;
	};

	product->PremultiplyColor16 = [](
		AE_ProgressInfoPtr effect_ref,
		AE_LayerParam *src,
		const AE_Pixel16 *color,
		int forward,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.premultiply_color16\"");
		return AE_Error::NONE;
	};

	product->Iterate16 = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		void *refcon,
		AE_IteratePixel16Func pix_fn,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.iterate16\"");
		return AE_Error::NONE;
	};

	product->IterateOrigin16 = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		const AE_PointParam *origin,
		void *refcon,
		AE_IteratePixel16Func pix_fn,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.iterate_origin16\"");
		return AE_Error::NONE;
	};

	product->IterateOriginNonClipSource16 = [](
		AE_InData *in_data,
		int progress_base,
		int progress_final,
		AE_LayerParam *src,
		const AE_Rect *area,
		const AE_PointParam *origin,
		void *refcon,
		AE_IteratePixel16Func pix_fn,
		AE_LayerParam *dst
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.iterate_origin_non_clip_src16\"");
		return AE_Error::NONE;
	};

	product->GetPixelData8 = [](
		AE_LayerParam *worldP,
		AE_PixelPtr pixelsP0,
		AE_Pixel **pixPP
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.get_pixel_data8\"");
		return AE_Error::NONE;
	};

	product->GetPixelData16 = [](
		AE_LayerParam *worldP,
		AE_PixelPtr pixelsP0,
		AE_Pixel16 **pixPP
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.get_pixel_data16\"");
		return AE_Error::NONE;
	};

	auto reserved0 = [](
		AE_ProgressInfoPtr effect_ref,
		const AE_Pixel *color,
		const AE_Rect *dst_rect,
		AE_LayerParam *world
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.reserved[0]\"");
		return AE_Error::NONE;
	};

	return product;
}
