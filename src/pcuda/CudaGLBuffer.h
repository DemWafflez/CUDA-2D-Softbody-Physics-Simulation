#pragma once

#include <GL/glew.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <iostream>
#include <vector>

#include "CudaUtility.h"
#include "../utils/Utility.h"

class CudaGLBuffer
{
public:
	CudaGLBuffer(int size, int count);
	CudaGLBuffer(vector<int> sizes);
	~CudaGLBuffer();

	int size;

	vector<GLuint> vbos;

	vector<void *> hBuffers;
	void **dBuffers;

private:
	vector<cudaGraphicsResource *> resources;
};