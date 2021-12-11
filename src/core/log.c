#include "log.h"

#include <stdio.h>
#include <stdarg.h>

static void Log(FILE *stream, const char *level, const char *format, va_list args)
{
    fprintf(stream, "[%s]\t: ", level);
    vfprintf(stream, format, args);
    fputc('\n', stream);
}

void LogInfo(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Log(stdout, "INFO", format, args);
    va_end(args);
}

void LogTrace(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Log(stdout, "TRACE", format, args);
    va_end(args);
}

void LogError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Log(stderr, "ERROR", format, args);
    va_end(args);
}

void LogFatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Log(stderr, "FATAL", format, args);
    va_end(args);
}
