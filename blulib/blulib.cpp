namespace Blu {
	float dt;
}
using namespace Blu;
#include <Windows.h>
#include <d2d1_1.h>
#include <fstream>
#include <ios>
#include "blulib.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};
static Render_State render_state;
namespace Blu {
	static class screen {
	public:
		static const int width = 1280, height = 720;
	};
	bool running = true;
	const char* GAME_NAME = "My Game (Change GAME_NAME variable to \"Whatever You Want\" to change window heading)";
}
HWND window;
#include "utils.cpp"
#include "render.cpp"
#include "input.cpp"
#include "objects.cpp"
LPWSTR CharToL(const char* c) {
	int length = MultiByteToWideChar(CP_UTF8, 0, c, -1, NULL, 0);
	LPWSTR wideString = new WCHAR[length];
	MultiByteToWideChar(CP_UTF8, 0, c, -1, wideString, length);
	return wideString;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		running = false;
		return 0;
	}
	if (uMsg == WM_PAINT) {
		
	}
	if (uMsg == WM_SIZE) {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(unsigned int);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

	}
	DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int Blu::BluMain(HINSTANCE hInstance, HINSTANCE prevInstance, int nCmdShow) {
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = WindowProc;

	// Register Class
	RegisterClass(&window_class);

	// Create Window
	window = CreateWindow(window_class.lpszClassName, CharToL(GAME_NAME), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);
	
	Input input = {};
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	LARGE_INTEGER perf;
	QueryPerformanceFrequency(&perf);
	performance_frequency = (float)perf.QuadPart;

	gra = new Graphics();
	if (!gra->init(window)) { delete gra; return -1; }
	while (running) {
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
			case WM_LBUTTONUP: {
				input.buttons[LMOUSE].isdown = false;
				input.buttons[LMOUSE].changed = true;
			}
			case WM_LBUTTONDOWN: {
				//input.buttons[LMOUSE].isdown = true; 
				input.buttons[LMOUSE].changed = true;
			}
			case WM_RBUTTONUP: {
				input.buttons[RMOUSE].isdown = false;
				input.buttons[RMOUSE].changed = true;
			}
			case WM_RBUTTONDOWN: {
				//input.buttons[RMOUSE].isdown = true; 
				input.buttons[RMOUSE].changed = true;
			}
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);
#define process_button(b, vk)\
case (vk): {\
input.buttons[b].isdown = is_down;\
input.buttons[b].changed = true;\
}break;
				switch (vk_code) {
					process_button(K_UP, VK_UP);
					process_button(K_DOWN, VK_DOWN);
					process_button(K_LEFT, VK_LEFT);
					process_button(K_RIGHT, VK_RIGHT);
					process_button(K_A, 0x41);
					process_button(K_B, 0x42);
					process_button(K_C, 0x43);
					process_button(K_D, 0x44);
					process_button(K_E, 0x45);
					process_button(K_F, 0x46);
					process_button(K_G, 0x47);
					process_button(K_H, 0x48);
					process_button(K_I, 0x49);
					process_button(K_J, 0x4A);
					process_button(K_K, 0x4B);
					process_button(K_L, 0x4C);
					process_button(K_M, 0x4D);
					process_button(K_N, 0x4E);
					process_button(K_O, 0x4F);
					process_button(K_P, 0x50);
					process_button(K_Q, 0x51);
					process_button(K_R, 0x52);
					process_button(K_S, 0x53);
					process_button(K_T, 0x54);
					process_button(K_U, 0x55);
					process_button(K_V, 0x56);
					process_button(K_W, 0x57);
					process_button(K_X, 0x58);
					process_button(K_Y, 0x59);
					process_button(K_Z, 0x5A);
					process_button(K_0, 0x30);
					process_button(K_1, 0x31);
					process_button(K_2, 0x32);
					process_button(K_3, 0x33);
					process_button(K_4, 0x34);
					process_button(K_5, 0x35);
					process_button(K_6, 0x36);
					process_button(K_7, 0x37);
					process_button(K_8, 0x38);
					process_button(K_9, 0x39);
					process_button(LMOUSE, VK_LBUTTON);
					process_button(RMOUSE, VK_RBUTTON);
					process_button(K_BACKSPACE, 0x08);
					process_button(K_TAB, 0x09);
					process_button(K_ENTER, 0x0D);
					process_button(K_LSHIFT, 0xA0);
					process_button(K_RSHIFT, 0xA1);
					process_button(K_RALT, 0xA5);
					process_button(K_LALT, 0xA4);
					process_button(K_LCTRL, 0xA2);
					process_button(K_RCTRL, 0xA3);
					process_button(K_ESCAPE, VK_ESCAPE);
				}
			} break;
			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}
		gra->begin();
		Update(&input);
		gra->end();
		InpOff(&input);

		WCHAR title[256];
		GetWindowText(window, title, sizeof(title) / sizeof(WCHAR));
		if (CharToL(GAME_NAME) != title) {
			SetWindowText(window, CharToL(GAME_NAME));
		}

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		dt = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
}