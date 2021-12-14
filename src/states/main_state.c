#include "main_state.h"

#include "../game.h"
#include "../core/log.h"
#include "../core/input.h"
#include "../graphics/texture.h"
#include "../graphics/renderer2d.h"

typedef struct MainState MainState;
struct MainState
{
    Texture texture;
    int rect_pos_x;
    int rect_pos_y;
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
    bool success = true;
    
    if (!Texture_Load("assets/images/UFDK2_kinoko_Header.png", &state->texture))
    {
        success = false;
        goto end;
    }

    state->texture.width *= (float)WINDOW_HEIGHT/state->texture.height;
    state->texture.height = WINDOW_HEIGHT;

    state->rect_pos_x = WINDOW_WIDTH - 100;
    state->rect_pos_y = WINDOW_HEIGHT - 100;

end:
    return success;
}

static void CleanUp(MainState *state)
{
    Texture_Destroy(&state->texture);
}

static void ProcessInput(MainState *state)
{
}

static void Update(MainState *state, float dt)
{
}

static void Render(MainState *state)
{
    Renderer2D_DrawTexturedRect(0, 0, state->texture.width, state->texture.height, -1, state->texture.id);
    Renderer2D_DrawRect(state->rect_pos_x, state->rect_pos_y, 100, 100, 0xFF5500FF);
}
