
{
	"targets": [{
		"target_name": "aexlo",
		"sources": [ "src/main.cc" ],
		'include_dirs': [ "<!@(node -p \"require('node-addon-api').include\")" ],
		'dependencies': [ "<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except" ],
		'defines': [ 'NAPI_CPP_EXCEPTIONS' ],
		# "cflags!": [ "-fno-exceptions" ],
		# "cflags_cc!": [ "-fno-exceptions" ]
	}]
}
