#include "assert.h"

#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#else
    #error "Compiler not supported!"
#endif

void Assert(const char *message, const char *file, int line)
{
    const char *filename = strrchr(file, '\\') + 1;

    fprintf(stderr, "[ASSERT] at %s:%d : %s\n", filename, line, message);
    DEBUG_BREAK();
}
