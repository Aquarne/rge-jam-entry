#include "shader.h"
#include "gl.h"

#include "../game.h"
#include "../core/file.h"
#include "../core/log.h"

static unsigned int CompileShader(const char *path, int type)
{
    GL_CALL(unsigned int shader = glCreateShader(type));

    size_t size = 0;
    char *src = (char*)ReadFile(path, &size);
    if (!src)
    {
        goto end;
    }
    
    {
        int sizei = (int)size;
        GL_CALL(glShaderSource(shader, 1, &src, &sizei));
        GL_CALL(glCompileShader(shader));
    }

    int success;
    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        int info_log_length = 0;
        GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length));

        char *info_log = StackAllocator_Alloc(&g_Game.resource_stack, info_log_length);
        GL_CALL(glGetShaderInfoLog(shader, info_log_length, NULL, info_log));
        
        LogError("Failed to compile shader %s: %s", path, info_log);
        
        StackAllocator_Free(&g_Game.resource_stack, info_log_length);
    }

    StackAllocator_Free(&g_Game.resource_stack, size);

end:
    return shader;
}

Shader Shader_Load(const char *vshader, const char *fshader)
{
    GL_CALL(unsigned int shader = glCreateProgram());

    unsigned int vs = CompileShader(vshader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fshader, GL_FRAGMENT_SHADER);

    GL_CALL(glAttachShader(shader, vs));
    GL_CALL(glAttachShader(shader, fs));
    GL_CALL(glLinkProgram(shader));

    int success;
    GL_CALL(glGetProgramiv(shader, GL_LINK_STATUS, &success));
    if (!success)
    {
        int info_log_length = 0;
        GL_CALL(glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &info_log_length));

        char *info_log = StackAllocator_Alloc(&g_Game.resource_stack, info_log_length);
        GL_CALL(glGetProgramInfoLog(shader, info_log_length, NULL, info_log));

        LogError("Failed to link shaders %s and %s: %s", vshader, fshader, info_log);

        StackAllocator_Free(&g_Game.resource_stack, info_log_length);
    }

    GL_CALL(glValidateProgram(shader));

    GL_CALL(glGetProgramiv(shader, GL_VALIDATE_STATUS, &success));
    if (!success)
    {
        int info_log_length = 0;
        GL_CALL(glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &info_log_length));

        char *info_log = StackAllocator_Alloc(&g_Game.resource_stack, info_log_length);
        GL_CALL(glGetProgramInfoLog(shader, info_log_length, NULL, info_log));

        LogError("Failed to validate shaders %s and %s: %s", vshader, fshader, info_log);

        StackAllocator_Free(&g_Game.resource_stack, info_log_length);
    }

    GL_CALL(glDeleteShader(vs));
    GL_CALL(glDeleteShader(fs));

    return shader;
}

void Shader_Destroy(Shader shader)
{
    GL_CALL(glDeleteProgram(shader));
}

void Shader_Bind(Shader shader)
{
    GL_CALL(glUseProgram(shader));
}
