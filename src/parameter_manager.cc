#include "./parameter_manager.hh"

std::map<AE_ProgressInfoPtr, std::vector<AE_ParamDef>> ParamManager::params;

void ParamManager::AddParam (AE_ProgressInfoPtr effect_ref, AE_ParamDef param) {
	try {
		params.at (effect_ref).push_back (param);
	} catch (const std::out_of_range& oor) {
		LOG_DEBUG ("Parameter Added: " << param.name);
		params.insert (std::pair<AE_ProgressInfoPtr, std::vector<AE_ParamDef>>(effect_ref, std::vector<AE_ParamDef>{ param }));
	}

	LOG_INFO ("  ==> ID: " << param.uu.id);
	LOG_INFO ("  ==> Param Name: " << param.name);
	LOG_INFO ("  ==> Param Type: " << NAMEOF_ENUM(param.param_type));

	LOG_INFO ("  ==> Valid Min: " << param.u.fs_d.valid_min);
	LOG_INFO ("  ==> Valid Max: " << param.u.fs_d.valid_max);

	LOG_INFO ("  ==> Slider Min: " << param.u.fs_d.slider_min);
	LOG_INFO ("  ==> Slider Max: " << param.u.fs_d.slider_max);

	LOG_INFO ("  ==> Value: " << param.u.fs_d.value);
	LOG_INFO ("  ==> Default: " << param.u.fs_d.dephault);

	LOG_INFO ("  ==> Precision: " << param.u.fs_d.precision);
	LOG_INFO ("  ==> Curve Tolerance: " << param.u.fs_d.curve_tolerance);

	LOG_INFO ("  ==> Display Flags: " << param.u.fs_d.display_flags);
	LOG_INFO ("  ==> Flags: " << param.u.fs_d.fs_flags);
}

int ParamManager::GetParamsCount() {
	return params.size();
}
