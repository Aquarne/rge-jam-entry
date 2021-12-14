#ifndef RGE_GRAPHICS_TEXTURE_H
#define RGE_GRAPHICS_TEXTURE_H

#include "../core/defs.h"

typedef struct Texture Texture;
struct Texture
{
    unsigned int id;
    unsigned int width;
    unsigned int height;
};

bool Texture_Load(const char *path, Texture *texture);
void Texture_Destroy(Texture *texture);
void Texture_Bind(unsigned int texture_id, unsigned int index);
void Texture_Unbind(unsigned int index);

#endif
