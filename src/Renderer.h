#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_AVX
#include <glm/glm.hpp>

#include "ogl/CircleRenderer.h"
#include "input/Input.h"

using namespace std;
using namespace glm;

namespace Renderer {
	extern GLFWwindow* window;
	void init(int width, int height);
	bool update(CircleVao& vao, Camera& camera);
}