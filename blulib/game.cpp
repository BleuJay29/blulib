#include "blulib.h"
#include <Windows.h>
using namespace Blu;
void Blu::Update(Input* input) {
	GAME_NAME = "Spinning";
	ClearScreen(0x000000);
	
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmd, int nCmdShow) {
	Blu::BluMain(hInstance, prevInstance, nCmdShow);
}