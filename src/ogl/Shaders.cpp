#include "Shaders.h"

namespace Shaders {
	const int logSize = 256;
	char log[logSize];

	GLuint createShader(Str source, GLenum type) {
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		return shader;
	}
	GLuint createShader(Str path) {
		return createShader(File::readFile(path), shaderType(path));
	}
	GLenum shaderType(Str path) {
		int start = Utility::strFind(path, '.');
		char c = path[start + 1];// should be fine

		switch (c) { 
			case 'v':
				return GL_VERTEX_SHADER;
			case 'f':
				return GL_FRAGMENT_SHADER;
		}

		return GL_INVALID_ENUM;
	}

	GLuint createProgram(vector<Str> paths) {
		GLuint program = glCreateProgram();

		for (int i = 0;i < paths.size();i++) {
			GLuint shader = createShader(paths[i]);
			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		int succ;
		glGetProgramiv(program, GL_LINK_STATUS, &succ);

		if (!succ) {
			printProgramLog(program);
		}
		else {
			cout << "Program link successful\n";
		}

		return program;
	}
	
	void printProgramLog(GLuint program) {
		static int length;
		glGetProgramInfoLog(program, logSize, &length, log);

		cout << log << "\n";
	}

	GLint uniformLocation(GLuint program, Str name) {
		int loc = glGetUniformLocation(program, name);

		if (loc == -1) {
			cerr << name << " uniform not found!\n";
			return -1;
		}

		return loc;
	}
	void setUniform(GLuint program, Str name, int size, const float* values) { // lets go man
		int loc = uniformLocation(program, name);

		switch (size) {
		case 1:
			glProgramUniform1fv(program, loc, 1, values);
			return;
		case 2:
			glProgramUniform2fv(program, loc, 1, values);
			return;
		case 3:
			glProgramUniform3fv(program, loc, 1, values);
			return;
		case 4:
			glProgramUniform4fv(program, loc, 1, values);
			return;
		case 9:
			glProgramUniformMatrix3fv(program, loc, 1, false, values);
			return;
		case 16:
			glProgramUniformMatrix4fv(program, loc, 1, false, values);
			return;
		}

		cerr << "Error setting uniform " << name << "\n";
	}
}