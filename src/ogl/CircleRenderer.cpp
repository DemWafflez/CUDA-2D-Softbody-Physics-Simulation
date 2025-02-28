#include "CircleRenderer.h"

namespace CircleRenderer {
	GLuint program;

	void init() {
		vector<Str> paths;
		paths.push_back("resources/shaders/circle.vert");
		paths.push_back("resources/shaders/circle.frag");

		program = Shaders::createProgram(paths);

		glEnable(GL_POINT_SPRITE);
		glEnable(GL_PROGRAM_POINT_SIZE);
	}

	void draw(CircleVao& vao, Camera& cam) {
		cam.update();
		cam.setUniforms(program);

		glUseProgram(program);

		vao.bind();
		glDrawArrays(GL_POINTS, 0, vao.size);
	}
};