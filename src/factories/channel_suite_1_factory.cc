/**
 * @file channel_suite_1_factory.cc
 * @brief Factory for AE_ChannelSuite1
 * @author potistudio
 */

#pragma once

#include <stdint.h>

#include "../logger/logger.hh"

#include "../headers/suites/channel_suite_1.hh"

class ChannelSuite1Factory {
	public:
		ChannelSuite1Factory() { }
		~ChannelSuite1Factory() { }

		AE_ChannelSuite1* Create() {
			AE_ChannelSuite1 *suite = new AE_ChannelSuite1();

			suite->GetLayerChannelCount = [](
				AE_ProgressInfoPtr effect_ref,
				AE_ParamIndex   param_index,
				int         *num_channels
			) -> AE_Error {
				int NUM_CHANNELS = 4;
				*num_channels = NUM_CHANNELS;

				LOG_DEBUG ("Called: AE_ChannelSuite1::GetLayerChannelCount (");
				LOG_DEBUG ("    effect_ref: " << effect_ref);
				LOG_DEBUG ("    param_index: " << param_index);
				LOG_DEBUG (")");
				LOG_DEBUG ("  ==> num_channels: " << NUM_CHANNELS);

				return AE_Error::NONE;
			};

			suite->GetLayerChannelIndexedRefAndDesc = [](
				AE_ProgressInfoPtr       effect_ref,
				AE_ParamIndex         param_index,
				AE_ChannelIndex       channel_index,
				AE_Boolean            *foundPB,
				AE_ChannelRef         *channel_refP,
				AE_ChannelDescription *channel_descP
			) -> AE_Error {
				LOG_DEBUG ("Called: AE_ChannelSuite1::GetLayerChannelIndexedRefAndDesc (");
				LOG_DEBUG ("    effect_ref: " << effect_ref);
				LOG_DEBUG ("    param_index: " << param_index);
				LOG_DEBUG ("    channel_index: " << channel_index);
				LOG_DEBUG (")");

				return AE_Error::NONE;
			};

			suite->GetLayerChannelTypedRefAndDesc = [](
				AE_ProgressInfoPtr       effect_ref,
				AE_ParamIndex         param_index,
				AE_ChannelType        channel_type,
				AE_Boolean            *foundPB,
				AE_ChannelRef         *channel_refP,
				AE_ChannelDescription *channel_descP
			) -> AE_Error {
				LOG_DEBUG ("Called: AE_ChannelSuite1::GetLayerChannelTypedRefAndDesc (");
				LOG_DEBUG ("    effect_ref: " << effect_ref);
				LOG_DEBUG ("    param_index: " << param_index);
				LOG_DEBUG ("    channel_type: " << channel_type);
				LOG_DEBUG (")");

				return AE_Error::NONE;
			};

			suite->CheckoutLayerChannel = [](
				AE_ProgressInfoPtr			effect_ref,
				AE_ChannelRefPtr	channel_refP,
				int				what_time,
				int				duration,
				unsigned int		time_scale,
				AE_DataType 		data_type,
				AE_ChannelChunk		*channel_chunkP
			) -> AE_Error {
				LOG_DEBUG ("Called: AE_ChannelSuite1::CheckoutLayerChannel (");
				LOG_DEBUG ("    effect_ref: " << effect_ref);
				LOG_DEBUG ("    channel_refP: " << channel_refP);
				LOG_DEBUG ("    what_time: " << what_time);
				LOG_DEBUG ("    duration: " << duration);
				LOG_DEBUG ("    time_scale: " << time_scale);
				LOG_DEBUG ("    data_type: " << data_type);
				LOG_DEBUG (")");

				return AE_Error::NONE;
			};

			suite->CheckinLayerChannel = [](
				AE_ProgressInfoPtr  effect_ref,
				AE_ChannelRefPtr channel_refP,
				AE_ChannelChunk  *channel_chunkP
			) -> AE_Error {
				LOG_DEBUG ("Called: AE_ChannelSuite1::CheckinLayerChannel (");
				LOG_DEBUG ("    effect_ref: " << effect_ref);
				LOG_DEBUG ("    channel_refP: " << channel_refP);
				LOG_DEBUG (")");

				return AE_Error::NONE;
			};

			return suite;
		}
};
