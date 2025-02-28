#pragma once

#include "CircleVao.h"
#include "../math/Camera.h"
#include "Shaders.h"

namespace CircleRenderer {
	void init();
	void draw(CircleVao& vao, Camera& cam);
};