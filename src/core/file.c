#include "file.h"

#include "../game.h"
#include "../core/log.h"

#include <stdio.h>

u8* ReadFile(const char *path, size_t *size)
{
    u8 *buf = NULL;

    FILE *file = fopen(path, "rb");
    if (!file)
    {
        LogError("Failed to open file %s", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long long file_size = ftell(file);
    rewind(file);

    buf = StackAllocator_Alloc(&g_Game.resource_stack, file_size);

    size_t bytes_read = fread(buf, 1, file_size, file);
    if (bytes_read != file_size)
    {
        LogError("Failed to properly read file %s", path);
        StackAllocator_Free(&g_Game.resource_stack, file_size);
        goto end;
    }

    *size = file_size;

end:
    fclose(file);

    return buf;
}
