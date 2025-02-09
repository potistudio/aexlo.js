
{
	"targets": [{
		"target_name": "aexlo",
		"sources": [
			"src/main.cc",
			"src/parameter_manager.cc",
			"src/parameter_parser.cc",
			"src/plugin_instance.cc",
			"src/plugin_instance_wrapper.cc",
			"src/factories/channel_suite_1_factory.cc",
			"src/factories/interact_callbacks_factory.cc",
			"src/factories/suite/ansi_callbacks_suite_factory.cc",
			"src/factories/utility_callbacks_factory.cc",
			"src/factories/suite/channel_suite_1_factory.cc",
			"src/factories/suite/effect_ui_suite_1_factory.cc",
			"src/factories/suite/handler_suite_1_factory.cc",
			"src/factories/suite/iterate_8_suite_2_factory.cc",
			"src/factories/suite/world_transform_suite_factory.cc"
		],
		'include_dirs': [ "<!@(node -p \"require('node-addon-api').include\")" ],
		'dependencies': [ "<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except" ],
		'defines': [ 'NAPI_CPP_EXCEPTIONS' ],
		# "cflags!": [ "-fno-exceptions" ],
		# "cflags_cc!": [ "-fno-exceptions" ]
	}]
}
