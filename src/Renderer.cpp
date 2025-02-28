#include "Renderer.h"

namespace Renderer {
	GLFWwindow* window;
	int width;
	int height;

	void init(int w, int h) {
		width = w;
		height = h;

		// GLFW

		glfwInit();
		window = glfwCreateWindow(width, height, "GPU Particle Simulation", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwShowWindow(window);

		// GL

		glewInit();
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		CircleRenderer::init();
		Input::setup(window);
	}

	bool update(CircleVao& vao, Camera& camera) {
		if (glfwWindowShouldClose(window)) return true;
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		CircleRenderer::draw(vao, camera);
		glfwSwapBuffers(Renderer::window);

		return false;
	}
}