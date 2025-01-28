#pragma once

#include "./macros.hh"
#include "./basic.hh"
#include "./layer_data.hh"
#include "./parameters/point.hh"



typedef int PF_ChangeFlags;
typedef int PF_ParamUIFlags;
typedef int PF_ParamType;

typedef int PF_ParamFlags;
typedef int PF_WorldFlags;

//* Slider Def
typedef int PF_ParamValue;


typedef int PF_Fixed;
//* Fixed Slide Def
typedef short PF_ValueDisplayFlags;
typedef char PF_Boolean;

typedef double PF_FpLong;

//* Floating Point Slider Parameter
typedef float PF_FpShort;
typedef unsigned int PF_FSliderFlags;



typedef void **PF_Handle;





typedef int PF_CustomEventFlags;
typedef int PF_UIAlignment;
struct _PF_CustomUIInfo {

	int					reserved;
	PF_CustomEventFlags		events;

	int				comp_ui_width;
	int				comp_ui_height;
	PF_UIAlignment		comp_ui_alignment;			// unused

	int				layer_ui_width;
	int				layer_ui_height;
	PF_UIAlignment		layer_ui_alignment;			// unused

	int				preview_ui_width;			// unused
	int				preview_ui_height;			// unused
	PF_UIAlignment		preview_ui_alignment;		// unused

};
typedef struct _PF_CustomUIInfo PF_CustomUIInfo;

typedef unsigned int	PF_UFixed;
typedef struct _PF_LayerAudio *PF_LayerAudio;
typedef void *PF_SndSamplePtr;













typedef short PF_SoundChannels;
typedef short PF_SoundFormat;
typedef short PF_SoundSampleSize;

enum {
	PF_MF_Alpha_PREMUL 		= 0,
	PF_MF_Alpha_STRAIGHT 	= (1L << 0)
};
typedef int PF_ModeFlags;
typedef	unsigned int PF_SampleEdgeBehav;
typedef int    PF_TransferMode;
typedef unsigned short	A_u_short;
typedef struct {
		PF_TransferMode     xfer;
		int				rand_seed;  // for PF_Xfer_DISSOLVE_RANDOMIZED
		unsigned char			opacity;	// 0 - 255
		PF_Boolean          rgb_only;   // ignored for PF_Xfer_MULTIPLY_ALPHA modes
		A_u_short			opacitySu;	// for deep color only
	} PF_CompositeMode;
typedef struct {
	PF_Fixed				x_radius;		/* radii are used for area sample, 0 for point sample */
	PF_Fixed				y_radius;
	PF_Fixed				area;			/* must fit in a Fixed; must be correct */
	LayerParam			*src;			/* the world to sample from */
	PF_SampleEdgeBehav		samp_behave;
	int					allow_asynch;	/* It's okay if I don't get the result until end_sampling */


	/* parameters needed for batch sampling & compositing, motion blur, etc. */

	int					motion_blur;	/* requires pointer to 2 starting points and 2 dxdy's */
	PF_CompositeMode		comp_mode;		/* compositing mode info */
    PF_PixelPtr           	mask0;     		/* per-pixel extra masking, before xfer mode */

	unsigned char			*fcm_table;
	unsigned char			*fcd_table;
	int 					reserved[8];	/* Set to zero at beginsampling */

} PF_SampPB;

typedef PF_TransferMode PF_XferMode;
typedef unsigned int PF_KernelFlags;
typedef int PF_MaskFlags;
enum {
	PF_Callback_NONE = 0,
	PF_Callback_BEGIN_SAMPLING,
	PF_Callback_SUBPIXEL_SAMPLE,
	PF_Callback_AREA_SAMPLE,
	PF_Callback_OBSOLETE0,
	PF_Callback_END_SAMPLING,
	PF_Callback_COMPOSITE_RECT,
	PF_Callback_BLEND,
	PF_Callback_CONVOLVE,
	PF_Callback_COPY,
	PF_Callback_FILL,
	PF_Callback_GAUSSIAN,
	PF_Callback_ITERATE,
	PF_Callback_PREMUL,
	PF_Callback_PREMUL_COLOR,
	PF_Callback_RGB_TO_HLS,
	PF_Callback_HLS_TO_RGB,
	PF_Callback_RGB_TO_YIQ,
	PF_Callback_YIQ_TO_RGB,
	PF_Callback_LUMINANCE,
	PF_Callback_HUE,
	PF_Callback_LIGHTNESS,
	PF_Callback_SATURATION,
	PF_Callback_NEW_WORLD,
	PF_Callback_DISPOSE_WORLD,
	PF_Callback_ITERATE_ORIGIN,
	PF_Callback_ITERATE_LUT,
	PF_Callback_TRANSFER_RECT,
	PF_Callback_TRANSFORM_WORLD,
	PF_Callback_ITERATE_ORIGIN_NON_CLIP_SRC,
	PF_Callback_ITERATE_GENERIC,
	PF_Callback_SUBPIXEL_SAMPLE16,
	PF_Callback_AREA_SAMPLE16,
	PF_Callback_FILL16,
	PF_Callback_PREMUL_COLOR16,
	PF_Callback_ITERATE16,
	PF_Callback_ITERATE_ORIGIN16,
	PF_Callback_ITERATE_ORIGIN_NON_CLIP_SRC16,
	PF_Callback_ITERATE_GENERIC_NO_MAX_THREADS,
	PF_Callback_ITERATE_NO_MAX_THREADS,
	PF_Callback_ITERATE_ORIGIN_NO_MAX_THREADS,
	PF_Callback_ITERATE_ORIGIN_NON_CLIP_SRC_NO_MAX_THREADS,
	PF_Callback_ITERATE16_NO_MAX_THREADS,
	PF_Callback_ITERATE_ORIGIN16_NO_MAX_THREADS,
	PF_Callback_ITERATE_ORIGIN_NON_CLIP_SRC16_NO_MAX_THREADS,
};
typedef int PF_CallbackID;
typedef struct PF_YouMustCastThisToActualFunctionType  *PF_CallbackFunc;
typedef struct {
	double	(*atan)(double);
	double	(*atan2)(double y, double x);	/* returns atan(y/x) - note param order! */
	double	(*ceil)(double);				/* returns next int above x */
	double	(*cos)(double);
	double	(*exp)(double);					/* returns e to the x power */
	double	(*fabs)(double);				/* returns absolute value of x */
	double	(*floor)(double);				/* returns closest int below x */
	double	(*fmod)(double x, double y);	/* returns x mod y */
	double	(*hypot)(double x, double y);	/* returns sqrt(x*x + y*y) */
	double	(*log)(double);					/* returns natural log of x */
	double	(*log10)(double);				/* returns log base 10 of x */
	double	(*pow)(double x, double y);		/* returns x to the y power */
	double	(*sin)(double);
	double	(*sqrt)(double);
	double	(*tan)(double);

	int (*sprintf)(char *, const char *, ...);
	char *	(*strcpy)(char *, const char *);

	double (*asin)(double);
	double (*acos)(double);

	int	ansi_procs[1];
} PF_ANSICallbacks;
typedef PF_Fixed	PF_HLS_Pixel[3];
typedef PF_Fixed	PF_RGB_Pixel[3];
typedef PF_Fixed	PF_YIQ_Pixel[3];
typedef struct {
	int (*RGBtoHLS)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		Pixel		*rgb,
		PF_HLS_Pixel	hls);

	int (*HLStoRGB)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		PF_HLS_Pixel	hls,
		Pixel		*rgb);

	int (*RGBtoYIQ)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		Pixel		*rgb,
		PF_YIQ_Pixel	yiq);

	int (*YIQtoRGB)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		PF_YIQ_Pixel	yiq,
		Pixel		*rgb);

	int (*Luminance)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		Pixel		*rgb,
		int			*lum100);		/* << 100 * luminance */

	int (*Hue)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		Pixel		*rgb,
		int			*hue);			/* << 0-255 maps to 0-360  */

	int (*Lightness)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		Pixel		*rgb,
		int			*lightness);		/* <<  goes from 0-255 */

	int (*Saturation)(
		ProgressInfoPtr		effect_ref,		/* reference from in_data */
		Pixel		*rgb,
		int			*saturation);		/* <<  goes from 0-255 */

} PF_ColorCallbacks;
enum {
	PF_PlatData_MAIN_WND = 0,			// windows only		(output data => HWND)
	PF_PlatData_EXE_FILE_PATH_DEPRECATED,			// deprecated in CS6. Use _W versions below
	PF_PlatData_RES_FILE_PATH_DEPRECATED,			// deprecated in CS6. Use _W versions below
	PF_PlatData_RES_REFNUM,				// deprecated in AE 2015. Use PF_PlatData_BUNDLE_REF instead
	PF_PlatData_RES_DLLINSTANCE,		// windows only		(output data => HANDLE)
	PF_PlatData_SP_PLUG_REF,			// unimplemented
	PF_PlatData_BUNDLE_REF,				// mac only			(output data => CFBundleRef)
	PF_PlatData_EXE_FILE_PATH_W,		// mac and windows	(output data => A_UTF16Char[AEFX_MAX_PATH])
	PF_PlatData_RES_FILE_PATH_W			//// mac and windows	(output data => A_UTF16Char[AEFX_MAX_PATH])
};

typedef int PF_PlatDataID;
typedef unsigned __int64 	A_u_longlong;
typedef struct {
		#ifdef PF_PIXEL16_RENAME_COMPONENTS
			// this style is useful for debugging code converted from 8 bit
			A_u_short		alphaSu, redSu, greenSu, blueSu;
		#else
			A_u_short		alpha, red, green, blue;
		#endif
	} PF_Pixel16;
typedef struct {
		PF_FpLong				mat[3][3];
	} PF_FloatMatrix;
typedef struct {

	LayerParam		mask;
	AE_PointParam			offset;
	PF_MaskFlags		what_is_mask;

} PF_MaskWorld;

typedef int PF_NewWorldFlags;
typedef int (*PF_IteratePixel16Func)	(	void* refconP,					/* >> see comment above !! */
											int xL,						/* >> */
											int yL,						/* >> */
											PF_Pixel16 *inP,				/* <> */
											PF_Pixel16 *outP);				/* <> */
typedef int (*PF_IteratePixel8Func)	(	void* refconP,					/* >> see comment above !! */
											int xL,						/* >> */
											int yL,						/* >> */
											Pixel *inP,					/* <> */
											Pixel *outP);				/* <> */

typedef int32_t AE_ParamIndex;
typedef int32_t AE_ChannelIndex;
typedef int32_t AE_DataType;

/**
 * @brief (A_Long PF_ChannelIndex)
 * @brief for enumerating over all the channels
 */
typedef int32_t AE_ChannelType;

/**
 * @struct AE_ChannelRef
 * @brief (PF_ChannelRef)
 * @brief the opaque type representing the channel data
 */
typedef struct {
	intptr_t opaque[8];
} AE_ChannelRef, *AE_ChannelRefPtr;

/**
 * @struct AE_ChannelDescription
 * @brief (PF_ChannelDesc)
 */
typedef struct {
	AE_ChannelType channel_type;
	char           name[64];
	AE_DataType    data_type;
	int32_t        dimension;  // the number of data per pixel
} AE_ChannelDescription;

typedef struct {
	AE_ChannelRef channel_ref;
	int32_t       widthL;
	int32_t       heightL;
	int32_t       dimensionL;
	int32_t       row_bytesL;
	AE_DataType   data_type;
	PF_Handle     dataH;
	void          *dataPV;
} AE_ChannelChunk;
