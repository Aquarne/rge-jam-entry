#ifndef RGE_CORE_ERROR_H
#define RGE_CORE_ERROR_H

typedef enum Error Error;
enum Error
{
    RGE_NO_ERROR,
    RGE_OUT_OF_MEMORY
};

const char* ErrorToString(Error e);

#endif
