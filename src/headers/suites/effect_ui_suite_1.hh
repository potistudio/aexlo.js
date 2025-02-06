#pragma once
#pragma pack (push, AE, 8)

#include "../errors.hh"
#include "../common.hh"

struct AE_EffectUISuite1 {
	AE_Error (*SetOptionsButtonName) (
		AE_ProgressInfoPtr    effect_ref,
		const char            *nameZ
	);
};

#pragma pack (pop, AE)
