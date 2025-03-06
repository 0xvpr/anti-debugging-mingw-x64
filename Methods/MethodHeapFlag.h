#pragma once

#include <windows.h>
#include <iostream>

bool MethodHeapFlags() {
    auto processHeap = reinterpret_cast<uintptr_t>(GetProcessHeap());
    auto Flags = reinterpret_cast<uintptr_t*>(processHeap + 0x40);
    auto ForceFlags = reinterpret_cast<uintptr_t*>(processHeap + 0x44);

    return(*Flags != HEAP_GROWABLE || *ForceFlags != 0);
}
