#include "Camera.h"

Camera::Camera(float w, float h) : 
projection(ortho<float>(0, w, 0, h)),
width(w), height(h), 
center(w / 2, h / 2),
translation(0, 0),
zoom(1) 
{
}

void Camera::update() {
	view = mat4(1);
	
	view = translate(view, vec3(center, 0));
	view = scale(view, vec3(zoom, zoom, 1)); // storing zoom inside view matrix dont forget! should put in projection instead!
	view = translate(view, vec3(-translation.x - center.x, -translation.y - center.y, 0)); 

	invView = inverse(view);
}

void Camera::worldToViewport(vec2& pos) {
	vec4 temp(pos, 0, 1);
	temp = view * temp;

	pos.x = temp.x;
	pos.y = temp.y;
}
void Camera::viewportToWorld(vec2& pos) {
	vec4 temp(pos, 0, 1);
	temp = invView * temp;

	pos.x = temp.x;
	pos.y = temp.y;
}

void Camera::setUniforms(GLuint program) {
	Shaders::setUniform(program, "projection", 16, value_ptr(projection));
	Shaders::setUniform(program, "view", 16, value_ptr(view));
}

vec2 Camera::getMouse() {
	vec2 m = Input::getMouse();
	viewportToWorld(m);

	return m;
}