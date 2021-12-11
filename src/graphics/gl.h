#ifndef RGE_GRAPHICS_GL_H
#define RGE_GRAPHICS_GL_H

#include <glad/glad.h>

#define GL_CALL(x) \
    GLClearErrors(); \
    x; \
    GLGetErrors("\\" __FILE__, __LINE__)

void GLClearErrors();
void GLGetErrors(const char *file, int line);

#endif
