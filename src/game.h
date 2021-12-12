#ifndef RGE_GAME_H
#define RGE_GAME_H

#include "core/defs.h"
#include "core/state.h"
#include "allocators/stack_allocator.h"
#include "graphics/gl.h"

#include "glfw/glfw3.h"

#define WINDOW_TITLE  "Roguelike"
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

#define RESOURCE_STACK_SIZE MiB(200)

typedef struct Game Game;
struct Game
{
    StackAllocator resource_stack;
    GLFWwindow *window;
    State state;
    void *state_data;
    int requested_state;
    int cursor_pos_x;
    int cursor_pos_y;
    float scroll_x;
    float scroll_y;
    unsigned int fps;
    bool prev_keys[GLFW_KEY_LAST+1];
    bool prev_mouse_buttons[GLFW_MOUSE_BUTTON_LAST+1];
    bool is_running;
};

extern Game g_Game;

bool InitGame();
void RunGame();
void TerminateGame();

void RequestState(int index);

#endif
