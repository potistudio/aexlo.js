#include "utility_callbacks_factory.hh"

UtilityCallbackFactory::UtilityCallbackFactory() {}
UtilityCallbackFactory::~UtilityCallbackFactory() {}

_PF_UtilCallbacks * UtilityCallbackFactory::Create() {
	_PF_UtilCallbacks *product = new _PF_UtilCallbacks();
	product->ansi = PF_ANSICallbacks();

	product->ansi.sin = [](double x) -> double {
		return sin (x);
	};

	product->ansi.cos = [](double x) -> double {
		return cos (x);
	};

	product->ansi.tan = [](double x) -> double {
		return tan (x);
	};

	product->ansi.asin = [](double x) -> double {
		std::cout << "asin: " << x << std::endl;
		return 0;
	};

	product->ansi.acos = [](double x) -> double {
		std::cout << "acos: " << x << std::endl;
		return 0;
	};

	product->ansi.atan = [](double x) -> double {
		std::cout << "atan: " << x << std::endl;
		return 0;
	};

	product->ansi.atan2 = [](double y, double x) -> double {
		std::cout << "atan2: " << x << std::endl;
		return 0;
	};

	product->ansi.log = [](double x) -> double {
		std::cout << "log10: " << x << std::endl;
		return 0;
	};

	product->ansi.log10 = [](double x) -> double {
		std::cout << "log10: " << x << std::endl;
		return 0;
	};

	product->ansi.ceil = [](double x) -> double {
		std::cout << "ceil: " << x << std::endl;
		return 0;
	};

	product->ansi.exp = [](double x) -> double {
		std::cout << "exp: " << x << std::endl;
		return 0;
	};

	product->ansi.fabs = [](double x) -> double {
		std::cout << "fabs: " << x << std::endl;
		return 0;
	};

	product->ansi.floor = [](double x) -> double {
		std::cout << "floor: " << x << std::endl;
		return 0;
	};

	product->ansi.fmod = [](double x, double y) -> double {
		std::cout << "fmod: " << x << std::endl;
		return 0;
	};

	product->ansi.hypot = [](double x, double y) -> double {
		std::cout << "hypot: " << x << std::endl;
		return 0;
	};

	product->ansi.pow = [](double x, double y) -> double {
		std::cout << "pow: " << x << std::endl;
		return 0;
	};

	product->ansi.sqrt = [](double x) -> double {
		std::cout << "sqrt: " << x << std::endl;
		return 0;
	};

	product->ansi.sprintf = [](char *buffer, const char *format, ...) -> int {
		va_list args;
		va_start (args, format);

		vsnprintf (buffer, 1024, format, args);
		std::cout << buffer << std::endl;

		va_end (args);
		return 0;
	};

	product->ansi.strcpy = [](char *dest, const char *src) -> char * {
		strcpy (dest, src);
		std::cout << dest << std::endl;

		return 0;
	};

	return product;
}
