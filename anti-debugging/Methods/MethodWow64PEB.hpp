#pragma once

#include <windows.h>

extern "C" bool check_x64_peb();

inline bool MethodWow64PEB()
{
	// auto peb32 = (unsigned char *)__readfsdword( 0x30 );
	// ^ uncomment this and you'll see that the 32bit PEB check will be passed, but this one wont.
	//return check_x64_peb( );
    
	auto peb64 = (unsigned char *)__readgsqword( 0x60 );
    bool is_debugger_present = *( peb64 + 0x2 );

    return is_debugger_present;
}
