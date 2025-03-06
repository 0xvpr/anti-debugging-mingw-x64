#pragma once

#include <windows.h>
#include <iostream>

bool MethodGetTickCount() {


    //DWORD tickReference = GetTickCount64();
    DWORD tickReference = GetTickCount();

    Sleep(50); 

    //DWORD currentTick = GetTickCount64();
    DWORD currentTick = GetTickCount();
    DWORD elapsedTime = currentTick - tickReference;

    if (elapsedTime > 100)
        return true;

    return false;
}
