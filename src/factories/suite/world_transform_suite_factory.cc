#pragma once

#include "../../../lib/nameof/nameof.hpp"

#include "../../headers/errors.hh"
#include "../../headers/common.hh"
#include "../../headers/layer_data.hh"
#include "../../headers/suites/world_transform_suite_1.hh"

#include "../../logger/logger.hh"

class WorldTransformSuiteFactory {
	public:
		static AE_WorldTransformSuite1* Create() {
			AE_WorldTransformSuite1 *suite = new AE_WorldTransformSuite1();

			suite->Copy = [] (
				AE_ProgressInfoPtr    effect_ref,
				AE_LayerParam         *src,
				AE_LayerParam         *dst,
				AE_Rect               *src_r,
				AE_Rect               *dst_r
			) -> AE_Error {
				AE_Error error = AE_Error::NONE;

				LOG_DEBUG ("Called: AE_WorldTransformSuite1::Copy (");
				LOG_DEBUG ("     from: 0x" << effect_ref);
				LOG_DEBUG ("      src: 0x" << src);
				LOG_DEBUG ("      dst: 0x" << dst);
				LOG_DEBUG ("    src_r: 0x" << src_r);
				LOG_DEBUG ("    dst_r: 0x" << dst_r);
				LOG_DEBUG (") -> AE_Error::" << NAMEOF_ENUM(error));

				return error;
			};

			return suite;
		};
};
