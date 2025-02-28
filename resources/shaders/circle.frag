#version 460 core

in vec3 circleColor;
out vec4 outputColor;

void main() {
	vec2 coord = gl_PointCoord.xy * 2.0f - vec2(1.0f); // mapping to [-1, 1]
	float magSq = dot(coord, coord);

	if(magSq > 1.0f) {
		discard;
	}

	outputColor = vec4(circleColor, 1);
}
