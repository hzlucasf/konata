# konata

## Install

```sh
git clone https://github.com/hzlucasf/konata

cd konata

cmake .

sudo make install
```

## Examples

```C
#include <knt.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    String foo = knt_string_from("foo"); // The String 'foo' is dynamically allocated in memory

    if (foo == NULL)
    {
        // knt_string_from returns NULL if it was not possible to dynamically allocate memory

        return EXIT_FAILURE;
    }

    printf("'foo': \"%s\"\n", knt_string_as_str(foo)); // knt_string_as_str returns the representation of a String as a string literal

    // knt_drop_string(foo); // Necessary if you are using MSVC

    return EXIT_SUCCESS;
} // The String 'foo' is automatically deallocated from memory if you are using GCC or Clang

```

```C
#include <knt.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    String foo = knt_string_from("foo");

    if (foo == NULL)
    {
        return EXIT_FAILURE;
    }

    printf("'foo': \"%s\"\n", knt_string_as_str(foo));
    
    // knt_string_push adds a character to the end of a String. It returns true if the character was added successfully and false otherwise
    if (!knt_string_push(foo, '_'))
    {
        return EXIT_FAILURE;
    }

    printf("'foo': \"%s\"\n", knt_string_as_str(foo));

    // knt_string_push adds a string literal to the end of a String. It returns true if the character was added successfully and false otherwise
    if (!knt_string_push_str(foo, "bar"))
    {
        return EXIT_FAILURE;
    }

    printf("'foo': \"%s\"\n", knt_string_as_str(foo));

    return EXIT_SUCCESS;
}

```
