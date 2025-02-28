#include "Utility.h"

namespace Utility {
	int strFind(Str string, char c) {
		char curr = string[0];
		int i = 0;

		while (curr != '\0') {
			if (curr == c) return i;
			curr = string[++i];
		}

		return -1;
	}
	int intCeil(int top, int bot) {
		return (top + bot - 1) / bot;
	}

	vector<int> getSizes(int size, int count) {
		vector<int> v;

		for (int i = 0;i < count;i++) {
			v.push_back(size);
		}

		return v;
	}

	float random() {
		static bool initialized = false;

		if (!initialized) {
			srand(time(nullptr));
			initialized = true;
		}

		return (float) rand() / (float) RAND_MAX;
	}
	vec2 randomPos(float x, float x2, float y, float y2) {
		float t = random();
		float t2 = random();

		return vec2((x2 - x) * t + x, (y2 - y) * t2 + y);
	}
}