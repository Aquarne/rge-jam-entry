#include "stack_allocator.h"

#include "../core/assert.h"
#include "../core/memory.h"

Error StackAllocator_Init(StackAllocator *stack, size_t size)
{
    ASSERT(stack != NULL);

    void *block = NULL;
    Error e = Alloc(size, &block);

    stack->bottom = block;
    stack->top = block;
    stack->marker = block;
    stack->capacity = e == RGE_NO_ERROR ? size : 0;

    return e;
}

void StackAllocator_Destroy(StackAllocator *stack)
{
    ASSERT(stack != NULL);

    Free(stack->bottom);

    stack->bottom = NULL;
    stack->top = NULL;
    stack->marker = NULL;
    stack->capacity = 0;
}

void* StackAllocator_Alloc(StackAllocator *stack, size_t size)
{
    ASSERT(stack != NULL);
    ASSERT((stack->top + size) <= (stack->bottom + stack->capacity));

    void *block = (void*)stack->top;
    stack->top += size;

    return block;
}

void StackAllocator_SetMarker(StackAllocator *stack)
{
    stack->marker = stack->top;
}

void StackAllocator_ClearToMarker(StackAllocator *stack)
{
    stack->top = stack->marker;
}

void StackAllocator_Clear(StackAllocator *stack)
{
    stack->top = stack->bottom;
}
