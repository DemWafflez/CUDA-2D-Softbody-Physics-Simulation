#pragma once

#include <GL/glew.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <vector>
#include <iostream>

using namespace std;

namespace CudaUtility
{
	void mapGLResources(vector<cudaGraphicsResource *> &resources, vector<GLuint> &vbos, vector<void *> &ptrs, unsigned int flags);
	void unmapGLResources(vector<cudaGraphicsResource *> &resources);
	void *allocateAndCopy(void *data, int bSize);
	void bulkAllocate(vector<int> &sizes, vector<void *> &buffers, int bytePer = sizeof(int));
	void copy(void *dst, void *src, int start, int end, cudaMemcpyKind kind = cudaMemcpyHostToDevice);
	void fcopy(float *dst, float *src, int start, int end, cudaMemcpyKind kind = cudaMemcpyHostToDevice);
}
