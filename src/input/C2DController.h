#pragma once

#include "../math/Camera.h"
#include "Input.h"

namespace C2DController {
	extern Camera* camera;
	void connect(Camera* camera);
	void update(float sensitivity, float zoomSpeed);
}