#include "CudaBuffer.h"

CudaBuffer::CudaBuffer(int size, int count) : CudaBuffer(Utility::getSizes(size, count)) {}

CudaBuffer::CudaBuffer(vector<int> sizes) : size(sizes.size()) {
	hBuffers.resize(size);

	CudaUtility::bulkAllocate(sizes, hBuffers);

	dBuffers = (void**) CudaUtility::allocateAndCopy(hBuffers.data(), size * sizeof(void*));
}

CudaBuffer::~CudaBuffer() {
	for (int i = 0;i < size;i++) {
		cudaFree(hBuffers[i]);
	}

	cudaFree(dBuffers);
}