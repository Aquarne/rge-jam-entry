#include "game.h"

#include "core/assert.h"
#include "core/log.h"
#include "core/input.h"
#include "core/threads.h"

#include "graphics/renderer2d.h"

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

static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

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
    g_Game.fps = 0;

    g_Game.scroll_x = 0;
    g_Game.scroll_y = 0;
    g_Game.cursor_pos_x = 0;
    g_Game.cursor_pos_y = 0;
    memset(g_Game.prev_keys, 0, sizeof(g_Game.prev_keys));
    memset(g_Game.prev_mouse_buttons, 0, sizeof(g_Game.prev_mouse_buttons));

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

    glfwSetCursorPosCallback(g_Game.window, CursorPosCallback);
    glfwSetScrollCallback(g_Game.window, ScrollCallback);

    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    {
        Error e = StackAllocator_Init(&g_Game.resource_stack, RESOURCE_STACK_SIZE);
        if (e != RGE_NO_ERROR)
        {
            LogFatal("Failed to initialise resource stack: %s!", ErrorToString(e));
            success = false;
            goto end;
        }
    }
 
    if (!Renderer2D_Init())
    {
        LogFatal("Failed to initialise 2D Renderer!");
        success = false;
        goto end;
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

    unsigned int frames = 0;
    double frame_counter = 0;

    double prev_time = glfwGetTime();

    while (g_Game.is_running)
    {
        double now = glfwGetTime();
        double dt = now - prev_time;
        prev_time = now;

        frame_counter += dt;

        if (frame_counter >= 1.0)
        {
            LogInfo("FPS: %u", frames);
            g_Game.fps = frames;
            frames = 0;
            frame_counter = 0;
        }

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

            g_Game.requested_state = -1;
        }

        PollEvents();

        State_ProcessInput();
        State_Update(dt);

        Render();

        ++frames;

        Thread_Yield();
    }
}

void TerminateGame()
{
    State_CleanUp();
    StackAllocator_Destroy(&g_Game.resource_stack);
    Renderer2D_CleanUp();
    glfwDestroyWindow(g_Game.window);
    glfwTerminate();
}

static void PollEvents()
{
    g_Game.scroll_x = 0;
    g_Game.scroll_y = 0;

    for (int i = 0; i < GLFW_KEY_LAST+1; i++)
    {
        g_Game.prev_keys[i] = GetKey(i);
    }

    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST+1; i++)
    {
        g_Game.prev_mouse_buttons[i] = GetMouseButton(i);
    }

    glfwPollEvents();

    if (glfwWindowShouldClose(g_Game.window))
    {
        g_Game.is_running = false;
    }
}

static void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    State_Render();

    glfwSwapBuffers(g_Game.window);
}

static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    g_Game.cursor_pos_x = (int)xpos;
    g_Game.cursor_pos_y = (int)ypos;
}

static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    g_Game.scroll_x = (float)xoffset;
    g_Game.scroll_y = (float)yoffset;
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
        g_Game.state.update(g_Game.state_data, dt);
    }
}

static void State_Render()
{
    if (g_Game.state.render)
    {
        g_Game.state.render(g_Game.state_data);
    }
}
