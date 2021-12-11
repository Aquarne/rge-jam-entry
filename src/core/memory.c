#include "memory.h"

#include <stdlib.h>

Error Alloc(size_t size, void **out)
{
    void *ret = malloc(size);
    if (!ret)
    {
        return RGE_OUT_OF_MEMORY;
    }

    *out = ret;

    return RGE_NO_ERROR;
}

Error ReAlloc(void *block, size_t new_size, void **out)
{
    void *ret = realloc(block, new_size);
    if (!ret)
    {
        return RGE_OUT_OF_MEMORY;
    }

    *out = ret;

    return RGE_NO_ERROR;
}

void Free(void *block)
{
    free(block);
}
