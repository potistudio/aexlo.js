#pragma once
#pragma pack (push, AE, 8)

#include "./errors.hh"
#include "./common.hh"
#include "./layer_data.hh"

typedef unsigned int AE_KernelFlags;

enum class AE_SampleEdgeBehavior : unsigned int {
	ZERO = 0L
};

enum class AE_MaskFlags : int {
	NONE      = 0,
	INVERTED  = 1L << 0,
	LUMINANCE = 1L << 1
};

struct AE_MaskWorld {
	AE_EffectWorld    mask;
	AE_Point          offset;
	AE_MaskFlags      what_is_mask;
};

struct AE_SamplePB {
	AE_Fixed x_radius;
	AE_Fixed y_radius;

	AE_Fixed area;
	AE_EffectWorld *src;

	AE_SampleEdgeBehavior samp_behave;
	int allow_async;

	int motion_blur;
	AE_CompositeMode comp_mode;
	AE_PixelPtr mask0;

	unsigned char *fcm_table;
	unsigned char *fcd_table;
	int reserved[8];
};

enum class AE_CallbackID : int {
	NONE = 0,
	BEGIN_SAMPLING,
	SUBPIXEL_SAMPLE,
	AREA_SAMPLE,
	OBSOLETE0,
	END_SAMPLING,
	COMPOSITE_RECT,
	BLEND,
	CONVOLVE,
	COPY,
	FILL,
	GAUSSIAN,
	ITERATE,
	PREMUL,
	PREMUL_COLOR,
	RGB_TO_HLS,
	HLS_TO_RGB,
	RGB_TO_YIQ,
	YIQ_TO_RGB,
	LUMINANCE,
	HUE,
	LIGHTNESS,
	SATURATION,
	NEW_WORLD,
	DISPOSE_WORLD,
	ITERATE_ORIGIN,
	ITERATE_LUT,
	TRANSFER_RECT,
	TRANSFORM_WORLD,
	ITERATE_ORIGIN_NON_CLIP_SRC,
	ITERATE_GENERIC,
	SUBPIXEL_SAMPLE16,
	AREA_SAMPLE16,
	FILL16,
	PREMUL_COLOR16,
	ITERATE16,
	ITERATE_ORIGIN16,
	ITERATE_ORIGIN_NON_CLIP_SRC16,
	ITERATE_GENERIC_NO_MAX_THREADS,
	ITERATE_NO_MAX_THREADS,
	ITERATE_ORIGIN_NO_MAX_THREADS,
	ITERATE_ORIGIN_NON_CLIP_SRC_NO_MAX_THREADS,
	ITERATE16_NO_MAX_THREADS,
	ITERATE_ORIGIN16_NO_MAX_THREADS,
	ITERATE_ORIGIN_NON_CLIP_SRC16_NO_MAX_THREADS,
};

/**
  * @details versions of AE_CallbackFunc were defined using varargs in attempt to enforce the effect_ref passed as the first argument to all callbacks.
  * @details actual host implementations are generally *not* varargs,
  * @details and on some platforms the calling conventions between normal C ABI and C varargs ABI are not compatible.
  * @details If your code is trying to call through a AE_CallbackFunc it is unsafe; with this definition it will now no longer compile.
  * @details To fix, cast to the proper API signature before calling.
  * @details Or better, use the extensive Suite implementations which are explicitly typed.
**/
typedef struct AE_YouMustCastThisToActualFunctionType  *AE_CallbackFunc;

enum class AE_PlatDataID : int {
	MAIN_WND = 0,
	EXE_FILE_PATH_DEPRECATED,
	RES_FILE_PATH_DEPRECATED,
	RES_REFNUM,
	RES_DLLINSTANCE,
	SP_PLUG_REF,
	BUNDLE_REF,
	EXE_FILE_PATH_W,
	RES_FILE_PATH_W
};

enum class AE_Plane : unsigned int {
	ALPHA = 1,
	RED   = 2,
	GREEN = 4,
	BLUE  = 8
};

/**
 * @brief ANSI Routines Block
 *
 * @details Within the callback routines block there is a block of ANSI routines,
 * @details so that the filter will not need to link with the ANSI library.
 * @details The following structure describes that block and is included in the larger Callback Routines block below.
 *
 * @details All angles are expressed in radians; use AE_RAD_PER_DEGREE to convert from degrees to radians, if necessary.
 * @details Be aware that angle parameter types use degrees (in fixed point).
 *
 * @details Sprintf and strcpy are provided to facilitate string usage,
 * @details such as printing for names and supervised controls.
 *
 * @details None of these callbacks vary based on the Quality setting.
 */
struct AE_ANSICallbacks {
	double (*atan) (double);
	double (*atan2) (double y, double x);
	double (*ceil) (double);
	double (*cos) (double);
	double (*exp) (double);
	double (*fabs) (double);
	double (*floor) (double);
	double (*fmod) (double x, double y);
	double (*hypot) (double x, double y);
	double (*log )(double);
	double (*log10) (double);
	double (*pow )(double x, double y);
	double (*sin) (double);
	double (*sqrt) (double);
	double (*tan) (double);
	int (*sprintf) (char *, const char *, ...);
	char * (*strcpy) (char *, const char *);
	double (*asin) (double);
	double (*acos) (double);  // 144-8*

	int	ansi_procs[1];  // 152-4
};  // 160bytes

/**
 * @brief Colorspace Conversion Callbacks
 */
struct AE_ColorCallbacks {
	AE_Error (*RGBtoHLS) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Pixel              *rgb,
		AE_HLS_Pixel          hls
	);

	AE_Error (*HLStoRGB) (
		AE_ProgressInfoPtr    effect_ref,
		AE_HLS_Pixel          hls,
		AE_Pixel              *rgb
	);

	AE_Error (*RGBtoYIQ) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Pixel              *rgb,
		AE_YIQ_Pixel          yiq
	);

	AE_Error (*YIQtoRGB) (
		AE_ProgressInfoPtr    effect_ref,
		AE_YIQ_Pixel          yiq,
		AE_Pixel              *rgb
	);

	AE_Error (*Luminance) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Pixel              *rgb,
		int                   *lum100
	);

	AE_Error (*Hue) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Pixel              *rgb,
		int                   *hue
	);

	AE_Error (*Lightness) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Pixel              *rgb,
		int                   *lightness
	);

	AE_Error (*Saturation) (
		AE_ProgressInfoPtr    effect_ref,
		AE_Pixel              *rgb,
		int                   *saturation
	);
};  // 64bytes

typedef void *AE_BatchSampleFunc;
typedef void *AE_BatchSample16Func;

enum class AE_NewWorldFlags : int {
	NONE         = 0,
	CLEAR_PIXELS = 1L << 0,
	DEEP_PIXELS  = 1L << 1,
	RESERVED0    = 1L << 2,
	RESERVED1    = 1L << 3
};

typedef AE_Error (*AE_IteratePixel8Func) (
	void        *refconP,
	int         xL,
	int         yL,
	AE_Pixel    *inP,
	AE_Pixel    *outP
);

typedef AE_Error (*AE_IteratePixel16Func) (
	void       *refconP,
	int        xL,
	int        yL,
	AE_Pixel16 *inP,
	AE_Pixel16 *outP
);

typedef AE_Error (*AE_IteratePixelFloatFunc) (
	void          *refconP,
	int           xL,
	int           yL,
	AE_PixelFloat *inP,
	AE_PixelFloat *outP
);

#pragma pack (pop, AE)
