typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
#define global_variable static
#define internal static
namespace Blu {
#define B_NONE -1
#define DEG2RAD PI/180
	Rect::Rect(int X, int Y, int WIDTH, int HEIGHT) {
		x = X;
		y = Y;
		width = WIDTH;
		height = HEIGHT;
	}

	SpotF::SpotF(float x1, float y1) {
		x = x1;
		y = y1;
	}

	Spot::Spot(int x1, int y1) {
		x = x1;
		y = y1;
	}

	bool Spot::operator==(const Spot& s) {
		return x == s.x && y == s.y;
	}

	Spot Spot::operator+(const Spot& s) {
		return { x + s.x, y + s.y };
	}

	Spot operator+(const Spot& l, const Spot& r) {
		return { l.x + r.x, l.y + r.y };
	}

	bool operator==(const Spot& lhs, const Spot& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
}
global_variable SpotF render_scale = SpotF(1280, 720);