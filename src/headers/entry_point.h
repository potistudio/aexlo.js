#ifndef AEXLO_ENTRYPOINTDEF_H_
#define AEXLO_ENTRYPOINTDEF_H_

#include "./basic.h"
#include "./commands.h"
#include "./input_data.h"
#include "./output_data.h"
#include "./param_data.h"
#include "./layer_data.h"

typedef int (*EntryPointFunc) (
	PF_Cmd,
	PF_InData *,
	PF_OutData *,
	PF_ParamDef *[],
	LayerParam *,
	void *
);

#endif
