#pragma once

#include <map>
#include <vector>

#include "../lib/nameof/nameof.hpp"

#include "./logger/logger.hh"

#include "./headers/common.hh"
#include "./headers/param_data.hh"

class ParamManager {
	private:
		static std::map<AE_ProgressInfoPtr, std::vector<AE_ParamDef>> params;

	public:
		static void AddParam (AE_ProgressInfoPtr, AE_ParamDef);
		static int GetParamsCount();
		static std::vector<AE_ParamDef> GetParamsByRef (AE_ProgressInfoPtr);
};
