#ifndef RGE_CORE_THREADS_H
#define RGE_CORE_THREADS_H

#include "defs.h"

typedef u32 (*ThreadFn)(void*);

typedef struct Thread Thread;
struct Thread
{
    void *handle;
    u32 id;
};

bool Thread_Create(Thread *thread, ThreadFn proc, void *context);
void Thread_Destroy(Thread *thread);
void Thread_Exit(u32 exit_code);
void Thread_Terminate(Thread *thread, u32 exit_code);
void Thread_Yield();
void Thread_Join(Thread *thread);
void Thread_Sleep(u32 ms);

#endif
