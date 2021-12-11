#include "error.h"
#include "defs.h"

const char* ErrorToString(Error e)
{
    switch (e)
    {
    #define ERROR_CASE(e) \
        case e: return #e;

        ERROR_CASE(RGE_NO_ERROR)
        ERROR_CASE(RGE_OUT_OF_MEMORY)

    #undef ERROR_CASE
    }

    return NULL;
}
