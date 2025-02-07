
{
	"targets": [{
		"target_name": "aexlo",
		"sources": [
			"src/main.cc",
			"src/plugin_instance.cc",
			"src/plugin_instance_wrapper.cc",
			"src/factories/interact_callbacks_factory.cc",
			"src/factories/utility_callbacks_factory.cc",
			"src/factories/channel_suite_1_factory.cc",
			"src/parameter_manager.cc",
		],
		'include_dirs': [ "<!@(node -p \"require('node-addon-api').include\")" ],
		'dependencies': [ "<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except" ],
		'defines': [ 'NAPI_CPP_EXCEPTIONS' ],
		# "cflags!": [ "-fno-exceptions" ],
		# "cflags_cc!": [ "-fno-exceptions" ]
	}]
}
