#pragma once

#include "./macros.hh"
#include "./basic.hh"
#include "./layer_data.hh"



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
//* Angle Def
typedef struct {
	/* PARAMETER VALUE */
	PF_Fixed		value;		/* degrees with fixed point accuracy;
								 * this is NOT limited in range to 0 to 360.
								 */

	/* PARAMETER DESCRIPTION */
	PF_Fixed		dephault;

	/* Min and max values. Note!! Not supported for effect plugins.
	** Angle properties in effects are always unlimited in range.
	*/
	PF_Fixed		valid_min, valid_max;
} PF_AngleDef;

//* Checkbox Def
typedef struct {
	/* PARAMETER VALUE */
	PF_ParamValue		value;

	/* PARAMETER DESCRIPTION */
	PF_Boolean		dephault;
	char		reserved;	/* padding	*/
	short		reserved1;
	union {
		const char	*nameptr;
	} u;
} PF_CheckBoxDef;

//* Point Parameter

typedef struct {
	/* PARAMETER VALUE */
	PF_Fixed			x_value;
	PF_Fixed			y_value;

	/* PARAMETER DESCRIPTION */
	char				reserved[3];
	PF_Boolean			restrict_bounds;		/* restrict bounds to size of src */
	PF_Fixed			x_dephault;				/* percentage */
	PF_Fixed			y_dephault;				/* percentage */
} PF_PointDef;

//* Popup Menu
typedef struct {
	/* PARAMETER VALUE */
	PF_ParamValue	value;

	/* PARAMETER DESCRIPTION */
	short		num_choices;
	short		dephault;
	union {
		const char	*namesptr; /*  menu manager standard, '|' separator */
	} u;
} PF_PopupDef;

//* Floating Point Slider Parameter
typedef float PF_FpShort;
typedef unsigned int PF_FSliderFlags;



typedef void **PF_Handle;
//* Arbitrary
typedef PF_Handle PF_ArbitraryH;
typedef struct {
	short					id;			/* for effect use: lets effect distinguish between */
										/*	different arbitrary data param types in the same effect */
	short					pad;		/* padding, set to zero */
	PF_ArbitraryH			dephault;	/* becomes owned by host at ADD_PARAM time */
	PF_ArbitraryH			value;		/* pass NULL at ADD_PARAM time; owned by host at render time */
	void					*refconPV;	/* passed into all callbacks, for effect use */
} PF_ArbitraryDef;

//* Path
typedef unsigned int PF_PathID;
typedef struct PF_PathDef {

	/* PARAMETER VALUE */
	PF_PathID			path_id;		/* to be used with PF_CheckoutPath()
											note that path_id != PF_PathID_NONE does not
											guarantee that PF_CheckoutPath will return a
											valid path (it may have been deleted) */

	/* PARAMETER DESCRIPTION */
	int				reserved0;		/*  not currently used, set to zero */

	int				dephault;		/*	0 means that the default is NONE,
											other numbers are the 1-based index of the
											path, if the path doesn't exist, the
											path_idLu value will be PF_PathID_NONE.
										 */
} PF_PathDef;

//* Momentary Buttons
typedef struct {
	/* PARAMETER VALUE */
	PF_ParamValue	value;		// not used at this time

	union {
		const char	*namesptr; /* button name */
	} u;
} PF_ButtonDef;

//* 3D Point
typedef struct {
	/* PARAMETER VALUE */
	PF_FpLong			x_value;
	PF_FpLong			y_value;
	PF_FpLong			z_value;

	/* PARAMETER DESCRIPTION */
	PF_FpLong			x_dephault;				/* percentage of layer width; note: use 50 for halfway, not 0.5; this matches the old PF_PointDef behavior */
	PF_FpLong			y_dephault;				/* percentage of layer height */
	PF_FpLong			z_dephault;				/* percentage of layer _height_ (since typical layers are zero depth) */

	char				reserved[16];			/* set to zeros */
} PF_Point3DDef;





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

//* Out Data
typedef struct {
		#ifdef	LPOINT_RENAME_COMPONENTS
			int	x;
			int	y;
		#else
			int	h;
			int	v;
		#endif
	} PF_Point;
	typedef int PF_OutFlags;
enum {
	PF_OutFlag2_NONE = 0L,
																// which PF_Cmds each flag is relevant for:
	PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS	= 1L << 0,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_I_USE_3D_CAMERA					= 1L << 1,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_I_USE_3D_LIGHTS					= 1L << 2,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG= 1L << 3,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_I_AM_THREADSAFE					= 1L << 4,		// PF_Cmd_GLOBAL_SETUP (unused)
	PF_OutFlag2_CAN_COMBINE_WITH_DESTINATION	= 1L << 5,		// Premiere only (as of AE 6.0)
	PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS		= 1L << 6,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_REVEALS_ZERO_ALPHA				= 1L << 7,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_PRESERVES_FULLY_OPAQUE_PIXELS	= 1L << 8,		// Premiere only (as of AE 6.0)
	PF_OutFlag2_SUPPORTS_SMART_RENDER			= 1L << 10,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_RESERVED9						= 1L << 11,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_FLOAT_COLOR_AWARE				= 1L << 12,		// PF_Cmd_GLOBAL_SETUP, may require PF_OutFlag2_SUPPORTS_SMART_RENDER
	PF_OutFlag2_I_USE_COLORSPACE_ENUMERATION	= 1L << 13,		// PF_Cmd_GLOBAL_SETUP, not implemented in AE7 (may be impl in Premiere Pro)
	PF_OutFlag2_I_AM_DEPRECATED					= 1L << 14,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_PPRO_DO_NOT_CLONE_SEQUENCE_DATA_FOR_RENDER	= 1L << 15,		// PF_Cmd_GLOBAL_SETUP, Premiere only, CS4.1 and later
	PF_OutFlag2_RESERVED10						= 1L << 16,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_AUTOMATIC_WIDE_TIME_INPUT		= 1L << 17,		// PF_Cmd_GLOBAL_SETUP, falls back to PF_OutFlag_WIDE_TIME_INPUT if not PF_OutFlag2_SUPPORTS_SMART_RENDER
	PF_OutFlag2_I_USE_TIMECODE					= 1L << 18,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_DEPENDS_ON_UNREFERENCED_MASKS	= 1L << 19,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_OUTPUT_IS_WATERMARKED			= 1L << 20,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_I_MIX_GUID_DEPENDENCIES			= 1L << 21,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_AE13_5_THREADSAFE				= 1L << 22,		// PF_Cmd_GLOBAL_SETUP (unused)
	PF_OutFlag2_SUPPORTS_GET_FLATTENED_SEQUENCE_DATA	= 1L << 23,		// PF_Cmd_GLOBAL_SETUP, support required if both PF_OutFlag_SEQUENCE_DATA_NEEDS_FLATTENING and PF_OutFlag2_SUPPORTS_THREADED_RENDERING is set
	PF_OutFlag2_CUSTOM_UI_ASYNC_MANAGER			= 1L << 24,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_SUPPORTS_GPU_RENDER_F32			= 1L << 25,		// PF_Cmd_GLOBAL_SETUP, PF_Cmd_GPU_DEVICE_SETUP. Must also set PF_RenderOutputFlag_GPU_RENDER_POSSIBLE at pre-render to enable GPU rendering.
	PF_OutFlag2_RESERVED12						= 1L << 26,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_SUPPORTS_THREADED_RENDERING		= 1L << 27,		// PF_Cmd_GLOBAL_SETUP
	PF_OutFlag2_MUTABLE_RENDER_SEQUENCE_DATA_SLOWER = 1L << 28	// PF_Cmd_GLOBAL_SETUP
};
typedef int PF_OutFlags2;

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
	PF_Point			offset;
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
