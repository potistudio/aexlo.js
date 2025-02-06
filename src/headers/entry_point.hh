#pragma once

#include "./errors.hh"
#include "./commands.hh"
#include "./input_data.hh"
#include "./output_data.hh"
#include "./param_data.hh"
#include "./layer_data.hh"

typedef AE_Error (*EntryPointFunc) (
	AE_Command,
	AE_InData *,
	AE_OutData *,
	AE_ParamDef *[],
	AE_LayerParam *,
	void *
);
