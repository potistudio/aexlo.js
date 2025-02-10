#pragma once

#include "../../headers/common.hh"
#include "../../headers/input_data.hh"
#include "../../headers/layer_data.hh"
#include "../../headers/suites/iterate_8_suite_2.hh"

#include "../../logger/logger.hh"

class Iterate8Suite2Factory {
	public:
		static AE_Iterate8Suite2 * Create() {
			AE_Iterate8Suite2 *suite = new AE_Iterate8Suite2();

			suite->iterate = [](AE_InData *in_data, int progress_base, int progress_final, AE_LayerParam *src, const AE_Rect *area, void *controller, int(*pix_fn)(void* controller, int x, int y, AE_Pixel* in, AE_Pixel* out), AE_LayerParam *dts) -> int {
				AE_Pixel inPixel;
				AE_Pixel outPixel;

				for (int i = 0; i < 10; i++) {
					pix_fn (controller, i, 0, &inPixel, &outPixel);
				}

				return 0;
			};

			return suite;
		}
};
