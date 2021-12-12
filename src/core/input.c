#include "input.h"
#include "../game.h"

bool GetKey(int key)
{
    return glfwGetKey(g_Game.window, key);
}

bool GetKeyDown(int key)
{
    return GetKey(key) && !g_Game.prev_keys[key];
}

bool GetKeyUp(int key)
{
    return !GetKey(key) && g_Game.prev_keys[key];
}

bool GetMouseButton(int button)
{
    return glfwGetMouseButton(g_Game.window, button);
}

bool GetMouseButtonDown(int button)
{
    return GetMouseButton(button) && !g_Game.prev_mouse_buttons[button];
}

bool GetMouseButtonUp(int button)
{
    return !GetMouseButton(button) && g_Game.prev_mouse_buttons[button];
}

void SetCursorMode(int mode)
{
    glfwSetInputMode(g_Game.window, GLFW_CURSOR, mode);
}

void GetCursorPosition(int *x, int *y)
{
    *x = g_Game.cursor_pos_x;
    *y = g_Game.cursor_pos_y;
}

void GetMouseScroll(float *x, float *y)
{
    *x = g_Game.scroll_x;
    *y = g_Game.scroll_y;
}
