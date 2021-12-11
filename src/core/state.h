#ifndef RGE_CORE_STATE_H
#define RGE_CORE_STATE_H

#include "defs.h"

typedef bool (*StateInitFn)(void*);
typedef void (*StateCleanUpFn)(void*);
typedef void (*StateProcessInputFn)(void*);
typedef void (*StateUpdateFn)(void*, float);
typedef void (*StateRenderFn)(void*);

typedef struct State State;
struct State
{
    size_t size;
    StateInitFn init;
    StateCleanUpFn clean_up;
    StateProcessInputFn process_input;
    StateUpdateFn update;
    StateRenderFn render;
};

typedef enum StateIndex StateIndex;
enum StateIndex
{
    STATE_INDEX_MAINSTATE,
    STATE_INDEX_COUNT
};

#endif
