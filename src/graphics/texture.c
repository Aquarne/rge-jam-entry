#include "texture.h"
#include "gl.h"

#include "../game.h"
#include "../core/assert.h"
#include "../core/file.h"
#include "../core/log.h"

#include <stb/stb_image.h>

bool Texture_Load(const char *path, Texture *texture)
{
    bool success = true;

    Texture ret = { 0 };

    size_t size = 0;
    u8 *compressed_data = NULL;
    u8 *raw_data = NULL;

    GL_CALL(glGenTextures(1, &ret.id));

    compressed_data = ReadFile(path, &size);
    if (!compressed_data)
    {
        success = false;
        goto end;
    }

    stbi_set_flip_vertically_on_load(true);

    int x, y, channels;
    raw_data = stbi_load_from_memory(compressed_data, (int)size, &x, &y, &channels, 4);
    if (!raw_data)
    {
        LogError("Failed to load image %s", path);
        success = false;
        goto end;
    }

    GL_CALL(glBindTexture(GL_TEXTURE_2D, ret.id));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, raw_data));
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    ret.width = x;
    ret.height = y;

end:
    *texture = ret;

    stbi_image_free(raw_data);
    StackAllocator_Free(&g_Game.resource_stack, size);

    return success;
}

void Texture_Destroy(Texture *texture)
{
    GL_CALL(glDeleteTextures(1, &texture->id));

    texture->id = 0;
    texture->width = 0;
    texture->height = 0;
}

void Texture_Bind(unsigned int texture_id, unsigned int index)
{
    ASSERT(index < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    GL_CALL(glActiveTexture(GL_TEXTURE0 + index));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture_id));
}

void Texture_Unbind(unsigned int index)
{
    ASSERT(index < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    GL_CALL(glActiveTexture(GL_TEXTURE0 + index));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
