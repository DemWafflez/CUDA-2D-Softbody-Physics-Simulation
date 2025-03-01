#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "ParticleGrid.cuh"

#include "../ogl/CircleVao.h"
#include "../utils/Utility.h"
#include "CudaBuffer.h"
#include "../input/Input.h"

#include "../Settings.h"

using namespace Settings;

namespace ParticleManager
{
	void updateParticles(CudaGLBuffer &buffer, CudaBuffer &mapBuffer, CudaBuffer &softBuffer, vec2 mouse, int size);
	int generateParticles(vec2 pos, float w, float h, int start, CudaGLBuffer &buffer, CudaBuffer &softBuffer, int size);
}