#pragma once

/**
 * @enum AE_InFlags
 * @brief The in_flags field of the InData can be set to an OR-ed combination of these flags to communicate various things from AE to an effect plugin.
 */
enum class AE_InFlags : int {
	NONE                   = 0L,
	PROJECT_IS_RENDER_ONLY = 1L << 0
};
