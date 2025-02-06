/**
 * @file path.hh
 * @brief Path Parameter
 * @author potistudio
 */

#pragma once
#pragma pack (push, AE, 8)

enum AE_PathId : unsigned long {
	NONE = 0,
};

struct AE_PathParam {
	AE_PathId    path_id;
	long         reserved0;
	long         dephault;
};

#pragma pack (pop, AE)
