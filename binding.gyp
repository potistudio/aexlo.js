
{
	"targets": [{
		"target_name": "aexlo",
		"sources": [ "src/Main.cpp" ],
		'include_dirs': [ "<!@(node -p \"require('node-addon-api').include\")" ],
		'dependencies': [ "<!(node -p \"require('node-addon-api').gyp\")" ],
		'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
		"cflags!": [ "-fno-exceptions" ],
		"cflags_cc!": [ "-fno-exceptions" ]
	}]
}
