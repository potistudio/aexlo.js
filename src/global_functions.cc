#ifndef AEXLO_GLOBAL_FUNCTIONS_H_
#define AEXLO_GLOBAL_FUNCTIONS_H_

#include <iostream>

#include "./headers/basic.h"
#include "./headers/suites.h"
#include "./headers/input_data.h"
#include "./headers/layer_data.h"

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
