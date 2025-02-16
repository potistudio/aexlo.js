#pragma once

#include <ppl.h>
#include "../../../lib/nameof/nameof.hpp"

#include "../../headers/common.hh"
#include "../../headers/input_data.hh"
#include "../../headers/layer_data.hh"
#include "../../headers/suites/iterate_8_suite_2.hh"

#include "../../logger/logger.hh"

class Iterate8Suite2Factory {
	public:
		static AE_Iterate8Suite2 * Create() {
			AE_Iterate8Suite2 *suite = new AE_Iterate8Suite2();

			suite->iterate = [] (
				AE_InData        *in_data,
				int              progress_base,
				int              progress_final,
				AE_LayerParam    *src,
				const AE_Rect    *area,
				void             *controller,
				int              (*pix_fn)(void* controller, int x, int y, AE_Pixel* in, AE_Pixel* out),
				AE_LayerParam    *dts
			) -> int {
				AE_Error error = AE_Error::NONE;

				int width = in_data->width;
				int height = in_data->height;
				const int pixel_count = width * height;

				AE_Pixel *output_pixels = new AE_Pixel[pixel_count];

				Concurrency::parallel_for (0, height, 1, [&](int y) -> void {
					for (int x = 0; x < width; x++) {
						AE_Pixel inPixel { 255, 0, 0, 0 };
						AE_Pixel outPixel;

						pix_fn (controller, x, y, &inPixel, &outPixel);
						output_pixels[x + y * width] = outPixel;
					}
				});

				dts->data = output_pixels;

				LOG_DEBUG ("Called: AE_Iterate8Suite2::Iterate (");
				LOG_DEBUG ("           in_data: 0x" << in_data);
				LOG_DEBUG ("     progress_base: " << progress_base);
				LOG_DEBUG ("    progress_final: " << progress_final);
				LOG_DEBUG ("               src: 0x" << src);
				LOG_DEBUG ("              area: 0x" << area);
				LOG_DEBUG ("        controller: 0x" << controller);
				LOG_DEBUG ("            pix_fn: 0x" << pix_fn);
				LOG_DEBUG ("               dst: 0x" << dts);
				LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

				return static_cast<int>(error);
			};

			return suite;
		}
};
