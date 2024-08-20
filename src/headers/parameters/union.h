#ifndef AEXLO_PARAM_UNION_H_
#define AEXLO_PARAM_UNION_H_

#include "../layer_data.h"
#include "./slider.h"
#include "./fixed_slider.h"
#include "./angle.h"
#include "./checkbox.h"
#include "./color.h"
#include "./point.h"
#include "./popup.h"
#include "./float_slider.h"
#include "./arbitrary.h"
#include "./path.h"
#include "./button.h"
#include "./point_3d.h"

typedef union {
	LayerParam          ld;
	PF_SliderDef         sd;
	PF_FixedSliderDef    fd;
	PF_AngleDef          ad;
	PF_CheckBoxDef       bd;
	ColorParam           cd;
	PF_PointDef          td;
	PF_PopupDef          pd;
	FloatSlider          fs_d;
	PF_ArbitraryDef      arb_d;
	PF_PathDef           path_d;
	PF_ButtonDef         button_d;
	PF_Point3DDef        point3d_d;
} PF_ParamDefUnion;

#endif
