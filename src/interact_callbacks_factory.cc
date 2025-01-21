#include "interact_callbacks_factory.hh"

InteractCallbackFactory::InteractCallbackFactory() {}
InteractCallbackFactory::~InteractCallbackFactory() {}

PF_InteractCallbacks InteractCallbackFactory::Create() {
	PF_InteractCallbacks product = PF_InteractCallbacks();

	product.checkout_param = [](ProgressInfoPtr effect_ref, int index, int what_time, int time_step, unsigned int time_scale, PF_ParamDef *param) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.checkout_param\"");
		return 0;
	};

	product.checkin_param = [](ProgressInfoPtr effect_ref, PF_ParamDef *param) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.checkin_param\"");
		return 0;
	};

	product.add_param = [](ProgressInfoPtr effect_ref, int index, PF_ParamDefPtr def) -> int {
		LOG_INFO ("Called: InteractCallbacks::add_param (" << "index: " << index << ")");

		LOG_INFO ("  ==> ID: " << def->uu.id);
		LOG_INFO ("  ==> Param Name: " << def->name);
		LOG_INFO ("  ==> Param Type: " << def->param_type);

		LOG_INFO ("  ==> Valid Min: " << def->u.fs_d.valid_min);
		LOG_INFO ("  ==> Valid Max: " << def->u.fs_d.valid_max);

		LOG_INFO ("  ==> Slider Min: " << def->u.fs_d.slider_min);
		LOG_INFO ("  ==> Slider Max: " << def->u.fs_d.slider_max);

		LOG_INFO ("  ==> Value: " << def->u.fs_d.value);
		LOG_INFO ("  ==> Default: " << def->u.fs_d.dephault);

		LOG_INFO ("  ==> Precision: " << def->u.fs_d.precision);
		LOG_INFO ("  ==> Curve Tolerance: " << def->u.fs_d.curve_tolerance);

		LOG_INFO ("  ==> Display Flags: " << def->u.fs_d.display_flags);
		LOG_INFO ("  ==> Flags: " << def->u.fs_d.fs_flags);

		return 0;
	};

	product.abort = [](ProgressInfoPtr effect_ref) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.abort(" << effect_ref << ")\"");
		return 0;
	};

	product.progress = [](ProgressInfoPtr effect_ref, int current, int total) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.progress(" << effect_ref << ", " << current << ", " << total << ")\"");
		return 0;
	};

	product.register_ui = [](ProgressInfoPtr effect_ref, PF_CustomUIInfo *custom_info) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.register_ui(" << effect_ref << ", " << custom_info << ")\"");
		return 0;
	};

	product.checkout_layer_audio = [](ProgressInfoPtr effect_ref, int index, int start_time, int duration, unsigned int time_scale, unsigned int rate, int bytes_per_sample, int num_channels, int fmt_signed, PF_LayerAudio *audio) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.checkout_layer_audio(" << effect_ref << ", " << index << ", " << start_time << ", " << duration << ", " << time_scale << ", " << rate << ", " << bytes_per_sample << ", " << num_channels << ", " << fmt_signed << ", " << audio << ")\"");
		return 0;
	};

	product.checkin_layer_audio = [](ProgressInfoPtr effect_ref, PF_LayerAudio audio) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.checkin_layer_audio(" << effect_ref << ", " << audio << ")\"");
		return 0;
	};

	product.get_audio_data = [](ProgressInfoPtr effect_ref, PF_LayerAudio audio, PF_SndSamplePtr *data, int *num_samples, unsigned int *rate, int *bytes_per_sample, int *num_channels, int *fmt_signed) -> int {
		LOG_INFO ("Called \"PF_InteractCallbacks.get_audio_data(" << effect_ref << ", " << audio << ", " << data << ", " << num_samples << ", " << rate << ", " << bytes_per_sample << ", " << num_channels << ", " << fmt_signed << ")\"");
		return 0;
	};

	return product;
}
