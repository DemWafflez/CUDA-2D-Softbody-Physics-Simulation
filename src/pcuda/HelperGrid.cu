#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "../Settings.h"

using namespace Settings;

// moving to seperate file was only way to get this compiling and includable! 
// short term fix but it works!

__device__ __inline__ int convert(float value) {
	return (int)((value + CENTER_X * 1.05f) / CELL_SIZE);
}

__device__ __inline__ int hasher(int r, int c, int n) {
	return (r * ESTIMATED_COLUMS + c) % n;
}

__device__ __inline__ int query(int r, int c, int* hashes, int* starts, int n, int* outputs, int outputStart) {
	int h = hasher(r, c, n);
	int index = starts[h];

	if (index == INT_MAX) return outputStart;

	// absolutely beautiful 

	while (index < n && hashes[index] == h && outputStart < MAX_CHECKS) {
		outputs[outputStart++] = index++;
	}

	return outputStart;
}

__device__ __inline__ int queryRadiusBox(float x, float y, float r, int* hashes, int* starts, int n, int* outputs, int outputStart) {
	int bottomRow = convert(y - r);
	int bottomColumn = convert(x - r);

	int topRow = convert(y + r);
	int topColumn = convert(x + r);

	for (int i = bottomRow;i <= topRow;i++) {
		for (int j = bottomColumn;j <= topColumn;j++) {
			outputStart = query(i, j, hashes, starts, n, outputs, outputStart);
		}
	}

	return outputStart;
}