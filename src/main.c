#include "game.h"

int main(int argc, const char **argv)
{
    if (!InitGame())
    {
        return 1;
    }

    RunGame();
    TerminateGame();

    return 0;
}
