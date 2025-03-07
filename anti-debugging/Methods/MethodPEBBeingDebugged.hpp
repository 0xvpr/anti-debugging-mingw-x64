#pragma once

#include <windows.h>
#include <iostream>

__attribute__((naked))
PPEB getPeb(void);

bool MethodPEBBeingDebugged() {
#ifndef   __WIN64
    auto peb = (uintptr_t)__readfsqword(0x30);
#else 
    auto peb = (uintptr_t)__readgsqword(0x60);
#endif // __WIN64 
    return *(((char *)peb)+0x2);
}

__attribute__((naked))
PPEB getPeb() {
    __asm__ volatile (
        "mov rax, gs:[0x60]\n\t"
        "ret\n\t"
    );
}
