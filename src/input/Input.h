#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include<unordered_map>

using namespace std;
using namespace glm;

typedef unordered_map<int, int> Buttons;

namespace Input {
	void setup(GLFWwindow* window);

	int getKey(int key, bool reset = false);
	int getButton(int button, bool reset = false);
	float getScroll(bool reset = false);
	vec2 getMouse();
}