namespace Blu {
	class Button {
	public:
		Rect hitbox = { 0,0,0,0 };
		HCURSOR finger;
		Button(Rect HITBOX) {
			hitbox = HITBOX;
		}
		bool IsClicked(Input* input) {
			if (colliderect({ GetMousePos().x, GetMousePos().y, 1, 1 }, hitbox)) {
				if (IsDown(LMOUSE)) {
					return true;
				}
			}
			return false;
		}
		bool IsRightClicked(Input* input) {
			if (colliderect({ GetMousePos().x, GetMousePos().y, 1, 1 }, hitbox)) {
				if (IsDown(RMOUSE)) {
					return true;
				}
			}
			return false;
		}
		bool IsOver() {
			if (colliderect({ GetMousePos().x, GetMousePos().y, 1, 1 }, hitbox)) {
				return true;
			}
			return false;
		}
		void draw(u32 color) {
			DrawRect(hitbox, color);
		}
		void runScript(void (*func)(Button&)) {
			func(*this);
		}
	};
}