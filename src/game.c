#include "game.h"

#include "core/assert.h"
#include "core/log.h"
#include "core/input.h"

#include "states/main_state.h"

#include <string.h>

Game g_Game;

static State game_states[STATE_INDEX_COUNT];

static bool State_Init();
static void State_CleanUp();
static void State_ProcessInput();
static void State_Update(float dt);
static void State_Render();

static void PollEvents();
static void Render();

bool InitGame()
{
    bool success = true;

    if (!glfwInit())
    {
        LogFatal("Failed to initialise GLFW!");
        success = false;
        goto end;
    }

    g_Game.is_running = false;
    memset(g_Game.prev_keys, 0, sizeof(g_Game.prev_keys));

    g_Game.requested_state = -1;
    game_states[STATE_INDEX_MAINSTATE] = GetMainState();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    g_Game.window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        WINDOW_TITLE,
        NULL,
        NULL
    );
    if (!g_Game.window)
    {
        LogFatal("Failed to create window!");
        success = false;
        goto end;
    }
    glfwMakeContextCurrent(g_Game.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LogFatal("Failed to load OpenGL!");
        success = false;
        goto end;
    }

    {
        Error e = StackAllocator_Init(&g_Game.resource_stack, RESOURCE_STACK_SIZE);
        if (e != RGE_NO_ERROR)
        {
            LogFatal("Failed to initialise resource stack: %s!", ErrorToString(e));
            success = false;
            goto end;
        }
    }
    
    StackAllocator_SetMarker(&g_Game.resource_stack);

    g_Game.state = game_states[0];
    g_Game.state_data = StackAllocator_Alloc(&g_Game.resource_stack, g_Game.state.size);

    if (!State_Init())
    {
        LogFatal("Failed to initialise main state!");
    }

end:
    return success;
}

void RunGame()
{
    g_Game.is_running = true;

    while (g_Game.is_running)
    {
        if (g_Game.requested_state >= 0)
        {
            ASSERT(g_Game.requested_state < STATE_INDEX_COUNT);
            
            State_CleanUp();
            StackAllocator_ClearToMarker(&g_Game.resource_stack);

            g_Game.state = game_states[g_Game.requested_state];
            g_Game.state_data = StackAllocator_Alloc(&g_Game.resource_stack, g_Game.state.size);
            
            if (!State_Init())
            {
                LogFatal("Failed to initialise state!");
                break;
            }
        }

        PollEvents();

        State_ProcessInput();
        State_Update(0);

        Render();
    }
}

void TerminateGame()
{
    State_CleanUp();
    StackAllocator_Destroy(&g_Game.resource_stack);
    glfwDestroyWindow(g_Game.window);
    glfwTerminate();
}

static void PollEvents()
{
    for (int i = 0; i < GLFW_KEY_LAST+1; i++)
    {
        g_Game.prev_keys[i] = GetKey(i);
    }

    glfwPollEvents();

    if (glfwWindowShouldClose(g_Game.window))
    {
        g_Game.is_running = false;
    }
}

static void Render()
{
    State_Render();

    glfwSwapBuffers(g_Game.window);
}

static bool State_Init()
{
    bool ret = true;

    if (g_Game.state.init)
    {
        ret = g_Game.state.init(g_Game.state_data);
    }

    return ret;
}

static void State_CleanUp()
{
    if (g_Game.state.clean_up)
    {
        g_Game.state.clean_up(g_Game.state_data);
    }
}

static void State_ProcessInput()
{
    if (g_Game.state.process_input)
    {
        g_Game.state.process_input(g_Game.state_data);
    }
}

static void State_Update(float dt)
{
    if (g_Game.state.update)
    {
        g_Game.state.update(&g_Game.state_data, dt);
    }
}

static void State_Render()
{
    if (g_Game.state.render)
    {
        g_Game.state.render(&g_Game.state_data);
    }
}
