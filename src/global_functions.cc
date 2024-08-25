#ifndef AEXLO_GLOBAL_FUNCTIONS_H_
#define AEXLO_GLOBAL_FUNCTIONS_H_

#include "./headers/basic.h"
#include "./headers/suites.h"
#include "./headers/input_data.h"
#include "./headers/layer_data.h"

int addParam (ProgressInfoPtr effect_ref, int index, PF_ParamDefPtr def) {
	std::cout << "Param Type: " << def->param_type << std::endl;
	std::cout << "Param Name: " << def->name << std::endl;
	std::cout << "Valid Min: " << def->u.fs_d.valid_min << std::endl;
	std::cout << "Slider Min: " << def->u.fs_d.slider_min << std::endl;
	std::cout << "Valid Max: " << def->u.fs_d.valid_max << std::endl;
	std::cout << "Slider Max: " << def->u.fs_d.slider_max << std::endl;
	std::cout << "Value: " << def->u.fs_d.value << std::endl;
	std::cout << "Default: " << def->u.fs_d.dephault << std::endl;
	std::cout << "Precision: " << def->u.fs_d.precision << std::endl;
	std::cout << "Display Flags: " << def->u.fs_d.display_flags << std::endl;
	std::cout << "Flags: " << def->u.fs_d.fs_flags << std::endl;
	std::cout << "Curve Tolerance: " << def->u.fs_d.curve_tolerance << std::endl;
	std::cout << "ID: " << def->uu.id << std::endl;
	return 0;
}

int iterate (PF_InData *in_data, int progress_base, int progress_final, LayerParam *src, const PF_Rect *area, void *controller, int(*pix_fn)(void* controller, int x, int y, Pixel* in, Pixel* out), LayerParam *dts) {
	Pixel inPixel;
	Pixel outPixel;

	for (int i = 0; i < 10; i++) {
		pix_fn (controller, i, 0, &inPixel, &outPixel);
		std::cout << "A: " << ((int)outPixel.alpha) << ", R: " << ((int)outPixel.red) << ", G: " << ((int)outPixel.green) << ", B: " << ((int)outPixel.blue) << std::endl;
	}

	return 0;
}

int copy (ProgressInfoPtr effect_ref, LayerParam *src, LayerParam *dst, PF_Rect *src_r, PF_Rect *dst_r) {
	std::cout << "copy" << src << std::endl;
	return 0;
}

#endif
