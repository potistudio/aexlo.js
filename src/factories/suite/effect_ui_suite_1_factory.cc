#pragma once

#include "../../../lib/nameof/nameof.hpp"

#include "../../headers/commands.hh"
#include "../../headers/common.hh"
#include "../../headers/suites/effect_ui_suite_1.hh"

#include "../../logger/logger.hh"

class EffectUISuite1Factory {
	public:
		static AE_EffectUISuite1* Create() {
			AE_EffectUISuite1 *suite = new AE_EffectUISuite1();

			suite->SetOptionsButtonName = [] (
				AE_ProgressInfoPtr    effect_ref,
				const char            *name
			) -> AE_Error {
				AE_Error error = AE_Error::NONE;

				LOG_DEBUG ("Called: AE_EffectUISuite1::SetOptionsButtonName (");
				LOG_DEBUG ("    from: 0x" << effect_ref);
				LOG_DEBUG ("    name: \"" << *name << "\"");
				LOG_DEBUG (") -> " << NAMEOF_ENUM(error));

				return error;
			};

			return suite;
		}
};
