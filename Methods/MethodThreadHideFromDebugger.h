#pragma once

#include <windows.h>
#include <winternl.h>
#include <iostream>

static THREADINFOCLASS ThreadHideFromDebugger_{ (THREADINFOCLASS)0x11 };
static bool hasNtSetInformationThreadRun = false;

typedef NTSTATUS(WINAPI* NtSetInformationThread_t)(HANDLE, THREADINFOCLASS, PVOID, ULONG);
typedef NTSTATUS (WINAPI *NtQueryInformationThread_t)(HANDLE, THREADINFOCLASS, PVOID, ULONG, PULONG);

static NtSetInformationThread_t fnNtSetInformationThread = nullptr;
static NtQueryInformationThread_t fnNtQueryInformationThread = nullptr;


bool MethodThreadHideFromDebugger() {

    HANDLE hThread = GetCurrentThread();
    fnNtSetInformationThread = (NtSetInformationThread_t)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtSetInformationThread");
    fnNtQueryInformationThread = (NtQueryInformationThread_t)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationThread");

	if (hasNtSetInformationThreadRun == false)
	{
        NTSTATUS errorCode = fnNtSetInformationThread(hThread, ThreadHideFromDebugger_, nullptr, 0);
        hasNtSetInformationThreadRun = true;        
	}

    unsigned char lHideThreadQuery = false;
    ULONG lRet = 0;

    NTSTATUS errorCode = fnNtQueryInformationThread(hThread, ThreadHideFromDebugger_, &lHideThreadQuery, sizeof(lHideThreadQuery), &lRet);
    CloseHandle(hThread);

	return false; //it will crash if its detected anyway 
}
