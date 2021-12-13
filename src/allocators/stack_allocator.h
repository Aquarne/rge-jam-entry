#ifndef RGE_ALLOCATORS_STACK_ALLOCATOR_H
#define RGE_ALLOCATORS_STACK_ALLOCATOR_H

#include "../core/defs.h"
#include "../core/error.h"

typedef struct StackAllocator StackAllocator;
struct StackAllocator
{
    u8 *bottom;
    u8 *top;
    u8 *marker;
    size_t capacity;
};

Error StackAllocator_Init(StackAllocator *stack, size_t size);
void StackAllocator_Destroy(StackAllocator *stack);
void* StackAllocator_Alloc(StackAllocator *stack, size_t size);
void StackAllocator_Free(StackAllocator *stack, size_t size);
void StackAllocator_SetMarker(StackAllocator *stack);
void StackAllocator_ClearToMarker(StackAllocator *stack);
void StackAllocator_Clear(StackAllocator *stack);

#endif
