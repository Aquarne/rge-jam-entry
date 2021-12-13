#include "renderer2d.h"
#include "shader.h"
#include "gl.h"

#include "../core/log.h"

#define UNIFORM_LOCATION_COLOR  0

struct Renderer2D
{
    Shader shader;
    unsigned int rect_vao;
    unsigned int rect_vbo;
    unsigned int rect_ibo;
} g_Renderer2D;

bool Renderer2D_Init()
{
    g_Renderer2D.shader = Shader_Load("shaders/renderer2d.vs", "shaders/renderer2d.fs");

    const float vertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    const unsigned int indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    GL_CALL(glGenVertexArrays(1, &g_Renderer2D.rect_vao));
    GL_CALL(glGenBuffers(1, &g_Renderer2D.rect_vbo));
    GL_CALL(glGenBuffers(1, &g_Renderer2D.rect_ibo));

    GL_CALL(glBindVertexArray(g_Renderer2D.rect_vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, g_Renderer2D.rect_vbo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Renderer2D.rect_ibo));

    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0));

    GL_CALL(glBindVertexArray(0));

    return true;
}

void Renderer2D_CleanUp()
{
    GL_CALL(glDeleteBuffers(1, &g_Renderer2D.rect_vbo));
    GL_CALL(glDeleteBuffers(1, &g_Renderer2D.rect_ibo));
    Shader_Destroy(g_Renderer2D.shader);
}

void Renderer2D_DrawRect(int x, int y, int width, int height, u32 color)
{
    const float normalised_color[] = {
        ((color & 0xFF000000) >> 24) / 255.0f,
        ((color & 0x00FF0000) >> 16) / 255.0f,
        ((color & 0x0000FF00) >> 8)  / 255.0f,
        (color & 0x000000FF)         / 255.0f
    };

    GL_CALL(glBindVertexArray(g_Renderer2D.rect_vao));

    Shader_Bind(g_Renderer2D.shader);
    GL_CALL(glUniform4fv(UNIFORM_LOCATION_COLOR, 1, normalised_color));

    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}
