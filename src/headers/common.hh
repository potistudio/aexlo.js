#pragma once
#pragma pack (push, AE, 8)


/* ---------------- Enums ---------------- */

enum class AE_Quality : int {
	DRAWING_AUDIO = -1,
	LO            = 0,
	HI
};

enum class AE_ModeFlags : int {
	ALPHA_PREMUL   = 0,
	ALPHA_STRAIGHT = (1L << 0)
};

enum class AE_Field : int {
	FRAME = 0L,
	UPPER = 1L,
	LOWER = 2L
};

enum class AE_ParamFlags : int {
	RESERVED1                        = 1 << 0,
	CANNOT_TIME_VARY                 = 1 << 1,
	CANNOT_INTERP                    = 1 << 2,
	RESERVED2                        = 1 << 3,
	RESERVED3                        = 1 << 4,
	COLLAPSE_TWIRLY                  = 1 << 5,
	SUPERVISE                        = 1 << 6,
	START_COLLAPSED                  = COLLAPSE_TWIRLY,
	USE_VALUE_FOR_OLD_PROJECTS       = 1 << 7,
	LAYER_PARAM_IS_TRACKMATTE        = 1 << 7,
	EXCLUDE_FROM_HAVE_INPUTS_CHANGED = 1 << 8,
	SKIP_REVEAL_WHEN_UNHIDDEN        = 1 << 9
};

enum class AE_WorldFlags : int {
	DEEP      = 1L << 0,
	WRITEABLE = 1L << 1,
	RESERVED0 = 1L << 24,
	RESERVED1 = 1L << 25,
	RESERVED2 = 1L << 26,
	RESERVED3 = 1L << 27,
	RESERVED4 = 1L << 28,
	RESERVED5 = 1L << 29,
	RESERVED6 = 1L << 30,
	RESERVED  = 1L << 31
};


/* ---------------- Simple Types ---------------- */

typedef struct _AE_LayerAudio *AE_LayerAudio;
typedef void *AE_SndSamplePtr;

struct AE_ProgressInfo;
typedef struct AE_ProgressInfo *AE_ProgressInfoPtr;

typedef int AE_ParamValue;

struct AE_SpecVersion {
	short major;
	short minor;
};  // 8bytes

typedef int AE_ParamIndex;
typedef unsigned int AE_UFixed;

typedef int AE_Fixed;
typedef char AE_Boolean;
typedef void **AE_Handle;

struct AE_Point {
	int h, v;
};

struct AE_LRect {
	int left, top, right, bottom;
}; // 16bytes

typedef AE_LRect AE_Rect;
typedef AE_Rect AE_UnionableRect;

struct AE_RationalScale {
	int num;
	unsigned int den;
};

struct AE_FixedPoint {
	AE_Fixed x, y;
};

struct AE_FixedRect {
	AE_Fixed left, top, right, bottom;
};

struct AE_Matrix {
	AE_Fixed mat[3][3];
};

typedef int AE_TransferMode;
typedef AE_TransferMode AE_XferMode;

struct AE_Pixel {
	unsigned char alpha, red, green, blue;
};

typedef AE_Pixel AE_Pixel8;
typedef AE_Pixel AE_UnionablePixel;

struct AE_Pixel16 {
	unsigned short alpha, red, green, blue;
};

typedef float AE_FpShort;
typedef double AE_FpLong;

struct AE_PixelFloat {
	float alpha, red, green, blue;
};
typedef AE_PixelFloat AE_Pixel32;

struct AE_FloatMatrix {
	float mat[3][3];
};

struct AE_CompositeMode {
	AE_TransferMode    xfer;
	int                rand_seed;
	unsigned char      opacity;
	AE_Boolean         rgb_only;
	unsigned short     opacitySu;
};

typedef unsigned int AE_PixLong;
typedef struct _AE_PixelOpaque *AE_PixelOpaquePtr;
typedef AE_Pixel *AE_PixelPtr;

typedef AE_Fixed AE_RGB_Pixel[3];
typedef AE_Fixed AE_YIQ_Pixel[3];
typedef AE_Fixed AE_HLS_Pixel[3];


/* ---------------- Multi-channel Data ---------------- */

typedef int AE_ChannelType;
typedef int AE_DataType;
typedef int AE_ChannelIndex;

struct AE_ChannelDescription {
	AE_ChannelType    channel_type;
	char              name[64];
	AE_DataType       data_type;
	int               dimension;
};

struct AE_ChannelRef {
	long long opaque[8];
};
typedef AE_ChannelRef *AE_ChannelRefPtr;

struct AE_ChannelChunk {
	AE_ChannelRef    channel_ref;
	int              widthL;
	int              heightL;
	int              dimensionL;
	int              row_bytesL;
	AE_DataType      data_type;
	AE_Handle        dataH;
	void             *dataPV;
};

enum class AE_MaskMode : int {
	NONE = 0,
	ADD,
	SUBTRACT,
	INTERSECT,
	LIGHTEN,
	DARKEN,
	DIFFERENCE_,
	ACCUM,

	NUM_MASKMODES
};

#pragma pack (pop, AE)
