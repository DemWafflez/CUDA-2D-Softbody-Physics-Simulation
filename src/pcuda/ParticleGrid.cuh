#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include<thrust/sort.h>
#include<thrust/device_ptr.h>
#include<thrust/gather.h>
#include<thrust/host_vector.h>

#include "../ogl/CircleVao.h"
#include "../utils/Utility.h"
#include "../pcuda/CudaBuffer.h"
#include "../pcuda/CudaGLBuffer.h"

#include "../Settings.h"

#include "HelperGrid.cu"

namespace ParticleGrid {
	void build(CudaGLBuffer& buffer, CudaBuffer& temp, CudaBuffer& mapBuffer, CudaBuffer& softBuffer, CudaBuffer& temp2, int size);
}