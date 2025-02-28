#include "Input.h"

namespace Input {
	int w = 0, h = 0;
	float scroll = 0;

	Buttons keyboard, mouse;
	vec2 mousePos;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyboard[key] = action;
	}
	void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
		mouse[button] = action;
	}
	void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
		mousePos.x = (float)xpos;
		mousePos.y = h - (float)ypos;
	}
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		scroll = (float)yoffset;
	}

	void setup(GLFWwindow* window) {
		glfwGetWindowSize(window, &w, &h);

		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseCallback);
		glfwSetCursorPosCallback(window, cursorCallback);
		glfwSetScrollCallback(window, scrollCallback);
	}

	int getKey(int key, bool reset) {
		if (!keyboard.contains(key)) return GLFW_RELEASE;

		int value = keyboard[key];
		if (reset) keyboard[key] = GLFW_RELEASE;

		return value;
	}

	int getButton(int button, bool reset) {
		if (!mouse.contains(button)) return GLFW_RELEASE;

		int value = mouse[button];
		if (reset) mouse[button] = GLFW_RELEASE;

		return value;
	}

	float getScroll(bool reset) {
		float s = scroll;
		if (reset) scroll = 0;

		return s;
	}

	vec2 getMouse() {
		return mousePos;
	}
}