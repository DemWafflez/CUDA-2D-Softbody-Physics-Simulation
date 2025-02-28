#pragma once

#include<vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../utils/File.h"	
#include "../utils/Utility.h"

using namespace std;

namespace Shaders {
	GLuint createShader(Str source, GLenum type);
	GLuint createShader(Str path);
	GLenum shaderType(Str path);

	GLuint createProgram(vector<Str> paths);
	void printProgramLog(GLuint program);

	GLint uniformLocation(GLuint program, Str name);
	void setUniform(GLuint program, Str name, int size, const float* values);
}