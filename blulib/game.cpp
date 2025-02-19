#include "blulib.h"
#include <Windows.h>
using namespace Blu;
class Player : public PhysicsBody {
public:
	Player() : PhysicsBody({ 0, 0, 30, 30 }) {}
	void run(Input* input) {
		if (pressed(K_W)) {
			vel.y = -40;
		}
		if (!IsOnFloor) {
			vel.y += 5;
		}
		if (IsDown(K_D)) vel.x += 1;
		else if (IsDown(K_A)) vel.x -= 1;
		else if (vel.x < 0) vel.x += 2;
		else if (vel.x > 0) vel.x -= 2;
		if (pos.y+vel.y > 500) {
			pos.y = 500;
			vel.y = 0;
		}
		update();
	}
};
Player player;
void Blu::Update(Input* input) {
	GAME_NAME = "Spinning";
	ClearScreen(0x000000);
	player.run(input);
	DrawRect(player.hitbox, 0xffffff);
	tick(30);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmd, int nCmdShow) {
	Blu::BluMain(hInstance, prevInstance, nCmdShow);
}