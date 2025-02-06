#pragma once
#pragma pack (push, AE, 8)

#include "./errors.hh"

struct SPBasicSuite {
	AE_Error (*AcquireSuite) (
		const char      *name,
		int             version,
		const void**    suite
	);

	AE_Error (*ReleaseSuite) (
		const char    *name,
		int           version
	);

	AE_Error (*IsEqual) (
		const char    *token1,
		const char    *token2
	);

	AE_Error (*AllocateBlock) (
		size_t    size,
		void      **block
	);

	AE_Error (*FreeBlock) (void *block);

	AE_Error (*ReallocateBlock) (
		void      *block,
		size_t    newSize,
		void      **newblock
	);

	AE_Error (*Undefined) (void);
};

#pragma pack (pop, AE)
