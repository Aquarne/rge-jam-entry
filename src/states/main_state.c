#include "main_state.h"

#include "../game.h"
#include "../core/log.h"
#include "../core/input.h"
#include "../graphics/renderer2d.h"

typedef struct MainState MainState;
struct MainState
{
    u8 _;
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
    return true;
}

static void CleanUp(MainState *state)
{
}

static void ProcessInput(MainState *state)
{
}

static void Update(MainState *state, float dt)
{
}

static void Render(MainState *state)
{
    Renderer2D_DrawRect(0, 0, 100, 100, 0xFFAA00FF);
}
