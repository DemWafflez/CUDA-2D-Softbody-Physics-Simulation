#include "CudaUtility.h"

namespace CudaUtility {
	void mapGLResources(vector<cudaGraphicsResource*>& resources, vector<GLuint>& vbos, vector<void*>& ptrs, unsigned int flags) {
		int size = resources.size();

		for (int i = 0;i < size;i++) {
			cudaGraphicsGLRegisterBuffer(&resources[i], vbos[i], flags);
		}

		cudaGraphicsMapResources(size, resources.data());

		for (int i = 0;i < size;i++) {
			cudaGraphicsResourceGetMappedPointer((void**)&ptrs[i], nullptr, resources[i]);
		}
	}

	void unmapGLResources(vector<cudaGraphicsResource*>& resources) {
		cudaGraphicsUnmapResources(resources.size(), resources.data());
		
		for (int i = 0;i < resources.size();i++) {
			cudaGraphicsUnregisterResource(resources[i]);
		}
	}

	void* allocateAndCopy(void* data, int bSize) {
		void* dest = nullptr;

		cudaMalloc(&dest, bSize);
		cudaMemcpy(dest, data, bSize, cudaMemcpyHostToDevice);

		return dest;
	}

	void copy(void* dst, void* src, int start, int end, cudaMemcpyKind kind) {
		void* d = (void*) ((uintptr_t)dst + start);
		void* s = (void*) ((uintptr_t)src + start);

		cudaMemcpy(d, s, end - start, kind);
	}

	void fcopy(float* dst, float* src, int start, int end, cudaMemcpyKind kind) {
		copy(dst, src, start * sizeof(float), end * sizeof(float));
	}

	void bulkAllocate(vector<int>& sizes, vector<void*>& buffers, int bytePer) {
		int length = sizes.size();

		for (int i = 0;i < length;i++) {
			cudaMalloc(&buffers[i], sizes[i] * bytePer);
		}
	}
}