
{
	"targets": [{
		"target_name": "aexlo",
		"sources": [
			"src/main.cc",
			"src/plugin_instance.cc",
			"src/plugin_instance_wrapper.cc",
			"src/interact_callbacks_factory.cc",
			"src/utility_callbacks_factory.cc",
			"src/factories/channel_suite_1_factory.cc",
		],
		'include_dirs': [ "<!@(node -p \"require('node-addon-api').include\")", "src" ],
		'dependencies': [ "<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except" ],
		'defines': [ 'NAPI_CPP_EXCEPTIONS' ],
		# "cflags!": [ "-fno-exceptions" ],
		# "cflags_cc!": [ "-fno-exceptions" ]
	}]
}
