#ifndef AEXLO_BASIC_H_
#define AEXLO_BASIC_H_

typedef struct {
	unsigned char alpha, red, green, blue;
} Pixel;
typedef Pixel *PF_PixelPtr;
typedef struct {
	int left, top, right, bottom;
} PF_LRect;
typedef PF_LRect PF_Rect;
typedef PF_Rect PF_UnionableRect;

struct ProgressInfo;
typedef struct ProgressInfo *ProgressInfoPtr;

typedef struct {
	int             num;  // numerator
	unsigned int    den;  // denominator
} PF_RationalScale;

typedef struct {
	short major;
	short minor;
} PF_SpecVersion;

typedef struct {
	int             value;
	unsigned int    scale;
} A_Time;

typedef struct {
	int             num;
	unsigned int    def;
} A_Ratio;

typedef struct {
	double x, y;
} A_FloatPoint;

#endif
