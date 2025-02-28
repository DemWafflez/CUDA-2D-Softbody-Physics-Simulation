#pragma once

#include "glm/glm.hpp"

#include<vector>
#include <cstdlib>
#include <ctime>

typedef const char* Str;

using namespace std;
using namespace glm;

namespace Utility {
	int strFind(Str string, char c);
	int intCeil(int top, int bot);

	vector<int> getSizes(int size, int count);

	float random();
	vec2 randomPos(float x, float x2, float y, float y2);
}