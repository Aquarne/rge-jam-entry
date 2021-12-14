#ifndef RGE_GRAPHICS_RENDERER_2D_H
#define RGE_GRAPHICS_RENDERER_2D_H

#include "../core/defs.h"

bool Renderer2D_Init();
void Renderer2D_CleanUp();

void Renderer2D_SetClearColor(u32 color);

void Renderer2D_Clear();
void Renderer2D_DrawRect(int x, int y, int width, int height, u32 color);
void Renderer2D_DrawTexturedRect(int x , int y, int width, int height, u32 color, unsigned int texture_id);

#endif
