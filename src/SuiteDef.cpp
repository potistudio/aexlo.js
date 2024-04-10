
#include "Generic.h"

typedef int32 SPErr;
typedef int32 SPBoolean;

typedef struct SPBasicSuite {
	SPErr (*AcquireSuite)(const char *name, int32 version, const void** suite);
	SPErr (*ReleaseSuite)(const char *name, int32 version);
	SPBoolean (*IsEqual)(const char *token1, const char *token2);
	SPErr (*AllocateBlock)(size_t size, void **block);
	SPErr (*FreeBlock)(void *block);
	SPErr (*ReallocateBlock)(void *block, size_t newSize, void **newblock);
	SPErr (*Undefined)(void);
} SPBasicSuite;
