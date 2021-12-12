#include "shader.h"
#include "gl.h"

#include "../core/log.h"
#include "../core/memory.h"

#include <stdio.h>

static char* ReadFile(const char *path)
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

    {
        Error e = Alloc(file_size + 1, &buf);
        if (e != RGE_NO_ERROR)
        {
            LogError("Failed to read file %s: %s", path, ErrorToString(e));
            goto end;
        }
    }

    size_t bytes_read = fread(buf, 1, file_size, file);
    if (bytes_read != file_size)
    {
        LogError("Failed to properly read file %s", path);
        Free(buf);
        goto end;
    }
    buf[file_size] = '\0';

end:
    fclose(file);

    return buf;
}

static unsigned int CompileShader(const char *path, int type)
{
    GL_CALL(unsigned int shader = glCreateShader(type));

    char *src = ReadFile(path);
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
        char info_log[1024];
        GL_CALL(glGetShaderInfoLog(shader, 1024, NULL, info_log));
        LogError("Failed to compile shader %s: %s", path, info_log);
    }

    Free(src);

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
        char info_log[1024];
        GL_CALL(glGetProgramInfoLog(shader, 1024, NULL, info_log));
        LogError("Failed to link shaders %s and %s: %s", vshader, fshader, info_log);
    }

    GL_CALL(glValidateProgram(shader));

    GL_CALL(glGetProgramiv(shader, GL_VALIDATE_STATUS, &success));
    if (!success)
    {
        char info_log[1024];
        GL_CALL(glGetProgramInfoLog(shader, 1024, NULL, info_log));
        LogError("Failed to validate shaders %s and %s: %s", vshader, fshader, info_log);
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
