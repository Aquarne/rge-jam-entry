#ifndef RGE_CORE_DEFS_H
#define RGE_CORE_DEFS_H

#include <stddef.h>
#include <stdint.h>

#define false 0
#define true  1

#define KiB(x) (x * 1024)
#define MiB(x) KiB(x * 1024)
#define GiB(x) MiB(x * 1024)

typedef _Bool bool;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#endif
