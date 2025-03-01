#pragma once

#include <cuda_runtime.h>
#include <vector>

#include "CudaUtility.h"
#include "../utils/Utility.h"

using namespace std;

class CudaBuffer
{
public:
	CudaBuffer(int size, int count);
	CudaBuffer(vector<int> sizes);
	~CudaBuffer();

	int size;

	vector<void *> hBuffers;
	void **dBuffers;
};
