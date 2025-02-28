#pragma once

#include<GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "../ogl/Shaders.h"
#include "../input/Input.h"

using namespace glm;

class Camera {
public:
	Camera(float w, float h);

	float width, height;
	vec2 center;

	vec2 translation;
	float zoom;

	void update();
	vec2 getMouse();

	void worldToViewport(vec2& pos);
	void viewportToWorld(vec2& pos);

	void setUniforms(GLuint program);
private:
	mat4 projection;
	mat4 view;
	mat4 invView;
};