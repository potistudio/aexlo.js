
#include "Generic.h"
#include "SuiteDef.h"

#define PF_FIRST_ERR                    512
#define PF_MAX_EFFECT_MSG_LEN           255
#define PF_MAX_EFFECT_NAME_LEN          31
#define PF_MAX_EFFECT_PARAM_NAME_LEN    31
#define PF_MAX_PARAM_DESCRIPTION_LEN    31
#define PF_MAX_PARAM_VALUE_LEN          31

typedef A_long PF_Err;
enum {
	PF_Err_NONE = 0,
	PF_Err_OUT_OF_MEMORY = 4,
	PF_Err_INTERNAL_STRUCT_DAMAGED = PF_FIRST_ERR,
	PF_Err_INVALID_INDEX,
	PF_Err_UNRECOGNIZED_PARAM_TYPE,
	PF_Err_INVALID_CALLBACK,
	PF_Err_BAD_CALLBACK_PARAM,
	PF_Interrupt_CANCEL,
	PF_Err_CANNOT_PARSE_KEYFRAME_TEXT
};

typedef A_long PF_ParamIndex;

typedef A_long PF_ChangeFlags;
typedef A_long PF_ParamUIFlags;
typedef A_long PF_ParamType;

typedef A_long PF_ParamFlags;
typedef A_long PF_WorldFlags;
typedef struct {
	A_u_char alpha, red, green, blue;
} PF_Pixel;
typedef PF_Pixel *PF_PixelPtr;
typedef struct {
	A_long left, top, right, bottom;
} PF_LRect;
typedef PF_LRect PF_Rect;
typedef PF_Rect		PF_UnionableRect;
typedef struct {
		A_long		num;	/* numerator */
		A_u_long	den;	/* denominator */
	} PF_RationalScale;

typedef double A_FpLong;
//* Slider Def
typedef A_long PF_ParamValue;

typedef struct {
	/* PARAMETER VALUE */
	PF_ParamValue	value;
	A_char			value_str[PF_MAX_PARAM_VALUE_LEN + 1]; /* string for value */
	A_char			value_desc[PF_MAX_PARAM_DESCRIPTION_LEN + 1]; /* qualitative descr */

	/* PARAMETER DESCRIPTION */
	PF_ParamValue	valid_min, valid_max;		/* acceptable input range */
	PF_ParamValue	slider_min, slider_max;		/* range represented by width of slider */
	PF_ParamValue	dephault;
} PF_SliderDef;
typedef A_long PF_Fixed;
//* Fixed Slide Def
typedef A_short PF_ValueDisplayFlags;
typedef A_char PF_Boolean;
typedef struct {
	/* PARAMETER VALUE */
	PF_Fixed					value;
	A_char						value_str[PF_MAX_PARAM_VALUE_LEN + 1]; /* string for value */
	A_char						value_desc[PF_MAX_PARAM_DESCRIPTION_LEN + 1]; /* qualitative descr */

	/* PARAMETER DESCRIPTION */
	PF_Fixed					valid_min, valid_max;		/* acceptable input range */
	PF_Fixed					slider_min, slider_max;		/* range represented by width of slider */
	PF_Fixed					dephault;
	A_short						precision;					/* decimal places to display */
	PF_ValueDisplayFlags		display_flags;				/* set bit to 1 to enable special display:
												 *	--> bit 0 == append percent sign
												 */
} PF_FixedSliderDef;
typedef A_FpLong PF_FpLong;
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
	A_char		reserved;	/* padding	*/
	A_short		reserved1;
	union {
		const A_char	*nameptr;
	} u;
} PF_CheckBoxDef;
typedef void **PF_Handle;
//* Color Parameter
typedef PF_Pixel PF_UnionablePixel;
typedef struct {
	/* PARAMETER VALUE */
	PF_UnionablePixel	value;

	/* PARAMETER DESCRIPTION */
	PF_UnionablePixel	dephault;
} PF_ColorDef;

//* Point Parameter

typedef struct {
	/* PARAMETER VALUE */
	PF_Fixed			x_value;
	PF_Fixed			y_value;

	/* PARAMETER DESCRIPTION */
	A_char				reserved[3];
	PF_Boolean			restrict_bounds;		/* restrict bounds to size of src */
	PF_Fixed			x_dephault;				/* percentage */
	PF_Fixed			y_dephault;				/* percentage */
} PF_PointDef;

//* Popup Menu
typedef struct {
	/* PARAMETER VALUE */
	PF_ParamValue	value;

	/* PARAMETER DESCRIPTION */
	A_short		num_choices;
	A_short		dephault;
	union {
		const A_char	*namesptr; /*  menu manager standard, '|' separator */
	} u;
} PF_PopupDef;

//* Floating Point Slider Parameter
typedef float A_FpShort;
typedef A_FpShort PF_FpShort;
typedef A_u_long PF_FSliderFlags;
typedef struct {
	/* PARAMETER VALUE */
	PF_FpLong				value;
	PF_FpLong				phase;					/* used for PF_FSliderFlag_WANT_PHASE */
	A_char					value_desc[PF_MAX_PARAM_DESCRIPTION_LEN + 1]; /* qualitative descr */

	/* PARAMETER DESCRIPTION */
	PF_FpShort				valid_min, valid_max;		/* acceptable input range */
	PF_FpShort				slider_min, slider_max;		/* range represented by width of slider */
	PF_FpShort				dephault;
	A_short					precision;					/* decimal places to display */
	PF_ValueDisplayFlags	display_flags;				/* set bit to 1 to enable special display:
														 *	--> bit 0 == append percent sign
														 */
	PF_FSliderFlags			fs_flags;
	PF_FpShort				curve_tolerance;		/* used for subdividing audio effects
														set to zero for default, or non-audio */

														/* next 2 fields are used in Premiere Pro and ignored in AE */
	PF_Boolean				useExponent;				/* use exponential value display */
	PF_FpShort				exponent;					/* typical values from 0.01 to 100 */
} PF_FloatSliderDef;

//* Arbitrary
typedef PF_Handle PF_ArbitraryH;
typedef struct {
	A_short					id;			/* for effect use: lets effect distinguish between */
										/*	different arbitrary data param types in the same effect */
	A_short					pad;		/* padding, set to zero */
	PF_ArbitraryH			dephault;	/* becomes owned by host at ADD_PARAM time */
	PF_ArbitraryH			value;		/* pass NULL at ADD_PARAM time; owned by host at render time */
	void					*refconPV;	/* passed into all callbacks, for effect use */
} PF_ArbitraryDef;

//* Path
typedef A_u_long PF_PathID;
typedef struct PF_PathDef {

	/* PARAMETER VALUE */
	PF_PathID			path_id;		/* to be used with PF_CheckoutPath()
											note that path_id != PF_PathID_NONE does not
											guarantee that PF_CheckoutPath will return a
											valid path (it may have been deleted) */

	/* PARAMETER DESCRIPTION */
	A_long				reserved0;		/*  not currently used, set to zero */

	A_long				dephault;		/*	0 means that the default is NONE,
											other numbers are the 1-based index of the
											path, if the path doesn't exist, the
											path_idLu value will be PF_PathID_NONE.
										 */
} PF_PathDef;
struct PF_ProgressInfo;
typedef struct PF_ProgressInfo *PF_ProgPtr;
//* Momentary Buttons
typedef struct {
	/* PARAMETER VALUE */
	PF_ParamValue	value;		// not used at this time

	union {
		const A_char	*namesptr; /* button name */
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





typedef A_long PF_CustomEventFlags;
typedef A_long PF_UIAlignment;
struct _PF_CustomUIInfo {

	A_long					reserved;
	PF_CustomEventFlags		events;

	A_long				comp_ui_width;
	A_long				comp_ui_height;
	PF_UIAlignment		comp_ui_alignment;			// unused

	A_long				layer_ui_width;
	A_long				layer_ui_height;
	PF_UIAlignment		layer_ui_alignment;			// unused

	A_long				preview_ui_width;			// unused
	A_long				preview_ui_height;			// unused
	PF_UIAlignment		preview_ui_alignment;		// unused

};
typedef struct _PF_CustomUIInfo PF_CustomUIInfo;

typedef A_u_long	PF_UFixed;
typedef struct _PF_LayerAudio *PF_LayerAudio;
typedef void *PF_SndSamplePtr;




typedef A_long PF_Quality;
typedef struct {
	A_short		major;
	A_short		minor;
} PF_SpecVersion;
typedef A_long PF_Field;






typedef A_short PF_SoundChannels;
typedef A_short PF_SoundFormat;
typedef A_short PF_SoundSampleSize;
typedef struct {
	PF_FpLong				rateF;
	PF_SoundChannels		num_channels;
	PF_SoundFormat			format;
	PF_SoundSampleSize		sample_size;
} PF_SoundFormatInfo;
typedef struct {
	PF_SoundFormatInfo		fi;
	A_long					num_samples;
	void					*dataP;
} PF_SoundWorld;

typedef A_long PF_InFlags;

typedef PF_Pixel		PF_Pixel8;
//* Out Data
typedef struct {
		#ifdef	LPOINT_RENAME_COMPONENTS
			A_long	x;
			A_long	y;
		#else
			A_long	h;
			A_long	v;
		#endif
	} PF_Point;
	typedef A_long PF_OutFlags;
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
typedef A_long PF_OutFlags2;

//* Layer Definition
typedef struct PF_LayerDef {
	void                *reserved0;
	void                *reserved1;
	PF_WorldFlags       world_flags;
	PF_PixelPtr         data;
	A_long              rowbytes;
	A_long              width;
	A_long              height;
	PF_UnionableRect    extent_hint;
	void                *platform_ref;
	A_long              reserved_long1;
	void                *reserved_long4;
	PF_RationalScale    pix_aspect_ratio;
	void                *reserved_long2;
	A_long              origin_x;
	A_long              origin_y;
	A_long              reserved_long3;
	A_long              dephault;
} PF_LayerDef;

//* Parameter Definition Union
typedef union {
	PF_LayerDef          ld;
	PF_SliderDef         sd;
	PF_FixedSliderDef    fd;
	PF_AngleDef          ad;
	PF_CheckBoxDef       bd;
	PF_ColorDef          cd;
	PF_PointDef          td;
	PF_PopupDef          pd;
	PF_FloatSliderDef    fs_d;
	PF_ArbitraryDef      arb_d;
	PF_PathDef           path_d;
	PF_ButtonDef         button_d;
	PF_Point3DDef        point3d_d;
} PF_ParamDefUnion;

//* Param Def
typedef struct {
	union {
		A_long            id;
		PF_ChangeFlags    change_flags;
	} uu;

	PF_ParamUIFlags       ui_flags;
	A_short               ui_width;
	A_short               ui_height;
	PF_ParamType          param_type;
	A_char                name[PF_MAX_EFFECT_PARAM_NAME_LEN + 1];
	PF_ParamFlags         flags;
	A_long                unused;
	PF_ParamDefUnion      u;
} PF_ParamDef, *PF_ParamDefPtr, **PF_ParamDefH;

//* Interact Callbacks
typedef struct {
	PF_Err (*checkout_param) (
		PF_ProgPtr       effect_ref,
		PF_ParamIndex    index,
		A_long           what_time,
		A_long           time_step,
		A_u_long         time_scale,
		PF_ParamDef      *param
	);

	PF_Err (*checkin_param) (
		PF_ProgPtr     effect_ref,
		PF_ParamDef    *param
	);

	PF_Err (*add_param) (
		PF_ProgPtr        effect_ref,
		PF_ParamIndex     index,
		PF_ParamDefPtr    def
	);

	PF_Err (*abort) (
		PF_ProgPtr    effect_ref
	);

	PF_Err (*progress) (
		PF_ProgPtr    effect_ref,
		A_long        current,
		A_long        total
	);

	PF_Err (*register_ui) (
		PF_ProgPtr         effect_ref,
		PF_CustomUIInfo    *cust_info
	);

	PF_Err (*checkout_layer_audio) (
		PF_ProgPtr       effect_ref,
		PF_ParamIndex    index,
		A_long           start_time,
		A_long           duration,
		A_u_long         time_scale,
		PF_UFixed        rate,
		A_long           bytes_per_sample,
		A_long           num_channels,
		A_long           fmt_signed,
		PF_LayerAudio    *audio
	);

	PF_Err (*checkin_layer_audio) (
		PF_ProgPtr       effect_ref,
		PF_LayerAudio    audio
	);

	PF_Err (*get_audio_data) (
		PF_ProgPtr         effect_ref,
		PF_LayerAudio      audio,
		PF_SndSamplePtr    *data0,
		A_long             *num_samples0,
		PF_UFixed          *rate0,
		A_long             *bytes_per_sample0,
		A_long             *num_channels0,
		A_long             *fmt_signed0
	);

	void    *reserved_str[3];
	void    *reserved[10];
} PF_InteractCallbacks;

enum {
	PF_MF_Alpha_PREMUL 		= 0,
	PF_MF_Alpha_STRAIGHT 	= (1L << 0)
};
typedef A_long PF_ModeFlags;
typedef	A_u_long PF_SampleEdgeBehav;
typedef A_long    PF_TransferMode;
typedef unsigned short	A_u_short;
typedef struct {
		PF_TransferMode     xfer;
		A_long				rand_seed;  // for PF_Xfer_DISSOLVE_RANDOMIZED
		A_u_char			opacity;	// 0 - 255
		PF_Boolean          rgb_only;   // ignored for PF_Xfer_MULTIPLY_ALPHA modes
		A_u_short			opacitySu;	// for deep color only
	} PF_CompositeMode;
typedef PF_LayerDef		PF_EffectWorld;
typedef struct {
	PF_Fixed				x_radius;		/* radii are used for area sample, 0 for point sample */
	PF_Fixed				y_radius;
	PF_Fixed				area;			/* must fit in a Fixed; must be correct */
	PF_EffectWorld			*src;			/* the world to sample from */
	PF_SampleEdgeBehav		samp_behave;
	A_long					allow_asynch;	/* It's okay if I don't get the result until end_sampling */


	/* parameters needed for batch sampling & compositing, motion blur, etc. */

	A_long					motion_blur;	/* requires pointer to 2 starting points and 2 dxdy's */
	PF_CompositeMode		comp_mode;		/* compositing mode info */
    PF_PixelPtr           	mask0;     		/* per-pixel extra masking, before xfer mode */

	A_u_char			*fcm_table;
	A_u_char			*fcd_table;
	A_long 					reserved[8];	/* Set to zero at beginsampling */

} PF_SampPB;

typedef PF_TransferMode PF_XferMode;
typedef A_u_long PF_KernelFlags;
typedef A_long PF_MaskFlags;
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
typedef A_long PF_CallbackID;
typedef struct PF_YouMustCastThisToActualFunctionType  *PF_CallbackFunc;
typedef struct {
	A_FpLong	(*atan)(A_FpLong);
	A_FpLong	(*atan2)(A_FpLong y, A_FpLong x);	/* returns atan(y/x) - note param order! */
	A_FpLong	(*ceil)(A_FpLong);				/* returns next int above x */
	A_FpLong	(*cos)(A_FpLong);
	A_FpLong	(*exp)(A_FpLong);					/* returns e to the x power */
	A_FpLong	(*fabs)(A_FpLong);				/* returns absolute value of x */
	A_FpLong	(*floor)(A_FpLong);				/* returns closest int below x */
	A_FpLong	(*fmod)(A_FpLong x, A_FpLong y);	/* returns x mod y */
	A_FpLong	(*hypot)(A_FpLong x, A_FpLong y);	/* returns sqrt(x*x + y*y) */
	A_FpLong	(*log)(A_FpLong);					/* returns natural log of x */
	A_FpLong	(*log10)(A_FpLong);				/* returns log base 10 of x */
	A_FpLong	(*pow)(A_FpLong x, A_FpLong y);		/* returns x to the y power */
	A_FpLong	(*sin)(A_FpLong);
	A_FpLong	(*sqrt)(A_FpLong);
	A_FpLong	(*tan)(A_FpLong);

	int		(*sprintf)(A_char *, const A_char *, ...);
	A_char *	(*strcpy)(A_char *, const A_char *);

	A_FpLong (*asin)(A_FpLong);
	A_FpLong (*acos)(A_FpLong);

	A_long	ansi_procs[1];
} PF_ANSICallbacks;
typedef PF_Fixed	PF_HLS_Pixel[3];
typedef PF_Fixed	PF_RGB_Pixel[3];
typedef PF_Fixed	PF_YIQ_Pixel[3];
typedef struct {
	PF_Err (*RGBtoHLS)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Pixel		*rgb,
		PF_HLS_Pixel	hls);

	PF_Err (*HLStoRGB)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_HLS_Pixel	hls,
		PF_Pixel		*rgb);

	PF_Err (*RGBtoYIQ)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Pixel		*rgb,
		PF_YIQ_Pixel	yiq);

	PF_Err (*YIQtoRGB)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_YIQ_Pixel	yiq,
		PF_Pixel		*rgb);

	PF_Err (*Luminance)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Pixel		*rgb,
		A_long			*lum100);		/* << 100 * luminance */

	PF_Err (*Hue)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Pixel		*rgb,
		A_long			*hue);			/* << 0-255 maps to 0-360  */

	PF_Err (*Lightness)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Pixel		*rgb,
		A_long			*lightness);		/* <<  goes from 0-255 */

	PF_Err (*Saturation)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Pixel		*rgb,
		A_long			*saturation);		/* <<  goes from 0-255 */

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

typedef A_long PF_PlatDataID;
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

	PF_EffectWorld		mask;
	PF_Point			offset;
	PF_MaskFlags		what_is_mask;

} PF_MaskWorld;

//* In Data
typedef struct {
	PF_InteractCallbacks        inter;
	struct _PF_UtilCallbacks    *utils;
	PF_ProgPtr                  effect_ref;
	PF_Quality                  quality;
	PF_SpecVersion              version;
	A_long                      serial_num;
	A_long                      appl_id;
	A_long                      num_params;
	A_long                      reserved;
	A_long                      what_cpu;
	A_long                      what_fpu;
	A_long                      current_time;
	A_long                      time_step;
	A_long                      total_time;
	A_long                      local_time_step;
	A_u_long                    time_scale;
	PF_Field                    field;
	PF_Fixed                    shutter_angle;
	A_long                      width;
	A_long                      height;
	PF_Rect                     extent_hint;
	A_long                      output_origin_x;
	A_long                      output_origin_y;
	PF_RationalScale            downsample_x;
	PF_RationalScale            downsample_y;
	PF_RationalScale            pixel_aspect_ratio;
	PF_InFlags                  in_flags;
	PF_Handle                   global_data;
	PF_Handle                   sequence_data;
	PF_Handle                   frame_data;
	A_long                      start_sampL;
	A_long                      dur_sampL;
	A_long                      total_sampL;
	PF_SoundWorld               src_snd;
	struct SPBasicSuite         *pica_basicP;
	A_long                      pre_effect_source_origin_x;
	A_long                      pre_effect_source_origin_y;
	PF_Fixed                    shutter_phase;
} PF_InData;

typedef A_long PF_NewWorldFlags;
typedef PF_Err (*PF_IteratePixel16Func)	(	void* refconP,					/* >> see comment above !! */
											A_long xL,						/* >> */
											A_long yL,						/* >> */
											PF_Pixel16 *inP,				/* <> */
											PF_Pixel16 *outP);				/* <> */
typedef PF_Err (*PF_IteratePixel8Func)	(	void* refconP,					/* >> see comment above !! */
											A_long xL,						/* >> */
											A_long yL,						/* >> */
											PF_Pixel *inP,					/* <> */
											PF_Pixel *outP);				/* <> */
typedef struct _PF_UtilCallbacks {
	PF_Err (*begin_sampling)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Quality		qual,
		PF_ModeFlags	mf,
		PF_SampPB		*params);

	PF_Err (*subpixel_sample)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		PF_Pixel		*dst_pixel);

	PF_Err (*area_sample)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		PF_Pixel		*dst_pixel);

	void *get_batch_func_is_deprecated;

	PF_Err (*end_sampling)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Quality		qual,
		PF_ModeFlags	mf,
		PF_SampPB		*params);

	PF_Err (*composite_rect)(
		PF_ProgPtr		effect_ref,		/* from in_data */
		PF_Rect			*src_rect,		/* rectangle in source image */
		A_long			src_opacity,	/* opacity of src */
		PF_EffectWorld	*source_wld,	/* src PF world */
		A_long			dest_x,			/* upper left-hand corner of src rect...*/
		A_long			dest_y,			/* ... in composite image */
		PF_Field		field_rdr,		/* which scanlines to render (all, upper, lower) */
		PF_XferMode		xfer_mode,		/* Copy, Composite Behind, Composite In Front */
		PF_EffectWorld	*dest_wld);		/* Destination buffer. Already filled */

	PF_Err (*blend)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		const PF_EffectWorld	*src1,
		const PF_EffectWorld	*src2,
		PF_Fixed		ratio,			/* 0 == full src1, 0x00010000 == full src2 */
		PF_EffectWorld	*dst);

	PF_Err (*convolve)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_EffectWorld	*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		PF_KernelFlags	flags,
		A_long			kernel_size,
		void			*a_kernel,
		void			*r_kernel,
		void			*g_kernel,
		void			*b_kernel,
		PF_EffectWorld	*dst);

	PF_Err (*copy)(
		PF_ProgPtr		effect_ref,		/* reference from in_data	*/
		PF_EffectWorld	*src,
		PF_EffectWorld	*dst,
		PF_Rect 		*src_r,			/* pass NULL for whole world */
		PF_Rect			*dst_r);		/* pass NULL for whole world */

	PF_Err (*fill)(
		PF_ProgPtr		effect_ref,		/* reference from in_data	*/
		const PF_Pixel	*color,
		const PF_Rect	*dst_rect,		/* pass NULL for whole world */
		PF_EffectWorld	*world);

	PF_Err (*gaussian_kernel)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		A_FpLong			kRadius,		/* desired gaussian radius */
		PF_KernelFlags	flags,			/* see kernel flags commented above */
		A_FpLong			multiplier,
		A_long			*diameter,
		void			*kernel);

	PF_Err (*iterate)(
		PF_InData				*in_data,
		A_long					progress_base,
		A_long					progress_final,
		PF_EffectWorld			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		void*					refcon,
		PF_IteratePixel8Func	pix_fn,
		PF_EffectWorld			*dst);

	PF_Err (*premultiply)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		A_long			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
		PF_EffectWorld	*dst);

	PF_Err (*premultiply_color)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_EffectWorld	*src,
		const PF_Pixel	*color,			/* color to premultiply/unmultiply with */
		A_long			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
		PF_EffectWorld	*dst);

	PF_Err (*new_world)(
		PF_ProgPtr			effect_ref,		/* reference from in_data */
		A_long				width,
		A_long				height,
		PF_NewWorldFlags	flags,			/* should would be pre-cleared to zeroes */
		PF_EffectWorld		*world);		/* always 32 bit */

	PF_Err (*dispose_world)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_EffectWorld		*world);

	PF_Err (*iterate_origin)(
		PF_InData				*in_data,
		A_long					progress_base,
		A_long					progress_final,
		PF_EffectWorld			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		const PF_Point			*origin,
		void*					refcon,
		PF_IteratePixel8Func	pix_fn,
		PF_EffectWorld			*dst);

	PF_Err (*iterate_lut)(
		PF_InData		*in_data,
		A_long			progress_base,
		A_long			progress_final,
		PF_EffectWorld		*src,
		const PF_Rect	*area,			/* pass NULL for all pixels */
		A_u_char	*a_lut0,		/* pass NULL for identity */
		A_u_char	*r_lut0,		/* pass NULL for identity */
		A_u_char	*g_lut0,		/* pass NULL for identity */
		A_u_char	*b_lut0,		/* pass NULL for identity */
		PF_EffectWorld		*dst);


	PF_Err	(*transfer_rect)(
		PF_ProgPtr				effect_ref,
		PF_Quality				quality,
		PF_ModeFlags			m_flags,
		PF_Field				field,
		const PF_Rect			*src_rec,
		const PF_EffectWorld	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		A_long					dest_x,
		A_long					dest_y,
		PF_EffectWorld			*dst_world);

	PF_Err	(*transform_world)(
		PF_ProgPtr				effect_ref,
		PF_Quality				quality,
		PF_ModeFlags			m_flags,
		PF_Field				field,
		const PF_EffectWorld	*src_world,
		const PF_CompositeMode	*comp_mode,
		const PF_MaskWorld		*mask_world0,
		const PF_FloatMatrix	*matrices,
		A_long					num_matrices,
		PF_Boolean				src2dst_matrix,
		const PF_Rect			*dest_rect,
		PF_EffectWorld			*dst_world);

	PF_Handle (*host_new_handle)(
		A_u_longlong			size);

	void * (*host_lock_handle)(
		PF_Handle				pf_handle);

	void (*host_unlock_handle)(
		PF_Handle				pf_handle);

	void (*host_dispose_handle)(
		PF_Handle				pf_handle);

	PF_Err (*get_callback_addr)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Quality		quality,
		PF_ModeFlags	mode_flags,
		PF_CallbackID	which_callback,
		PF_CallbackFunc	*fn_ptr);

	PF_Err (*app)(PF_ProgPtr, A_long, ...);	/* application specific callback */

	PF_ANSICallbacks	ansi;			/* ANSI callback block, see above */
	PF_ColorCallbacks	colorCB;		/* colorspace conversion callbacks */

	PF_Err (*get_platform_data)(
		PF_ProgPtr		effect_ref,
		PF_PlatDataID	which,
		void			*data);

	A_u_longlong (*host_get_handle_size)(
		PF_Handle				pf_handle);

	PF_Err	(*iterate_origin_non_clip_src)(
		PF_InData				*in_data,
		A_long					progress_base,
		A_long					progress_final,
		PF_EffectWorld			*src,
		const PF_Rect			*area,
		const PF_Point			*origin,
		void*					refcon,
		PF_IteratePixel8Func	pix_fn,
		PF_EffectWorld			*dst);

	PF_Err (*iterate_generic)(
		A_long			iterationsL,						/* >> */		// can be PF_Iterations_ONCE_PER_PROCESSOR
		void			*refconPV,							/* >> */
		PF_Err			(*fn_func)(	void *refconPV,			/* >> */
									A_long thread_indexL,		// only call abort and progress from thread_indexL == 0.
									A_long i,
									A_long iterationsL));		// never sends PF_Iterations_ONCE_PER_PROCESSOR

	PF_Err (*host_resize_handle)(
		A_u_longlong		new_sizeL,		/* >> */
		PF_Handle			*handlePH);		/* <> Handle Value May Change */


	PF_Err (*subpixel_sample16)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		PF_Pixel16		*dst_pixel);

	PF_Err (*area_sample16)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_Fixed		x,
		PF_Fixed		y,
		const PF_SampPB	*params,
		PF_Pixel16		*dst_pixel);

	PF_Err (*fill16)(
		PF_ProgPtr			effect_ref,		/* reference from in_data	*/
		const PF_Pixel16	*color,
		const PF_Rect		*dst_rect,		/* pass NULL for whole world */
		PF_EffectWorld		*world);

	PF_Err (*premultiply_color16)(
		PF_ProgPtr		effect_ref,		/* reference from in_data */
		PF_EffectWorld	*src,
		const PF_Pixel16 *color,			/* color to premultiply/unmultiply with */
		A_long			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
		PF_EffectWorld	*dst);

	PF_Err (*iterate16)(
		PF_InData				*in_data,
		A_long					progress_base,
		A_long					progress_final,
		PF_EffectWorld			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		void*					refcon,
		PF_IteratePixel16Func	pix_fn,
		PF_EffectWorld			*dst);

	PF_Err (*iterate_origin16)(
		PF_InData				*in_data,
		A_long					progress_base,
		A_long					progress_final,
		PF_EffectWorld			*src,
		const PF_Rect			*area,			/* pass NULL for all pixels */
		const PF_Point			*origin,
		void*					refcon,
		PF_IteratePixel16Func	pix_fn,
		PF_EffectWorld			*dst);

	PF_Err	(*iterate_origin_non_clip_src16)(
		PF_InData				*in_data,
		A_long					progress_base,
		A_long					progress_final,
		PF_EffectWorld				*src,
		const PF_Rect			*area,
		const PF_Point			*origin,
		void*				refcon,
		PF_IteratePixel16Func	pix_fn,
		PF_EffectWorld				*dst);

	PF_Err	(*get_pixel_data8)(
		PF_EffectWorld	*worldP,
		PF_PixelPtr		pixelsP0,		// NULL to use data in PF_EffectWorld
		PF_Pixel8		**pixPP);		// will return NULL if depth mismatch

	PF_Err	(*get_pixel_data16)(
		PF_EffectWorld	*worldP,
		PF_PixelPtr		pixelsP0,		// NULL to use data in PF_EffectWorld
		PF_Pixel16		**pixPP);		// will return NULL if depth mismatch


										// and we're done. all future expansion
										// is thru suite mechanism. (for example,
										// this is where you'll find the floating
										// pt pixel callbacks)
	A_long				reserved[1];

} PF_UtilCallbacks;

//* Cmd
enum {
	PF_Cmd_ABOUT = 0,
	PF_Cmd_GLOBAL_SETUP,
	PF_Cmd_UNUSED_0,
	PF_Cmd_GLOBAL_SETDOWN,
	PF_Cmd_PARAMS_SETUP,
	PF_Cmd_SEQUENCE_SETUP,
	PF_Cmd_SEQUENCE_RESETUP,
	PF_Cmd_SEQUENCE_FLATTEN,
	PF_Cmd_SEQUENCE_SETDOWN,
	PF_Cmd_DO_DIALOG,
	PF_Cmd_FRAME_SETUP,
	PF_Cmd_RENDER,
	PF_Cmd_FRAME_SETDOWN,
	PF_Cmd_USER_CHANGED_PARAM,
	PF_Cmd_UPDATE_PARAMS_UI,
	PF_Cmd_EVENT,
	PF_Cmd_GET_EXTERNAL_DEPENDENCIES,
	PF_Cmd_COMPLETELY_GENERAL,
	PF_Cmd_QUERY_DYNAMIC_FLAGS,
	PF_Cmd_AUDIO_RENDER,
	PF_Cmd_AUDIO_SETUP,
	PF_Cmd_AUDIO_SETDOWN,
	PF_Cmd_ARBITRARY_CALLBACK,
	PF_Cmd_SMART_PRE_RENDER,
  	PF_Cmd_SMART_RENDER,
	PF_Cmd_RESERVED1,
	PF_Cmd_RESERVED2,
	PF_Cmd_RESERVED3,
	PF_Cmd_GET_FLATTENED_SEQUENCE_DATA,
	PF_Cmd_TRANSLATE_PARAMS_TO_PREFS,
	PF_Cmd_RESERVED4,
	PF_Cmd_SMART_RENDER_GPU,
	PF_Cmd_GPU_DEVICE_SETUP,
	PF_Cmd_GPU_DEVICE_SETDOWN,
	PF_Cmd_NUM_CMDS
};
typedef A_long PF_Cmd;

//* Out Data
typedef struct {
	A_u_long         my_version;
	A_char           name[PF_MAX_EFFECT_NAME_LEN + 1];
	PF_Handle        global_data;
	A_long           num_params;
	PF_Handle        sequence_data;
	A_long           flat_sdata_size;
	PF_Handle        frame_data;
	A_long           width;
	A_long           height;
	PF_Point         origin;
	PF_OutFlags      out_flags;
	A_char           return_msg[PF_MAX_EFFECT_MSG_LEN + 1];
	A_long           start_sampL;
	A_long           dur_sampL;
	PF_SoundWorld    dest_snd;
	PF_OutFlags2     out_flags2;
} PF_OutData;

//* Entry Point
typedef PF_Err (*EntryPointFunc) (
	PF_Cmd,
	PF_InData *,
	PF_OutData *,
	PF_ParamDef *,
	PF_LayerDef *,
	void *
);
