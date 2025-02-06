#pragma once
#pragma pack (push, AE, 8)

struct AE_CheckBoxParam {
	/**
	 * @brief Parameter value
	 */
	int value;

	/**
	 * @brief Default value
	 */
	bool dephault;

	/**
	 * @brief padding
	 */
	char reserved;
	short reserved1;

	union {
		const char *nameptr;
	} u;
};

#pragma pack (pop, AE)
