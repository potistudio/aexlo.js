#include "./parameter_parser.hh"

AE_Pixel ParamParser::ParsePixel (Napi::Object pixel) {
	AE_Pixel result;

	result.alpha = static_cast<uint8_t>(pixel.Get("alpha").As<Napi::Number>().Int32Value());
	result.red = static_cast<uint8_t>(pixel.Get("red").As<Napi::Number>().Int32Value());
	result.green = static_cast<uint8_t>(pixel.Get("green").As<Napi::Number>().Int32Value());
	result.blue = static_cast<uint8_t>(pixel.Get("blue").As<Napi::Number>().Int32Value());

	return result;
}

AE_ParamDef ParamParser::ParseParam (Napi::Object param, std::vector<AE_ParamDef> params) {
	AE_ParamDef result;

	int target_id = param.Get ("id").As<Napi::Number>().Int32Value();

	for (int i = 0; i < params.size(); i++) {
		if (params[i].uu.id == target_id) {
			switch (params[i].param_type) {
				case AE_ParamType::SLIDER:
					result.u.fs_d.value = param.Get ("value").As<Napi::Number>().Int32Value();

					break;
				case AE_ParamType::CHECKBOX:
					result.u.bd.value = param.Get ("value").As<Napi::Boolean>().Value();

					break;
				case AE_ParamType::COLOR:
					result.u.cd.value = ParamParser::ParsePixel (param.Get("value").As<Napi::Object>());

					break;
				case AE_ParamType::FLOAT_SLIDER:
					result.u.fs_d.value = param.Get ("value").As<Napi::Number>().DoubleValue();

					break;
			}

			break;
		}
	}

	return result;
}
