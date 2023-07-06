#pragma once

#include "global.h"
#include "structs.h"

NAMESPACE(Hooks)

typedef uint64_t(*gfxLoader_t)(long long a1, const char *path, long long a3, unsigned int a4, unsigned int a5);
extern gfxLoader_t gfxLoader_Stub;
uint64_t gfxLoader_hook(long long a1, const char *path, long long a3, unsigned int a4, unsigned int a5);
END
