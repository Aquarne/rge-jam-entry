#include "gl.h"
#include "../core/log.h"

#include <string.h>

void GLClearErrors()
{
    while (glGetError());
}

void GLGetErrors(const char *file, int line)
{
    const char *filename = strrchr(file, '\\') + 1;

    GLenum error;
    while (error = glGetError())
    {
        switch (error)
        {
        #define ERROR_CASE(e) \
            case e: \
                LogError("OpenGL error at %s:%d: %s\n", filename, line, #e);

            ERROR_CASE(GL_INVALID_ENUM)
            ERROR_CASE(GL_INVALID_VALUE)
            ERROR_CASE(GL_INVALID_OPERATION)
            ERROR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION)
            ERROR_CASE(GL_OUT_OF_MEMORY)

        #undef ERROR_CASE
        }
    }
}
