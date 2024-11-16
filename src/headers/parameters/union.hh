#ifndef AEXLO_PARAM_UNION_H_
#define AEXLO_PARAM_UNION_H_

#include "../layer_data.hh"
#include "./slider.hh"
#include "./fixed_slider.hh"
#include "./angle.hh"
#include "./checkbox.hh"
#include "./color.hh"
#include "./point.hh"
#include "./popup.hh"
#include "./float_slider.hh"
#include "./arbitrary.hh"
#include "./path.hh"
#include "./button.hh"
#include "./point_3d.hh"

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
