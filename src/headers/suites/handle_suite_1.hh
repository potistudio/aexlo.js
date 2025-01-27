#pragma once

#include <stdint.h>

struct PF_HandleSuite1 {
	void * (*HostNewHandle)(uint64_t);
	void * (*HostLockHandle)(void *);
	void (*HostUnlockHandle)(void *);
	void (*HostDisposeHandle)(void *);
	uint64_t (*HostGetHandleSize)(void *);
	int (*HostResizeHandle)(uint64_t, void **);
};
