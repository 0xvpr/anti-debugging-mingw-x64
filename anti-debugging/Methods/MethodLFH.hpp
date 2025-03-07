#pragma once
#include <windows.h>
#include <iostream>


bool MethodLFH() {
	auto processHeap = reinterpret_cast<uintptr_t>(GetProcessHeap());
	//auto LFHPtr = reinterpret_cast<VOID **>(processHeap + 0xe4);
	auto lfh_ptr = reinterpret_cast<void **>(processHeap + 1024);

	if (lfh_ptr && *lfh_ptr == nullptr) {
		return true;
    }

	return false;
}
