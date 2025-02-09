#pragma once

#include <windows.h>
#include <iostream>
#include <math.h>

#include "../../headers/suites/ansi_callback_suite.hh"

#include "../../logger/logger.hh"

class ANSICallbacksSuiteFactory {
	public:
		static AE_ANSICallbacksSuite *Create() {
			AE_ANSICallbacksSuite *suite = new AE_ANSICallbacksSuite();

			suite->sin = [](double x) -> double {
				double result = sin (x);

				LOG_DEBUG ("Called: ANSICallbacksSuite::Sin (");
				LOG_DEBUG ("    x: " << x);
				LOG_DEBUG (") -> " << result);

				return result;
			};

			suite->cos = [](double x) -> double {
				double result = cos (x);

				LOG_DEBUG ("Called: ANSICallbacksSuite::Cos (");
				LOG_DEBUG ("    x: " << x);
				LOG_DEBUG (") -> " << result);

				return result;
			};

			suite->tan = [](double x) -> double {
				double result = tan (x);
				LOG_INFO ("Called: ANSICallbacksSuite::tan (" << x << ")" << "  ==> " << result);
				return result;
			};

			suite->asin = [](double x) -> double {
				double result = asin (x);
				LOG_INFO ("Called: ANSICallbacksSuite::asin (" << x << ")" << "  ==> " << result);
				return 0;
			};

			suite->acos = [](double x) -> double {
				double result = acos (x);
				LOG_INFO ("Called: ANSICallbacksSuite::acos (" << x << ")" << "  ==> " << result);
				return 0;
			};

			suite->atan = [](double x) -> double {
				double result = atan (x);
				LOG_INFO ("Called: ANSICallbacksSuite::atan (" << x << ")" << "  ==> " << result);
				return result;
			};

			suite->atan2 = [](double y, double x) -> double {
				double result = atan2 (y, x);
				LOG_INFO ("Called: ANSICallbacksSuite::atan2 (" << y << ", " << x << ")" << "  ==> " << result);
				return result;
			};

			suite->log = [](double x) -> double {
				double result = log (x);
				LOG_INFO ("Called: ANSICallbacksSuite::log (" << x << ")" << "  ==> " << result);
				return result;
			};

			suite->log10 = [](double x) -> double {
				double result = log10 (x);
				LOG_INFO ("Called: ANSICallbacksSuite::log10 (" << x << ")" << "  ==> " << result);
				return result;
			};

			suite->ceil = [](double x) -> double {
				LOG_INFO ("ceil: " << x);
				return 0;
			};

			suite->exp = [](double x) -> double {
				LOG_INFO ("exp: " << x);
				return 0;
			};

			suite->fabs = [](double x) -> double {
				double result = abs (x);
				LOG_INFO ("Called: ANSICallbacksSuite::fabs (" << x << ")" << "  ==> " << result);
				return result;
			};

			suite->floor = [](double x) -> double {
				LOG_INFO ("floor: " << x);
				return 0;
			};

			suite->fmod = [](double x, double y) -> double {
				LOG_INFO ("fmod: " << x);
				return 0;
			};

			suite->hypot = [](double x, double y) -> double {
				LOG_INFO ("hypot: " << x);
				return 0;
			};

			suite->pow = [](double x, double y) -> double {
				double result = pow (x, y);

				LOG_INFO ("Called: ANSICallbacksSuite::pow (" << x << ", " << y << ")" << "  ==> " << result);

				return result;
			};

			suite->sqrt = [](double x) -> double {
				LOG_INFO ("sqrt: " << x);
				return 0;
			};

			suite->sprintf = [](char *buffer, const char *format, ...) -> int {
				va_list args;
				va_start (args, format);

				vsnprintf (buffer, 1024, format, args);

				LOG_DEBUG ("Called: ANSICallbacksSuite::sprintf (");
				LOG_DEBUG ("    format:\n\"\"\"" << format << "\n\"\"\"");
				LOG_DEBUG ("      args: " << args);
				LOG_DEBUG (")  --> \n\"\"\"\n" << buffer << "\n\"\"\"");

				va_end (args);

				return 0;
			};

			suite->strcpy = [](char *dest, const char *src) -> char * {
				strcpy (dest, src);
				LOG_INFO (dest);

				return 0;
			};

			return suite;
		}
};
