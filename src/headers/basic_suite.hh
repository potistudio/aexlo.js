#pragma once

typedef struct SPBasicSuite {
	int (*AcquireSuite)(const char *name, int version, const void** suite);
	int (*ReleaseSuite)(const char *name, int version);
	int (*IsEqual)(const char *token1, const char *token2);
	int (*AllocateBlock)(size_t size, void **block);
	int (*FreeBlock)(void *block);
	int (*ReallocateBlock)(void *block, size_t newSize, void **newblock);
	int (*Undefined)(void);
} SPBasicSuite;
