#include "AntiDebugMethod.hpp"

#include "Methods/MethodIsDebuggerPresent.hpp"
#include "Methods/MethodUnhandledException.hpp"
#include "Methods/MethodCheckRemoteDebuggerPresent.hpp"
#include "Methods/MethodPEBBeingDebugged.hpp"
#include "Methods/MethodNtGlobalFlag.hpp"
#include "Methods/MethodGetParentProcess.hpp"
#include "Methods/MethodWow64PEB.hpp"
#include "Methods/MethodThreadHideFromDebugger.hpp"
#include "Methods/MethodTrapFlag.hpp"
#include "Methods/MethodGetLocalTime.hpp"
#include "Methods/MethodGetTickCount.hpp"
#include "Methods/MethodQPC.hpp"
#include "Methods/MethodHeapFlag.hpp"
#include "Methods/MethodLFH.hpp"

#include <shellapi.h>
#include <tchar.h>



static HMENU hMenu;
static HBITMAP hLogoImage;
static HWND hLogo;
static HWND hDetectedMessage;



static void AddControls( HWND hWnd ) {
	hDetectedMessage = CreateWindowA( "static", "You're doing good. No debugger has been detected yet!", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 60, 300, 40, hWnd, nullptr, nullptr, nullptr );
	int cur_x = 20, cur_y = 100;
	using fnptr = bool( * )( void );
	auto AddMethod = [ & ]( fnptr fn, const char * name )
	{
		auto methamphetamine = new AntiDebugMethod( fn, cur_x, cur_y, name );
		if ( cur_x == 20 )
			cur_x = 270;
		else
		{
			cur_x = 20;
			cur_y += 60;

			if ( cur_y > 220 ) // idk random number
			{
				RECT r{ };
				GetWindowRect( hWnd, &r );
				SetWindowPos( hWnd, 0, 0, 0, r.right - r.left, ( r.bottom - r.top ) + 50, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER );
				// automatically resize window as we add more methods.
			}
		}

		methamphetamine->createGUI( hWnd );
	};

	AddMethod( MethodIsDebuggerPresent,          "IsDebuggerPresent()" );
	AddMethod( MethodPEBBeingDebugged,           "PEB->BeingDebugged" );
	AddMethod( MethodNtGlobalFlag,               "NtGlobalFlag" );
	AddMethod( MethodCheckRemoteDebuggerPresent, "CheckRemoteDebuggerPresent()" );
	AddMethod( MethodGetParentProcess,           "Check Parent Process (CreateToolhelp32Snapshot)" );
	AddMethod( MethodUnhandledException,         "UnhandledExceptionFilter" );
	AddMethod( MethodWow64PEB,                   "WoW64 PEB->BeingDebugged" );
	AddMethod( MethodThreadHideFromDebugger,     "ThreadHideFromDebugger (will crash if debugged)" );
	AddMethod( MethodTrapFlag,                   "SEH & TrapFlag Detection");
	AddMethod( MethodLFH,                        "(busted) LowFragmentationHeap Detection");
	AddMethod( MethodHeapFlags,                  "(busted) Heap Flags Detection");
	AddMethod( MethodGetLocalTime,               "GetLocalTime Detection");
	AddMethod( MethodGetTickCount,               "GetTickCount Detection");
	AddMethod( MethodQPC,                        "QueryPerformanceCounter Detection");

	hLogo = CreateWindowA( "static", nullptr, WS_VISIBLE | WS_CHILD | SS_BITMAP, -10, 0, 100, 100, hWnd, nullptr, nullptr, nullptr );
	SendMessageA( hLogo, STM_SETIMAGE, IMAGE_BITMAP, ( LPARAM )hLogoImage );
}

static void LoadImages( HWND hwnd ) {
	hLogoImage = ( HBITMAP )LoadImageA( nullptr, "new_logo.bmp", IMAGE_BITMAP, 538, 0, LR_LOADFROMFILE );
	HANDLE hIcon = LoadImage( 0, _T( "gh.ico" ), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE );
	if ( hIcon ) {
		//Change both icons to the same icon handle.
		SendMessage( hwnd, WM_SETICON, ICON_SMALL, ( LPARAM )hIcon );
		SendMessage( hwnd, WM_SETICON, ICON_BIG, ( LPARAM )hIcon );

		//This will ensure that the application icon gets changed too.
		SendMessage( GetWindow( hwnd, GW_OWNER ), WM_SETICON, ICON_SMALL, ( LPARAM )hIcon );
		SendMessage( GetWindow( hwnd, GW_OWNER ), WM_SETICON, ICON_BIG, ( LPARAM )hIcon );
	}

}

static void AddMenus( HWND hWnd ) {
	hMenu = CreateMenu( );
	HMENU hFileMenu = CreateMenu( );

	AppendMenuA( hFileMenu, MF_STRING, WM_COMMAND_MENU_ID_EXIT, "Exit" );

	AppendMenuA( hMenu, MF_POPUP, ( UINT_PTR )hFileMenu, "File" );
	AppendMenuA( hMenu, MF_STRING, WM_COMMAND_MENU_ID_ABOUT, "About" );
	AppendMenuA(hMenu, MF_STRING, WM_COMMAND_MENU_HELP, "Help");

	SetMenu( hWnd, hMenu );
}

static LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp ) {
	switch ( msg )
	{
	case WM_COMMAND:
		std::cout << "lp: " << lp << "\n";
		std::cout << "wp: " << wp << "\n";

		switch ( wp ) {
		case WM_COMMAND_MENU_ID_EXIT:
			MessageBoxA( nullptr, "Who clicks exit on the File menu? Just click the X icon u dumb fuck.", "Exit", MB_ICONINFORMATION );

			// DestroyWindow(hWnd);
			break;
		case WM_COMMAND_MENU_ID_ABOUT:
			MessageBoxA( nullptr, "v1.0.0\n\nBy: RyccoSN \n\n\n www.guidedhacking.com", "About", MB_OK );
			break;
		case WM_COMMAND_MENU_HELP:
			ShellExecuteA(nullptr, "open", "https://guidedhacking.com/threads/anti-debug-techniques-a-comprehensive-guide.20391/", nullptr, nullptr, SW_SHOWNORMAL);
			break;
		}

		if ( wp >= 90 )
		{
			AntiDebugMethod::toggleThisMethod( 0b11111111 & (wp - 90) );
		}
		break;
	case WM_CREATE:
		LoadImages( hWnd );
		AddMenus( hWnd );
		AddControls( hWnd );
		break;
	case WM_DESTROY:
#if _DEBUG
		FreeConsole( );
		fclose( fp );
#endif
		ExitProcess( 0 );
		break;
	default:
		return DefWindowProcA( hWnd, msg, wp, lp );
	}

	return 0;
}


int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow )
{
    UNREFERENCED_PARAMETER(hPrevInst);
    UNREFERENCED_PARAMETER(args);
    UNREFERENCED_PARAMETER(ncmdshow);

#if _DEBUG
	AllocConsole( );
	freopen_s( &fp, "CONOUT$", "w", stdout );
#endif

	WNDCLASSA wc{ };
	wc.hbrBackground = ( HBRUSH )COLOR_WINDOW;
	wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wc.hInstance = hInst;
	wc.lpszClassName = "MainWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if ( !RegisterClassA( &wc ) )
	{
		return -1;
	}
	CreateWindowA( "MainWindowClass", "Guided Hacking - Debugme (VPR mod)", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 538, 380, nullptr, nullptr, nullptr, nullptr );

	MSG msg{ };
	while ( true )
	{
		if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		bool localAnyDetection = AntiDebugMethod::anyDetection;
		AntiDebugMethod::mainLoop( );
		if ( localAnyDetection != AntiDebugMethod::anyDetection )
		{
			if ( AntiDebugMethod::anyDetection )
			{
				SendMessageA( hDetectedMessage, WM_SETTEXT, 0, ( LPARAM )"Busted! You've been detected!" );
			}
			else {
				SendMessageA( hDetectedMessage, WM_SETTEXT, 0, ( LPARAM )"You're doing good. No debugger has been detected yet!" );
			}
		}
	}


	return 0;
}

