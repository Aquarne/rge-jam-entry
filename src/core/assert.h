#ifndef RGE_CORE_ASSERT_H
#define RGE_CORE_ASSERT_H

#include "defs.h"

#if defined(RGE_ENABLE_ASSERT)
    #define ASSERT(x) \
        if (!(x)) Assert(#x, "\\" __FILE__, __LINE__)

    void Assert(const char *message, const char *file, int line);
#else
    #define ASSERT(x)
#endif

#endif
