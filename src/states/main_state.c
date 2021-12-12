#include "main_state.h"

#include "../game.h"
#include "../core/log.h"
#include "../core/input.h"
#include "../graphics/gl.h"
#include "../graphics/shader.h"

typedef struct MainState MainState;
struct MainState
{
    Shader shader;
    unsigned int vao;
    unsigned int vbo;
};

static bool Init(MainState *state);
static void CleanUp(MainState *state);
static void ProcessInput(MainState *state);
static void Update(MainState *state, float dt);
static void Render(MainState *state);

State GetMainState()
{
    return (State) {
        .size = sizeof(MainState),
        .init = Init,
        .clean_up = CleanUp,
        .process_input = ProcessInput,
        .update = Update,
        .render = Render
    };
}

static bool Init(MainState *state)
{
    state->shader = Shader_Load("shaders/basic2DVertex.shader", "shaders/basic2DFragment.shader");

    const float vertices[] = {
        -1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f
    };

    GL_CALL(glGenVertexArrays(1, &state->vao));
    GL_CALL(glBindVertexArray(state->vao));
    
    GL_CALL(glGenBuffers(1, &state->vbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, state->vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glEnableVertexAttribArray(1));

    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float))));

    GL_CALL(glBindVertexArray(0));

    return true;
}

static void CleanUp(MainState *state)
{
    GL_CALL(glDeleteBuffers(1, &state->vbo));
    GL_CALL(glDeleteVertexArrays(1, &state->vao));
    Shader_Destroy(state->shader);
}

static void ProcessInput(MainState *state)
{
}

static void Update(MainState *state, float dt)
{
}

static void Render(MainState *state)
{
    Shader_Bind(state->shader);
    GL_CALL(glBindVertexArray(state->vao));
    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
}
