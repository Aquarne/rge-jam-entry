#ifndef RGE_CORE_MEMORY_H
#define RGE_CORE_MEMORY_H

#include "defs.h"
#include "error.h"

Error Alloc(size_t size, void **out);
Error ReAlloc(void *block, size_t new_size, void **out);
void Free(void *block);

#endif
