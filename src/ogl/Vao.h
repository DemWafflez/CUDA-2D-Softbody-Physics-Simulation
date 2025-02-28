#pragma once

#include<iostream>
#include<vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include<cuda_runtime.h>
#include<cuda_gl_interop.h>

#include "../pcuda/CudaGLBuffer.h"
#include "../utils/Utility.h"

using namespace glm;
using namespace std;

class Vao { // float vao?
public:
	Vao(int size, int count);
	Vao(vector<int> sizes);
	~Vao();

	virtual void initAttribs();
	virtual void writeData();

	void bind();
	void bindVbo(int i);

	void setAttrib(int i, int floats, int divisor);

	float* getPtr(int i);
	void copyCuda(int i, float* src, int start, int end);

	GLuint ptr;

	vector<int> sizes;
	vector<GLuint> vbos;
	CudaGLBuffer buffer;
private:
	CudaGLBuffer init();
};