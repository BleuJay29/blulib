#include "blulib.h"
#include <Windows.h>
using namespace Blu;
Transformations Transform;
int i = 0;
void Blu::Update(Input* input) {
	GAME_NAME = "Spinning";
	ClearScreen(0x000000);
	if (IsDown(K_D)) {
		i++;
	}
	Transform.Rotate(i);
	Transform.Translate(200, 0);
	DrawFilledCircle({ 50, 50 }, 50, 0xaa6600);
	DrawFilledCircle({ 50, 150 }, 50, 0xaa6600);
	DrawFilledOval({ 150, 100 }, 100, 50, 0xaa6600);
	DrawFilledArc({ 200, 100 }, 50, 50, -90, 90, 0xaa6600);
	DrawLine({ 225, 100 }, { 250, 100 }, 0x662200);
	DrawLine({ 200, 55 }, { 200, 145 }, 0x662200);
	Transform.reset();
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmd, int nCmdShow) {
	Blu::BluMain(hInstance, prevInstance, nCmdShow);
}