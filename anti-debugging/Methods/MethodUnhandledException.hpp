#pragma once

#include <windows.h>
#include <iostream>
#include <winternl.h>

static bool hasADbgAttached = true;

LONG WINAPI GetExecutedOnUnhandledException(EXCEPTION_POINTERS * pExceptionInfo) {
    hasADbgAttached = false;

    // thx @mambda for this tip!
#ifndef   __WIN64
    pExceptionInfo->ContextRecord->Eip += 1;
#else
    pExceptionInfo->ContextRecord->Rip += 1;
#endif // __WIN64
    
    return EXCEPTION_CONTINUE_EXECUTION;
}

bool MethodUnhandledException() {
    hasADbgAttached = true;

    SetUnhandledExceptionFilter(
      (LPTOP_LEVEL_EXCEPTION_FILTER) GetExecutedOnUnhandledException
    );

    __debugbreak( );

    return hasADbgAttached;
}
