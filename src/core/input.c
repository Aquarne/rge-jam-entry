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
