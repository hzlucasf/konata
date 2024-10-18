#pragma once

//

#include <stdint.h>

//

typedef uint8_t u8;

#if defined(__i386__) || defined(_WIN32)
typedef uint32_t u32;
#elif defined(__x86_64__) || defined(_WIN64)
typedef uint64_t u64;
#endif

// str_dup

char* str_dup(const char*);

// sub_str

#if defined(__i386__) || defined(_WIN32)
char* sub_str(const char*, u32, u32);
#elif defined(__x86_64__) || defined(_WIN64)
char* sub_str(const char*, u64, u64);
#endif
