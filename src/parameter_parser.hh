#pragma once

#include <stdint.h>
#include <napi.h>

#include "./headers/common.hh"
#include "./headers/param_data.hh"

class ParamParser {
	public:
		static AE_Pixel ParsePixel (Napi::Object pixel);
		static AE_ParamDef ParseParam (Napi::Object param, std::vector<AE_ParamDef> params);
};
