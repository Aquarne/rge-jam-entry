#include "threads.h"

#include <Windows.h>

bool Thread_Create(Thread *thread, ThreadFn proc, void *context)
{
    thread->handle = CreateThread(
        NULL,
        0,
        proc,
        context,
        0,
        &thread->id
    );

    return thread->handle != NULL;
}

void Thread_Destroy(Thread *thread)
{
    if (thread->handle)
    {
        CloseHandle(thread->handle);
    }
}

void Thread_Exit(u32 exit_code)
{
    ExitThread(exit_code);
}

void Thread_Terminate(Thread *thread, u32 exit_code)
{
    if (thread->handle)
    {
        // Thread requires the THREAD_TERMINATE access right.
        TerminateThread(thread->handle, exit_code);
    }
}

void Thread_Yield()
{
    SwitchToThread();
}

void Thread_Join(Thread *thread)
{
    if (thread->handle)
    {
        // WaitForSingleObject may return an error.
        while (WaitForSingleObject(thread->handle, 0))
        {
            Thread_Yield();
        }
    }
}

void Thread_Sleep(u32 ms)
{
    Sleep(ms);
}
