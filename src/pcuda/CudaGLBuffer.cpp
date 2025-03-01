#include "CudaGLBuffer.h"

CudaGLBuffer::CudaGLBuffer(int size, int count) : CudaGLBuffer(Utility::getSizes(size, count)) {}

CudaGLBuffer::CudaGLBuffer(vector<int> sizes) : size(sizes.size())
{
	int length = sizes.size();

	for (int i = 0; i < length; i++)
	{
		GLuint vbo;
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, (long)sizes[i] * 4, nullptr, GL_DYNAMIC_DRAW); // hard coded 32 bits

		vbos.push_back(vbo);
	}

	hBuffers.resize(size);
	resources.resize(size);

	CudaUtility::mapGLResources(resources, vbos, hBuffers, cudaGraphicsMapFlagsWriteDiscard);
	dBuffers = (void **)CudaUtility::allocateAndCopy(hBuffers.data(), size * sizeof(void *));
}

CudaGLBuffer::~CudaGLBuffer()
{
	CudaUtility::unmapGLResources(resources);
	cudaFree(dBuffers);
}