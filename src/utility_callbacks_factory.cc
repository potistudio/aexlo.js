#include "utility_callbacks_factory.hh"

UtilityCallbackFactory::UtilityCallbackFactory() {}
UtilityCallbackFactory::~UtilityCallbackFactory() {}

_PF_UtilCallbacks * UtilityCallbackFactory::Create() {
	_PF_UtilCallbacks *product = new _PF_UtilCallbacks();
	product->ansi = PF_ANSICallbacks();

	product->ansi.sprintf = [](char *buffer, const char *format, ...) -> int {
		va_list args;
		va_start (args, format);

		vsnprintf (buffer, 1024, format, args);
		std::cout << buffer << std::endl;

		va_end (args);
		return 0;
	};

	return product;
}
