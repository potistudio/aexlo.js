#include "./interact_callbacks_factory.hh"

InteractCallbackFactory::InteractCallbackFactory() {}
InteractCallbackFactory::~InteractCallbackFactory() {}

AE_InteractCallbacks InteractCallbackFactory::Create() {
	AE_InteractCallbacks product = AE_InteractCallbacks();

	product.CheckoutParam = [] (
		AE_ProgressInfoPtr effect_ref,
		int index,
		int what_time,
		int time_step,
		unsigned int time_scale,
		AE_ParamDef *param
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.checkout_param\"");
		return AE_Error::NONE;
	};

	product.CheckinParam = [](
		AE_ProgressInfoPtr effect_ref,
		AE_ParamDef *param
	) -> AE_Error {
		LOG_INFO ("Called \"AE_InteractCallbacks.checkin_param\"");
		return AE_Error::NONE;
	};

	product.add_param = [] (
		AE_ProgressInfoPtr    effect_ref,
		int                   index,
		AE_ParamDefPtr        def
	) -> int {
		AE_Error error = AE_Error::NONE;

		ParamManager::AddParam (effect_ref, *def);

		LOG_DEBUG ("Called: AE_InteractCallbacks::AddParam (");
		LOG_DEBUG ("     from: " << effect_ref);
		LOG_DEBUG ("    index: " << index);
		LOG_DEBUG ("      def: 0x" << def);
		LOG_DEBUG (") -> AE_Error::" << NAMEOF_ENUM(error));

		LOG_INFO ("    parameters: " << ParamManager::GetParamsCount());

		return static_cast<int>(error);
	};

	product.abort = [](AE_ProgressInfoPtr effect_ref) -> int {
		LOG_INFO ("Called \"AE_InteractCallbacks.abort(" << effect_ref << ")\"");
		return 0;
	};

	product.progress = [](AE_ProgressInfoPtr effect_ref, int current, int total) -> int {
		LOG_INFO ("Called \"AE_InteractCallbacks.progress(" << effect_ref << ", " << current << ", " << total << ")\"");
		return 0;
	};

	product.register_ui = [](AE_ProgressInfoPtr effect_ref, AE_CustomUIInfo *custom_info) -> int {
		LOG_INFO ("Called \"AE_InteractCallbacks.register_ui(" << effect_ref << ", " << custom_info << ")\"");
		return 0;
	};

	product.checkout_layer_audio = [](AE_ProgressInfoPtr effect_ref, int index, int start_time, int duration, unsigned int time_scale, unsigned int rate, int bytes_per_sample, int num_channels, int fmt_signed, AE_LayerAudio *audio) -> int {
		LOG_INFO ("Called \"AE_InteractCallbacks.checkout_layer_audio(" << effect_ref << ", " << index << ", " << start_time << ", " << duration << ", " << time_scale << ", " << rate << ", " << bytes_per_sample << ", " << num_channels << ", " << fmt_signed << ", " << audio << ")\"");
		return 0;
	};

	product.checkin_layer_audio = [](AE_ProgressInfoPtr effect_ref, AE_LayerAudio audio) -> int {
		LOG_INFO ("Called \"AE_InteractCallbacks.checkin_layer_audio(" << effect_ref << ", " << audio << ")\"");
		return 0;
	};

	product.get_audio_data = [](AE_ProgressInfoPtr effect_ref, AE_LayerAudio audio, AE_SndSamplePtr *data, int *num_samples, unsigned int *rate, int *bytes_per_sample, int *num_channels, int *fmt_signed) -> int {
		LOG_INFO ("Called \"AE_InteractCallbacks.get_audio_data(" << effect_ref << ", " << audio << ", " << data << ", " << num_samples << ", " << rate << ", " << bytes_per_sample << ", " << num_channels << ", " << fmt_signed << ")\"");
		return 0;
	};

	return product;
}
