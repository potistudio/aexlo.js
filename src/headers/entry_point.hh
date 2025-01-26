#pragma once

#include "./basic.hh"
#include "./commands.hh"
#include "./input_data.hh"
#include "./output_data.hh"
#include "./param_data.hh"
#include "./layer_data.hh"

typedef int (*EntryPointFunc) (
	PF_Cmd,
	PF_InData *,
	PF_OutData *,
	PF_ParamDef *[],
	LayerParam *,
	void *
);
