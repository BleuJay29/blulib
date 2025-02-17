namespace Blu {
	void InpOff(Input* input) {
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input->buttons[i].changed = false;
		}
	}
	bool isbudow(Input* input, int b) {
		return input->buttons[b].isdown;
	}
	bool iskbdow(Input* input, Keybind b) {
		int a = 0;
		for (auto bu : b) {
			if (input->buttons[bu].isdown) {
				a++;
			}
		}
		return a > 0;
	}
	bool iskfdow(Input* input, Keyfunc b) {
		int a = 0;
		for (auto bu : b) {
			if (input->buttons[bu].isdown) {
				a++;
			}
		}
		return a == b.size();
	}
	bool isbupre(Input* input, int b) {
		return (input->buttons[b].isdown && input->buttons[b].changed);
	}
	bool iskbpre(Input* input, Keybind b) {
		int a = 0;
		for (auto bu : b) {
			if ((input->buttons[bu].isdown && input->buttons[bu].changed)) {
				a++;
			}
		}
		return a > 0;
	}
	bool iskfpre(Input* input, Keyfunc b) {
		int a = 0;
		for (auto bu : b) {
			if ((input->buttons[bu].isdown && input->buttons[bu].changed)) {
				a++;
			}
		}
		return a == b.size();
	}
	bool isburel(Input* input, int b) {
		return !input->buttons[b].isdown && input->buttons[b].changed;
	}
	bool iskbrel(Input* input, Keybind b) {
		int a = 0;
		for (auto bu : b) {
			if (!input->buttons[bu].isdown && input->buttons[bu].changed) {
				a++;
			}
		}
		return a > 0;
	}
	bool iskfrel(Input* input, Keyfunc b) {
		int a = 0;
		for (auto bu : b) {
			if (!input->buttons[bu].isdown && input->buttons[bu].changed) {
				a++;
			}
		}
		return a == b.size();
	}
#define IsDown(b) isbudow(input, b)
#define pressed(b) isbupre(input, b)
#define released(b) isburel(input, b)
#define IsBindDown(b) iskbdow(input, b)
#define BindPressed(b) iskbpre(input, b)
#define BindReleased(b) iskbrel(input, b)
#define IsFuncDown(b) iskfdow(input, b)
#define FuncPressed(b) iskfpre(input, b)
#define FuncReleased(b) iskfrel(input, b)
	Spot GetMousePos() {
		tagPOINT point;
		GetCursorPos(&point);
		ScreenToClient(window, &point);
		Spot pos = { point.x, point.y };
		pos.x = pos.x / (render_state.width / render_scale.x);
		pos.y = pos.y / (render_state.height / render_scale.y);
		return pos;
	}
	void HideMouse() {
		ShowCursor(false);
	}
	void ShowMouse() {
		ShowCursor(true);
	}
}