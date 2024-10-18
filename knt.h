#pragma once

//

#include "knt_utils.h"

//

#include <stdint.h>
#include <stdbool.h>

//

typedef uint8_t u8;

//

#define KNT_NO_ERR        0
#define KNT_MEM_ALLOC_ERR 1

extern u8 knt_last_err;

// _String

typedef struct _String _String;

// knt_string_new

_String* knt_string_new(void);

// knt_string_from

_String* knt_string_from(const char*);

// (_knt_drop_string/knt_drop_string)

#if defined (__GNUC__) || defined(__clang__)
void _knt_drop_string(_String**);

#define String __attribute__((cleanup(_knt_drop_string))) _String*
#else
void knt_drop_string(_String*);
#endif

// knt_string_as_str

const char* knt_string_as_str(_String*);

// knt_string_len

#if defined(__i386__) || defined(_WIN32)
u32 knt_string_len(_String*);
#elif defined(__x86_64__) || defined(_WIN64)
u64 knt_string_len(_String*);
#endif

// knt_string_capacity

#if defined(__i386__) || defined(_WIN32)
u32 knt_string_capacity(_String*);
#elif defined(__x86_64__) || defined(_WIN64)
u64 knt_string_capacity(_String*);
#endif

// knt_string_clear

bool knt_string_clear(_String*);

// knt_string_is_empty

bool knt_string_is_empty(const _String*);

// knt_string_push

bool knt_string_push(_String*, char);

// knt_string_push_str

bool knt_string_push_str(_String*, const char*);

// knt_string_to_lowercase

bool knt_string_to_lowercase(_String*);

// knt_string_to_uppercase

bool knt_string_to_uppercase(_String*);

// knt_read_line

bool knt_read_line(_String*);

// knt_string_trim

bool knt_string_trim(_String*);

// knt_string_eq

bool knt_string_eq(_String*, _String*);

// knt_string_add

bool knt_string_add(_String*, _String*);
