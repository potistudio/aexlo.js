#pragma once

#include <stdint.h>

#include "../../headers/common.hh"
#include "../../headers/suites/handle_suite_1.hh"

#include "../../logger/logger.hh"

class HandlerSuite1Factory {
	public:
		static AE_HandleSuite1* Create() {
			AE_HandleSuite1 *suite = new AE_HandleSuite1();

			suite->HostNewHandle = [](uint64_t size) -> void * {
				LOG_INFO ("New Handle: " << size);
				AE_Handle *handle = new AE_Handle();
				return handle;
			};

			suite->HostLockHandle = [](void *handle) -> void * {
				LOG_INFO ("Lock Handle: " << handle);
				return new AE_Handle();
			};

			suite->HostUnlockHandle = [](void *handle) -> void {
				LOG_INFO ("Unlock Handle: " << handle);
			};

			suite->HostDisposeHandle = [](void *handle) -> void {
				LOG_INFO ("Dispose Handle: " << handle);
			};

			suite->HostGetHandleSize = [](void *handle) -> uint64_t {
				LOG_INFO ("Get Handle Size: " << handle);
				return 0;
			};

			suite->HostResizeHandle = [](uint64_t size, void **handle) -> int {
				LOG_INFO ("Resize Handle: " << size);
				return 0;
			};

			return suite;
		}
};
