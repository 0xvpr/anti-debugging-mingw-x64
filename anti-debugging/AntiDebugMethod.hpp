#pragma once

#include <windows.h>
#include <iostream>
#include <vector>

enum {
    WM_COMMAND_MENU_ID_EXIT  = 1,
    WM_COMMAND_MENU_ID_ABOUT = 2,
    WM_COMMAND_MENU_HELP     = 3
};
// any WM_COMMAND above 90 is for the antiDebugMethods instances.

class AntiDebugMethod
{
private:
	static int current_id; 
	static std::vector<AntiDebugMethod *> allInstances;
	std::string name;
	int id;
	bool enabled = false;
	bool detected = false;
	int windowPosX, windowPosY;
	HWND enableButtonHwnd;
public:
	bool (*funcPtr)();
	static void toggleThisMethod(int id);
	static void mainLoop();
	static bool anyDetection;
	static AntiDebugMethod* getMethodById(int id);

	void toggle();
	AntiDebugMethod(bool (*funcPtrParam)(), int windowPosXParam, int windowPosYParam, std::string nameParam);
	bool checkIfDetected();
	bool createGUI(HWND hWnd);
};
