#pragma once
#pragma pack (push, AE, 8)

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

union AE_ParamDefUnion {
	AE_LayerParam          ld;
	AE_SliderParam         sd;
	AE_FixedSliderParam    fd;
	AE_AngleParam          ad;
	AE_CheckBoxParam       bd;
	AE_ColorParam          cd;
	AE_PointParam          td;
	AE_PopupParam          pd;
	AE_FloatSliderParam    fs_d;
	AE_ArbitraryParam      arb_d;
	AE_PathParam           path_d;
	AE_ButtonParam         button_d;
	AE_Point3DParam        point3d_d;
};

#pragma pack (pop, AE)
