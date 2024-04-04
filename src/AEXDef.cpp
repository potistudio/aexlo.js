
#define PF_FIRST_ERR                    512
#define PF_MAX_EFFECT_MSG_LEN           255
#define PF_MAX_EFFECT_NAME_LEN          31
#define PF_MAX_EFFECT_PARAM_NAME_LEN    31
#define PF_MAX_PARAM_DESCRIPTION_LEN    31
#define PF_MAX_PARAM_VALUE_LEN          31

typedef int int32_t;
typedef unsigned int uint32_t;

typedef int32_t A_long;
typedef short A_short;
typedef uint32_t A_u_long;
typedef char A_char;
typedef unsigned char A_u_char;

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
