#include "ParticleGrid.cuh"

namespace ParticleGrid {
	__global__ void buildEntries(float* x, float* y, int* hashes, int* indices, int* starts, int size) {
		int i = blockIdx.x * blockDim.x + threadIdx.x;
		if (i >= size) return;

		int r = convert(y[i]);
		int c = convert(x[i]);

		hashes[i] = hasher(r, c, size);
		indices[i] = i;
		starts[i] = INT_MAX;
	}

	__global__ void buildStarts(int* hashes, int* starts, int size) {
		__shared__ int before[256 + 1]; // finally a time where shared memory has a use!

		int tid = threadIdx.x;
		int i = blockIdx.x * blockDim.x + tid;

		if (i >= size) return;

		int hash = hashes[i];
		before[tid + 1] = hash;

		if (i > 0 && tid == 0) {
			before[0] = hashes[i - 1];
		}

		__syncthreads();

		if (i == 0 || hash != before[tid]) {
			starts[hash] = i;
		}
	}

	__global__ void copyBack(float** buffer, float** temp, int* indices, int n, int size) {
		int x = blockIdx.x * blockDim.x + threadIdx.x;
		if (x >= size) return;

		int old = indices[x];

		for (int i = 0;i < n;i++) {
			temp[i][x] = buffer[i][old];
		}
	}

	void build(CudaGLBuffer& buffer, CudaBuffer& temp, CudaBuffer& mapBuffer, CudaBuffer& softBuffer, CudaBuffer& temp2, int size) {
		if (size == 0) return;

		int tbp = 256; // threads per block (tpb) ended up leaving as tbp due to typo
		int blocks = Utility::intCeil(size, tbp);

		float* x = (float*)buffer.hBuffers[0];
		float* y = (float*)buffer.hBuffers[1];

		int* hashes = (int*)mapBuffer.hBuffers[0];
		int* indices = (int*)mapBuffer.hBuffers[1];
		int* starts = (int*)mapBuffer.hBuffers[2];

		// build entries setting hashes

		buildEntries<<<blocks, tbp >>>(x, y, hashes, indices, starts, size);
		cudaDeviceSynchronize();

		auto k = thrust::device_pointer_cast(hashes);
		auto v = thrust::device_pointer_cast(indices);
		thrust::sort_by_key(k, k + size, v);

		cudaStream_t s, s2, s3;

		cudaStreamCreate(&s);
		cudaStreamCreate(&s2);
		cudaStreamCreate(&s3);

		// copy sorted data back into buffer
		// fuck you intellisense. never recognizing cuda syntax
		copyBack<<<blocks, tbp, 0, s>>>((float**)buffer.dBuffers, (float**)temp.dBuffers, indices, buffer.size, size);
		copyBack<<<blocks, tbp, 0, s2>>>((float**)softBuffer.dBuffers, (float**)temp2.dBuffers, indices, softBuffer.size, size);

		for (int i = 0;i < buffer.size;i++) {
			cudaMemcpyAsync(buffer.hBuffers[i], temp.hBuffers[i], size * sizeof(float), cudaMemcpyDeviceToDevice, s);
		}
		for (int i = 0;i < softBuffer.size;i++) {
			cudaMemcpyAsync(softBuffer.hBuffers[i], temp2.hBuffers[i], size * sizeof(float), cudaMemcpyDeviceToDevice, s2);
		}

		// mark starting indices for sorted hashes

		buildStarts<<<blocks, tbp, 0, s3>>>(hashes, starts, size);

		cudaDeviceSynchronize();

		cudaStreamDestroy(s);
		cudaStreamDestroy(s2);
		cudaStreamDestroy(s3);
	}
}