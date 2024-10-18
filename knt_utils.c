#include "knt_utils.h"

//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// str_dup

char* str_dup(const char* str)
{
#if defined(__i386__) || defined(_WIN32)
    u32 len = strlen(str);
#elif defined(__x86_64__) || defined(_WIN64)
    u64 len = strlen(str);
#endif

    char* result = calloc(len + 1, 1);

    if (result == NULL)
    {
        return NULL;
    }

#if defined(__i386__) || defined(_WIN32)
    u32 i = 0;
#elif defined(__x86_64__) || defined(_WIN64)
    u64 i = 0;
#endif

    for (; i < len; i += 1)
    {
        result[i] = str[i];
    }

    return result;
}

// sub_str

#if defined(__i386__) || defined(_WIN32)
char* sub_str(const char* str, u32 start_index, u32 end_index)
{
    if (str == NULL)
    {
        return NULL;
    }

    u32 len = end_index - start_index;

    char* result = malloc(len + 1);

    if (result == NULL)
    {
        return NULL;
    }

    u32 j = 0;

    for (u32 i = start_index; i < end_index; i += 1)
    {
        result[j] = str[i];

        j += 1;
    }

    result[j] = '\0';

    return result;
}
#elif defined(__x86_64__) || defined(_WIN64)
char* sub_str(const char* str, u64 start_index, u64 end_index)
{
    if (str == NULL)
    {
        return NULL;
    }

    u64 len = end_index - start_index;

    char* result = calloc(len + 1, 1);

    if (result == NULL)
    {
        return NULL;
    }

    u64 j = 0;

    for (u64 i = start_index; i < end_index; i += 1)
    {
        result[j] = str[i];

        j += 1;
    }

    result[j] = '\0';

    return result;
}
#endif
