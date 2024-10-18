#include "knt.h"
#include "knt_utils.h"

//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//

u8 knt_last_err = KNT_NO_ERR;

// _String

typedef struct _String
{
    char* buf;

#if defined(__i386__) || defined(_WIN32)
    u32 len;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 len;
#endif

#if defined(__i386__) || defined(_WIN32)
    u32 capacity;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 capacity;
#endif
} _String;

// knt_string_new

_String* knt_string_new(void)
{
    knt_last_err = KNT_NO_ERR;

    _String* s = malloc(sizeof(_String));

    if (s == NULL)
    {
        knt_last_err = KNT_MEM_ALLOC_ERR;

        return NULL;
    }

    s->buf = malloc(10);

    if (s->buf == NULL)
    {
        knt_last_err = KNT_MEM_ALLOC_ERR;

        free(s);

        return NULL;
    }

    s->len = 0;

    s->capacity = 10;

    return s;
}

// knt_string_from

_String* knt_string_from(const char* str)
{
    if (str == NULL)
    {
        return NULL;
    }

    _String* s = malloc(sizeof(_String));

    if (s == NULL)
    {
        knt_last_err = KNT_MEM_ALLOC_ERR;

        return NULL;
    }

    s->buf = str_dup(str);

    if (s->buf == NULL)
    {
        knt_last_err = KNT_MEM_ALLOC_ERR;

        free(s);

        return NULL;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 len = strlen(str);
#elif defined(__x86_64__) || defined(_WIN64)
    u64 len = strlen(str);
#endif

    void* ptr = realloc(s->buf, len + 1 + 10);

    if (ptr == NULL)
    {
        free(s->buf);

        free(s);

        return NULL;
    }

    s->buf = ptr;

    s->len = strlen(str);

    s->capacity = len + 1 + 10;

    return s;
}

// (_knt_drop_string/knt_drop_string)

#if defined (__GNUC__) || defined(__clang__)
void _knt_drop_string(_String** ptr)
{
    if (ptr == NULL || *ptr == NULL)
    {
        return;
    }

    free((*ptr)->buf);

    free(*ptr);

    *ptr = NULL;
}
#else
void knt_drop_string(_String* ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    free(ptr->buf);

    free(ptr);
}
#endif

// knt_string_as_str

const char* knt_string_as_str(_String* s)
{
    if (s == NULL)
    {
        return "(null)";
    }

    return s->buf;
}

// knt_string_len

#if defined(__i386__) || defined(_WIN32)
u32 knt_string_len(_String* s)
{
    if (s == NULL)
    {
        return 0;
    }

    return s->len;
}
#elif defined(__x86_64__) || defined(_WIN64)
u64 knt_string_len(_String* s)
{
    if (s == NULL)
    {
        return 0;
    }

    return s->len;
}
#endif

// knt_string_capacity

#if defined(__i386__) || defined(_WIN32)
u32 knt_string_capacity(_String* s)
{
    if (s == NULL)
    {
        return 0;
    }

    return s->capacity;
}
#elif defined(__x86_64__) || defined(_WIN64)
u64 knt_string_capacity(_String* s)
{
    if (s == NULL)
    {
        return 0;
    }

    return s->capacity;
}
#endif

// knt_string_clear

bool knt_string_clear(_String* s)
{
    if (s == NULL)
    {
        return false;
    }

    s->len = 0;

    return true;
}

// knt_string_is_empty

bool knt_string_is_empty(const _String* s)
{
    if (s == NULL)
    {
        return false;
    }

    return s->len == 0;
}

// knt_string_push

bool knt_string_push(_String* s, char c)
{
    if (s == NULL)
    {
        return false;
    }

    if (s->len == s->capacity - 1)
    {
        void* ptr = realloc(s->buf, s->capacity * 2);

        if (ptr == NULL)
        {
            return false;
        }

        s->buf = ptr;

        s->capacity *= 2;
    }

    s->buf[s->len] = c;

    s->buf[s->len + 1] = '\0';

    s->len += 1;

    return true;
}

// knt_string_push_str

bool knt_string_push_str(_String* s, const char* str)
{
    if (s == NULL || str == NULL)
    {
        return false;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 new_len = s->len + strlen(str);
#elif defined(__x86_64__) || defined(_WIN64)
    u64 new_len = s->len + strlen(str);
#endif

    if (new_len >= s->capacity)
    {
        void* ptr = realloc(s->buf, new_len + 1 + s->capacity * 2);

        if (ptr == NULL)
        {
            return false;
        }

        s->buf = ptr;

        s->capacity = new_len + 1 + s->capacity * 2;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 i = 0;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 i = 0;
#endif

    for (; i < new_len - s->len + 1; i += 1)
    {
        s->buf[s->len + i] = str[i];
    }

    s->len = new_len;

    return true;
}

// knt_string_to_lowercase

bool knt_string_to_lowercase(_String* s)
{
    if (s == NULL)
    {
        return false;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 i = 0;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 i = 0;
#endif

    for (; i < s->len ; i += 1)
    {
        if (s->buf[i] >= 'a' && s->buf[i] <= 'z')
        {
            s->buf[i] -= 32;
        }
    }

    return true;
}

// knt_string_to_uppercase

bool knt_string_to_uppercase(_String* s)
{
    if (s == NULL)
    {
        return false;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 i = 0;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 i = 0;
#endif

    for (; i < s->len ; i += 1)
    {
        if (s->buf[i] >= 'a' && s->buf[i] <= 'z')
        {
            s->buf[i] += 32;
        }
    }

    return true;
}

// knt_read_line

bool knt_read_line(_String* s)
{
    while (true)
    {
        char c = getchar();

        if (c == EOF)
        {
            break;
        }

        bool ok = knt_string_push(s, c);

        if (!ok)
        {
            return false;
        }

        if (c == '\n')
        {
            return true;
        }
    }

    return true;
}

// knt_string_trim

bool knt_string_trim(_String* s)
{
    if (s == NULL)
    {
        return false;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 string_len = s->len;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 string_len = s->len;
#endif

#if defined(__i386__) || defined(_WIN32)
    u32 start_index = 0;

    u32 end_index = string_len - 1;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 start_index = 0;

    u64 end_index = string_len - 1;
#endif

    for (; start_index < end_index; start_index += 1)
    {
        if (s->buf[start_index] != '\n' && s->buf[start_index] != ' ')
        {
            break;
        }
    }

    for (; end_index > start_index; end_index -= 1)
    {
        if (s->buf[end_index] != '\n' && s->buf[end_index] != ' ')
        {
            break;
        }
    }

    if (end_index < string_len - 1)
    {
        end_index += 1;
    }

    char* tmp = sub_str(s->buf, start_index, end_index);

    if (tmp == NULL)
    {
        return false;
    }

    void* ptr = realloc(tmp, s->capacity);

    if (ptr == NULL)
    {
        free(tmp);

        return false;
    }

    free(s->buf);

    s->buf = ptr;

    s->len = strlen(s->buf);

    return true;
}

// knt_string_eq

bool knt_string_eq(_String* x, _String* y)
{
    if (x == NULL || y == NULL)
    {
        return false;
    }

    if (x->len != y->len)
    {
        return false;
    }

    return strcmp(x->buf, y->buf) == 0;
}

// knt_string_add

bool knt_string_add(_String* x, _String* y)
{
    if (x == NULL || y == NULL)
    {
        return false;
    }

    if (x->len + y->len >= x->capacity)
    {
        void* ptr = realloc(x->buf, x->len + 1 + y->len + 1 + (x->capacity * 2) + (y->capacity * 2));

        if (ptr == NULL)
        {
            return false;
        }

        x->buf = ptr;

        x->capacity = x->len + 1 + y->len + 1 + (x->capacity * 2) + (y->capacity * 2);
    }

#if defined(__i386__) || defined(_WIN32)
    u32 i = 0;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 i = 0;
#endif

    for (; i < y->len + 1; i += 1)
    {
        x->buf[x->len + i] = y->buf[i];
    }

    x->len += y->len;

    return true;
}
