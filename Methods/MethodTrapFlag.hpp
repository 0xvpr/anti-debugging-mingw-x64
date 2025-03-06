#pragma once

#include <windows.h>
#include <iostream>

inline bool MethodTrapFlag()
{
    try {
        __asm__ volatile (
            "pushfq\n\t"
            "or word ptr[esp], 0x100\n\t"
            "popfq\n\t"
            "nop\n\t"
            :
            :
            : "memory", "cc"
    );

    } catch (...) {
        return false;
    }

    return true;
}
