#include "shader.h"
#include "gl.h"

#include "../game.h"
#include "../core/log.h"

#include <stdio.h>

static char* ReadFile(const char *path, size_t *size)
{
    char *buf = NULL;

    FILE *file = fopen(path, "rb");
    if (!file)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long long file_size = ftell(file);
    rewind(file);

    buf = StackAllocator_Alloc(&g_Game.resource_stack, file_size + 1);

    size_t bytes_read = fread(buf, 1, file_size, file);
    if (bytes_read != file_size)
    {
        LogError("Failed to properly read file %s", path);
        StackAllocator_Free(&g_Game.resource_stack, file_size + 1);
        goto end;
    }
    buf[file_size] = '\0';

    *size = file_size + 1;

end:
    fclose(file);

    return buf;
}

static unsigned int CompileShader(const char *path, int type)
{
    GL_CALL(unsigned int shader = glCreateShader(type));

    size_t size = 0;
    char *src = ReadFile(path, &size);
    if (!src)
    {
        goto end;
    }

    GL_CALL(glShaderSource(shader, 1, &src, NULL));
    GL_CALL(glCompileShader(shader));

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
