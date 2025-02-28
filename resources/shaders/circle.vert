#version 460 core

uniform mat4 projection;
uniform mat4 view;

layout(location = 0) in float x;
layout(location = 1) in float y;
layout(location = 2) in float r;
layout(location = 3) in float lx;
layout(location = 4) in float ly;

out vec3 circleColor;

vec3 start = vec3(1, 1, 1);
vec3 end = vec3(1, 0, 0);

void main() {
    gl_Position = projection * view * vec4(x, y, 0, 1);
    gl_PointSize = r * 2 * view[0][0]; // zoom inside view matrix! move to projection later!

    float dx = x - lx;
    float dy = y - ly;
    float magSq = dx * dx + dy * dy;
    float t = magSq / (5 * 5);

    circleColor = (end - start) * t + start;
}