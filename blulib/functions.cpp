namespace Blu {
	int clamp(int min, int val, int max) {
		if (val < min) return min;
		if (val > max) return max;
		else { return val; }
	}
	float clampf(float min, float val, float max) {
		if (val < min) return min;
		if (val > max) return max;
		else { return val; }
	}
	bool InRange(int num, int min, int max) {
		if (min <= num && num <= max) {
			return true;
		}
		else if (num <= min && num >= max) {
			return true;
		}
		else return false;
	}
	std::vector<int> range(int start, int end) {
		std::vector<int> r = {};
		for (int i = start; i < end; i++) {
			r.push_back(i);
		}
		return r;
	}
	float avg(std::vector<int> all) {
		int total = 0;
		for (int i : all) {
			total += i;
		}
		float average = total / all.size();
		return average;
	}
	int AbsI(int i) {
		if (i > 0) {
			return i;
		}
		else return -i;
	}
	float AbsF(float i) {
		if (i > 0) {
			return i;
		}
		else return -i;
	}
	int IsLeast(std::vector<float> all) {
		float leastval = all[0];
		int least = 0;
		for (int i = 0; i < all.size(); i++) {
			if (all[i] < leastval) {
				leastval = all[i];
				least = i;
			}
		}
		return least;
	}
	int IsMost(std::vector<float> all) {
		float mostval = all[0];
		int most = 0;
		for (int i = 0; i < all.size(); i++) {
			if (all[i] > mostval) {
				mostval = all[i];
				most = i;
			}
		}
		return most;
	}
	float GetDst(int x0, int y0, int x1, int y1) {
		return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
	}
	float GetSlope(int x0, int y0, int x1, int y1) {
		return (y0 - y1) / (x0 - x1);
	}
#define PI 3.1415926535
	Spot rotatePoint(Spot p, float angle, Spot center) {
		float radians = angle * DEG2RAD;
		float cosA = cos(radians);
		float sinA = sin(radians);

		p.x -= center.x;
		p.y -= center.y;

		float newX = p.x * cosA - p.y * sinA;
		float newY = p.x * sinA + p.y * cosA;

		p.x = newX + center.x;
		p.y = newY + center.y;

		return p;
	}
	template <typename T>
	bool isin(T i, const std::vector<T>& vec) {
		for (const T& t : vec) {
			if (i == t) return true;
		}
		return false;
	}
	template <typename T>
	std::vector<std::vector<T>> GetAllUniqueCombos(const std::vector<T>& arr) {
		std::vector<std::vector<T>> n;
		for (int i = 0; i < arr.size(); ++i) {
			for (int j = i + 1; j < arr.size(); ++j) {
				if (!isin({ arr[i], arr[j] }, n))n.push_back({ arr[i], arr[j] });
			}
		}
		return n;
	}
	std::string inttostring(int n) {
		int i = AbsI(n);
		std::vector<char> chars;
		for (int j = 1; i / j >= 1; j *= 10) {
			int d = i / j % 10;
			chars.push_back((char)d + 48);
		}
		std::reverse(chars.begin(), chars.end());
		if (chars.empty()) {
			return "0";
		}
		std::string str(chars.begin(), chars.end());
		if (i < 0) return str;
		return str;
	}
	void tick(float fps)
	{
		float frametime = fps/1000;
		if (dt < frametime) {
			Sleep(frametime - dt);
		}
	}
}