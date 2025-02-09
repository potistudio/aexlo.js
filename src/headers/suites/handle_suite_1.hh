#pragma once
#pragma pack (push, AE, 8)

struct AE_HandleSuite1 {
	void *             (*HostNewHandle)     (unsigned long long);
	void *             (*HostLockHandle)    (void *);
	void               (*HostUnlockHandle)  (void *);
	void               (*HostDisposeHandle) (void *);
	unsigned long long (*HostGetHandleSize) (void *);
	int                (*HostResizeHandle)  (unsigned long long, void **);
};

#pragma pack (pop, AE)
