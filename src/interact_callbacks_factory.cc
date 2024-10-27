#include "interact_callbacks_factory.h"

InteractCallbackFactory::InteractCallbackFactory() {}
InteractCallbackFactory::~InteractCallbackFactory() {}

PF_InteractCallbacks InteractCallbackFactory::Create() {
	PF_InteractCallbacks product = PF_InteractCallbacks();

	product.checkout_param = [](ProgressInfoPtr effect_ref, int index, int what_time, int time_step, unsigned int time_scale, PF_ParamDef *param) -> int {
		std::cout << "Called \"PF_InteractCallbacks.checkout_param\"" << std::endl;
		return 0;
	};

	product.checkin_param = [](ProgressInfoPtr effect_ref, PF_ParamDef *param) -> int {
		std::cout << "Called \"PF_InteractCallbacks.checkin_param\"" << std::endl;
		return 0;
	};

	product.add_param = [](ProgressInfoPtr effect_ref, int index, PF_ParamDefPtr def) -> int {
		std::cout << "Param Type: " << def->param_type << std::endl;
		std::cout << "Param Name: " << def->name << std::endl;
		std::cout << "Valid Min: " << def->u.fs_d.valid_min << std::endl;
		std::cout << "Slider Min: " << def->u.fs_d.slider_min << std::endl;
		std::cout << "Valid Max: " << def->u.fs_d.valid_max << std::endl;
		std::cout << "Slider Max: " << def->u.fs_d.slider_max << std::endl;
		std::cout << "Value: " << def->u.fs_d.value << std::endl;
		std::cout << "Default: " << def->u.fs_d.dephault << std::endl;
		std::cout << "Precision: " << def->u.fs_d.precision << std::endl;
		std::cout << "Display Flags: " << def->u.fs_d.display_flags << std::endl;
		std::cout << "Flags: " << def->u.fs_d.fs_flags << std::endl;
		std::cout << "Curve Tolerance: " << def->u.fs_d.curve_tolerance << std::endl;
		std::cout << "ID: " << def->uu.id << std::endl;

		return 0;
	};

	product.abort = [](ProgressInfoPtr effect_ref) -> int {
		std::cout << "Called \"PF_InteractCallbacks.abort(" << effect_ref << ")\"" << std::endl;
		return 0;
	};

	product.progress = [](ProgressInfoPtr effect_ref, int current, int total) -> int {
		std::cout << "Called \"PF_InteractCallbacks.progress(" << effect_ref << ", " << current << ", " << total << ")\"" << std::endl;
		return 0;
	};

	product.register_ui = [](ProgressInfoPtr effect_ref, PF_CustomUIInfo *custom_info) -> int {
		std::cout << "Called \"PF_InteractCallbacks.register_ui(" << effect_ref << ", " << custom_info << ")\"" << std::endl;
		return 0;
	};

	product.checkout_layer_audio = [](ProgressInfoPtr effect_ref, int index, int start_time, int duration, unsigned int time_scale, unsigned int rate, int bytes_per_sample, int num_channels, int fmt_signed, PF_LayerAudio *audio) -> int {
		std::cout << "Called \"PF_InteractCallbacks.checkout_layer_audio(" << effect_ref << ", " << index << ", " << start_time << ", " << duration << ", " << time_scale << ", " << rate << ", " << bytes_per_sample << ", " << num_channels << ", " << fmt_signed << ", " << audio << ")\"" << std::endl;
		return 0;
	};

	product.checkin_layer_audio = [](ProgressInfoPtr effect_ref, PF_LayerAudio audio) -> int {
		std::cout << "Called \"PF_InteractCallbacks.checkin_layer_audio(" << effect_ref << ", " << audio << ")\"" << std::endl;
		return 0;
	};

	product.get_audio_data = [](ProgressInfoPtr effect_ref, PF_LayerAudio audio, PF_SndSamplePtr *data, int *num_samples, unsigned int *rate, int *bytes_per_sample, int *num_channels, int *fmt_signed) -> int {
		std::cout << "Called \"PF_InteractCallbacks.get_audio_data(" << effect_ref << ", " << audio << ", " << data << ", " << num_samples << ", " << rate << ", " << bytes_per_sample << ", " << num_channels << ", " << fmt_signed << ")\"" << std::endl;
		return 0;
	};

	return product;
}
