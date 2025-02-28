#include<iostream>
#include<cuda_runtime.h>

#include "Renderer.h"

#include "ogl/Shaders.h"
#include "ogl/CircleVao.h"
#include "math/Camera.h"
#include "pcuda/CudaBuffer.h"
#include "input/C2DController.h"

#include "Settings.h"
#include "pcuda/ParticleManager.cuh"

#define WIDTH 1500
#define HEIGHT 1000

void handleInput(Camera& cam, CircleVao& vao, CudaBuffer& softBody, bool& paused, bool& slowmo) {
	vec2 mouse = cam.getMouse();

	if (Input::getKey(GLFW_KEY_E, true)) {
		vao.size = ParticleManager::generateParticles(mouse, R_BODY_COUNT * CELL_SIZE, R_BODY_COUNT * CELL_SIZE, vao.size, vao.buffer, softBody, MAX_PARTICLES);
		cout << "Particles: " << vao.size << endl;
	}
	if (Input::getKey(GLFW_KEY_R, true)) {
		vao.size = 0;
		cout << "RESETTED: " << endl;
	}
	if (Input::getKey(GLFW_KEY_SPACE, true)) {
		paused = !paused;
		cout << "TOGGLED PAUSE: " << endl;
	}
	if (Input::getKey(GLFW_KEY_G, true)) {
		slowmo = !slowmo;
		cout << "TOGGLED SLOWMO: " << endl;
	}
}

int main() {
	Renderer::init(WIDTH, HEIGHT);
	Camera cam(WIDTH, HEIGHT);
	C2DController::connect(&cam);

	CircleVao vao(MAX_PARTICLES);

	CudaBuffer map(MAX_PARTICLES, 3);
	CudaBuffer tempBuffer(MAX_PARTICLES, 5);

	CudaBuffer softBody(MAX_PARTICLES, 2);
	CudaBuffer tempBuffer2(MAX_PARTICLES, 2);

	bool paused = false;
	bool slowmo = false;

	cam.translation = vec2(0, -CENTER_Y);

	while (!Renderer::update(vao, cam)) {
		C2DController::update(MOUSE_SENSITIVITY, MOUSE_ZOOM_SPEED);
		handleInput(cam, vao, softBody, paused, slowmo);

		if (!paused) {
			ParticleGrid::build(vao.buffer, tempBuffer, map, softBody, tempBuffer2, vao.size);

			int scale = slowmo ? SLOWMO_SCALE : 1;

			for (int i = 0;i < SUBSTEPS / scale;i++) {
				ParticleManager::updateParticles(vao.buffer, map, softBody, cam.getMouse(), vao.size);
			}
		}
	}
}