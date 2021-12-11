#include "main_state.h"

#include "../game.h"
#include "../core/log.h"
#include "../core/input.h"

static void ProcessInput(void *state);
static void Update(void *state, float dt);
static void Render(void *state);

State GetMainState()
{
    return (State) {
        .size = 0,
        .init = NULL,
        .clean_up = NULL,
        .process_input = ProcessInput,
        .update = Update,
        .render = Render
    };
}

static void ProcessInput(void *state)
{
    if (GetKeyDown(GLFW_KEY_A))
    {
        LogTrace("Key A down!");
    }
    else if (GetKeyUp(GLFW_KEY_A))
    {
        LogTrace("Key A up!");
    }
}

static void Update(void *state, float dt)
{
}

static void Render(void *state)
{
}
