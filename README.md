# libpartition
small library for type-based memory partitioning and allocation

## Installation / Usage

Currently only been built on and tested on macOS but will probably work with linux (gcc or clang) and might even work
on windows with mingw but I'm not sure about that yet.

### Compiling
```bash
git clone https://github.com/zhooda/libpartition
cd libpartition && make
```

### Using the library

Copy `libpartition.a` and `partition.h` from the build directory to your project directory
and include `partition.h` in your C file (libpartition does not explicitly support C++ yet but it might work)

Use the `palloc` macro as a drop in replacement (almost) for `malloc` and `pfree` as a replacement for `free`. **Note: `pfree` is not yet implemented so you will get memory leaks.**

**main.c**
```c
#include "partition.h"
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    // palloc is a macro for __palloc so you dont have to pass
    // in a char* type, you can just pass in the type
    uint32_t *some_ints = (uint32_t *)palloc(sizeof(uint32_t), uint32_t);

    // palloc returns NULL if it can't allocate memory
    if (some_ints == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < 10; i++) {
        some_ints[i] = (uint32_t)i;
    }

    // pfree is a macro for __pfree so you dont have to pass
    // in a char* type, you can just pass in the type
    pfree(some_ints, uint32_t);

    return EXIT_SUCCESS;
}
```

**compiling**
```bash
clang main.c libpartition.a -o main
```