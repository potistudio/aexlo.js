
#include "Generic.h"
#define SPAPI

typedef int32 SPErr;
typedef int32 SPBoolean;

typedef struct SPBasicSuite{
	SPAPI SPErr (*AcquireSuite)( const char *name, int32 version, const void **suite );
	SPAPI SPErr (*ReleaseSuite)( const char *name, int32 version );
	SPAPI SPBoolean (*IsEqual)( const char *token1, const char *token2 );
	SPAPI SPErr (*AllocateBlock)( size_t size, void **block );
	SPAPI SPErr (*FreeBlock)( void *block );
	SPAPI SPErr (*ReallocateBlock)( void *block, size_t newSize, void **newblock );
	SPAPI SPErr (*Undefined)( void );
} SPBasicSuite;
