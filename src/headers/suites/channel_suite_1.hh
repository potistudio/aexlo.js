#pragma once

#include <stdint.h>

#include "../errors.hh"
#include "../basic.hh"
#include "../common.hh"

/**
 * @struct AE_ChannelSuite1
 * @brief (PF_ChannelSuite1) frozen in AE 5.0
 */
typedef struct AE_ChannelSuite1 {
	/**
	 * @brief use this to find the number of channels associated with a given source layer Most likely use is to get number of channels for iteration purposes.
	 *
	 * @param effect_ref in
	 * @param param_index in - the parameter index of the layer whose source you wish to interrogate
	 * @param num_channels out - the number of "auxillary" channels
	 *
	 * @return Error code
	 */
	AE_Error (*GetLayerChannelCount) (
		ProgressInfoPtr effect_ref,
		AE_ParamIndex   param_index,
		int32_t         *num_channels
	);

	/**
	 * @brief Given a channel index return the opaque channelRef and a channel description channel index must lie between 0 and num_channels-1.
	 * @brief you will use the channelRef in all subsequent calls
	 *
	 * @param effect_ref in
	 * @param param_index in
	 * @param channel_index in
	 * @param foundPB out
	 * @param channel_refP out
	 * @param channel_descP out
	 *
	 * @return Error code
	 */
	AE_Error (*GetLayerChannelIndexedRefAndDesc) (
		ProgressInfoPtr       effect_ref,
		AE_ParamIndex         param_index,
		AE_ChannelIndex       channel_index,
		PF_Boolean            *foundPB,
		AE_ChannelRef         *channel_refP,
		AE_ChannelDescription *channel_descP
	);

	/**
	 * @brief Given a type retrieve the channelRef and ChannelDescription.
	 *
	 * @param effect_ref in
	 * @param param_index in
	 * @param channel_index in
	 * @param found out
	 * @param channel_refP out
	 * @param channel_descP out
	 *
	 * @return Error code
	 */
	AE_Error (*GetLayerChannelTypedRefAndDesc) (
		ProgressInfoPtr       effect_ref,
		AE_ParamIndex         param_index,
		AE_ChannelType        channel_type,
		PF_Boolean            *foundPB,
		AE_ChannelRef         *channel_refP,
		AE_ChannelDescription *channel_descP
	);

	/**
	 * @brief given the time parameters and a channel reference, get the data.
	 * @brief data chunk is allocated is of the type requested.
	 * @brief The data is in chunky format.
	 *
	 * @param effect_ref in
	 * @param channel_refP in
	 * @param what_time in
	 * @param duration in
	 * @param time_scale in
	 * @param data_type in
	 * @param channel_chunkP out
	 *
	 * @return Error code
	 */
	AE_Error (*CheckoutLayerChannel) (
		ProgressInfoPtr  effect_ref,
		AE_ChannelRefPtr channel_refP,
		int32_t          what_time,
		int32_t          duration,
		uint32_t         time_scale,
		AE_DataType      data_type,
		AE_ChannelChunk  *channel_chunkP
	);

	/**
	 * @brief The checked out channel must be checked in to avoid memory leaks.
	 *
	 * @param effect_ref in
	 * @param channel_refP in
	 * @param channel_chunkP in
	 *
	 * @return Error code
	 */
	AE_Error (*CheckinLayerChannel) (
		ProgressInfoPtr  effect_ref,
		AE_ChannelRefPtr channel_refP,
		AE_ChannelChunk  *channel_chunkP
	);
};
