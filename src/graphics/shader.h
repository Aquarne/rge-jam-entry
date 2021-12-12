#ifndef RGE_GRAPHICS_SHADER_H
#define RGE_GRAPHICS_SHADER_H

typedef unsigned int Shader;

Shader Shader_Load(const char *vshader, const char *fshader);
void Shader_Destroy(Shader shader);
void Shader_Bind(Shader shader);

#endif
