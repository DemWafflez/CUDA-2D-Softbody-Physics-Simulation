#include "ParticleManager.cuh"

namespace ParticleManager
{
	__device__ __inline__ float fclamp(float x, float min, float max)
	{
		return fmaxf(fminf(x, max), min);
	}

	__global__ void updateMouse(float mx, float my, float *x, float *y, float *r, int n)
	{
		int i = blockIdx.x * blockDim.x + threadIdx.x;
		if (i >= n)
			return;

		// mouse grabbing

		float px = x[i];
		float py = y[i];
		float pr = RADIUS;

		float dx = px - mx;
		float dy = py - my;

		float magSq = dx * dx + dy * dy;
		if (magSq > MOUSE_MAX_DISTANCE * MOUSE_MAX_DISTANCE)
			return;

		float nx = MOUSE_FORCE * dx;
		float ny = MOUSE_FORCE * dy;

		x[i] -= nx;
		y[i] -= ny;
	}

	__device__ __forceinline__ void updateWorldBound(float px, float py, float pr, float dx, float dy, float *ox, float *oy)
	{
		px += CENTER_X;
		py += CENTER_Y;

		float depthX = 0;
		float depthY = 0;

		if (px - pr < 0)
		{
			depthX = 0 - (px - pr);
		}
		else if (px + pr > WORLD_WIDTH)
		{
			depthX = WORLD_WIDTH - (px + pr);
		}
		if (py - pr < 0)
		{
			depthY = 0 - (py - pr);
		}
		else if (py + pr > WORLD_HEIGHT)
		{
			depthY = WORLD_HEIGHT - (py + pr);
		}

		// fake friction but it works
		*ox += depthX * FLOOR_HARDNESS - dx * fabsf(depthY) * FRICTION_SCALE;
		*oy += depthY * FLOOR_HARDNESS - dy * fabsf(depthX) * FRICTION_SCALE;
	}

	__global__ void updatePosition(float *x, float *y, float *r, float *lx, float *ly, int n)
	{
		int i = blockIdx.x * blockDim.x + threadIdx.x;
		if (i >= n)
			return;

		float px = x[i];
		float py = y[i];

		float dx = px - lx[i];
		float dy = py - ly[i];

		updateWorldBound(px, py, RADIUS, dx, dy, &dx, &dy);

		// clamp + air reistance

		dx = fclamp(dx * (1 - DT * AIR_RESIST_SCALE), -MAX_VELOCITY, MAX_VELOCITY);
		dy = fclamp(dy * (1 - DT * AIR_RESIST_SCALE), -MAX_VELOCITY, MAX_VELOCITY);

		// verlet

		x[i] += dx;
		y[i] += dy - G_DT_DT;

		lx[i] = px;
		ly[i] = py;
	}

	__global__ void updateCollision(float *x, float *y, float *r, float *lx, float *ly, int *hashes, int *starts, int n)
	{
		int i = blockIdx.x * blockDim.x + threadIdx.x;
		if (i >= n)
			return;

		float ax = x[i];
		float ay = y[i];
		float ar = RADIUS;

		int indices[MAX_CHECKS];
		int total = queryRadiusBox(ax, ay, ar, hashes, starts, n, indices, 0);

		for (int j = 0; j < total; j++)
		{
			int k = indices[j];
			if (i == k)
				continue;

			float bx = x[k];
			float by = y[k];
			float br = RADIUS;

			float dx = bx - ax;
			float dy = by - ay;

			float magSq = dx * dx + dy * dy;
			float tr = ar + br;

			if (magSq < tr * tr)
			{
				float mag = sqrtf(magSq);
				float depth = tr - mag;

				float nx = dx / mag * depth * PARTICLE_HARDNESS;
				float ny = dy / mag * depth * PARTICLE_HARDNESS;

				// push

				atomicAdd(x + i, -nx);
				atomicAdd(y + i, -ny);

				atomicAdd(x + k, nx);
				atomicAdd(y + k, ny);
			}
		}
	}
	__device__ void handleConstraint(int i, int j, float *x, float *y)
	{
		float ax = x[i];
		float ay = y[i];
		float ar = RADIUS;

		float bx = x[j];
		float by = y[j];
		float br = RADIUS;

		float dx = bx - ax;
		float dy = by - ay;

		float magSq = dx * dx + dy * dy;
		float mag = sqrtf(magSq);
		float tr = (ar + br) * SPRING_INITIAL_STRETCH;

		if (fabs(mag - tr) > MIN_SPRING_DISTANCE && fabsf(mag - tr) < MAX_SPRING_DISTANCE)
		{
			float depth = mag - tr;

			float nx = dx / mag * depth * SPRING_HARDNESS;
			float ny = dy / mag * depth * SPRING_HARDNESS;

			// springs, need to add angle constraints but how?

			atomicAdd(x + i, nx);
			atomicAdd(y + i, ny);

			atomicAdd(x + j, -nx);
			atomicAdd(y + j, -ny);
		}
	}
	__global__ void updateConstraintsSlow(float *x, float *y, int *revIds, int n)
	{ // "slow" but not slow
	  // int tid = threadIdx.x;
	  // int i = blockIdx.x * blockDim.x + tid;
	  // if (i >= n)
	  // 	return;

		// int index = revIds[i]; // pointless optimization

		// int dr[] = {0, 1, 0, -1};
		// int dc[] = {-1, 0, 1, 0};
		// int l = sizeof(dc) / sizeof(int);

		// // soft body calculations

		// int bodyGroup = i / BODY_COUNT;
		// int localIndex = i % BODY_COUNT;

		// int row = localIndex / R_BODY_COUNT;
		// int column = localIndex % R_BODY_COUNT;

		// for (int j = 0; j < l; j++)
		// {
		// 	int cr = dr[j] + row;
		// 	int cc = dc[j] + column;

		// 	if (cr >= 0 && cr < R_BODY_COUNT && cc >= 0 && cc < R_BODY_COUNT)
		// 	{
		// 		int reconLocalId = cr * R_BODY_COUNT + cc;
		// 		int k = bodyGroup * BODY_COUNT + reconLocalId;

		// 		handleConstraint(index, revIds[k], x, y);
		// 	}
		// }
	}

	__global__ void updateReverseIds(int *ids, int *revIds, int n)
	{ // failed optimization neeed to refactor later
		int i = blockIdx.x * blockDim.x + threadIdx.x;
		if (i >= n)
			return;

		revIds[ids[i]] = i;
	}

	__global__ void generate(float *x, float *y, float *r, float *lx, float *ly, int *ids, float ox, float oy, int rows, int columns, int start, int *index, int n)
	{
		__shared__ int highestIndex;

		int cx = blockIdx.x * blockDim.x + threadIdx.x;
		int cy = blockIdx.y * blockDim.y + threadIdx.y;

		int i = cy * columns + cx;

		if (cx >= columns || cy >= rows || i + start >= n)
			return;

		// max size calculation

		if (threadIdx.x + threadIdx.y == 0)
		{
			highestIndex = *index;
		}

		__syncthreads();

		atomicMax(&highestIndex, i + start + 1);

		__syncthreads();

		if (threadIdx.x + threadIdx.y == 0)
		{
			atomicMax(index, highestIndex);
		}

		// creation

		int lc = cx / R_BODY_COUNT;
		int lr = cy / R_BODY_COUNT;

		float ax = cx * RADIUS * 2 * SPRING_INITIAL_STRETCH + ox;
		float ay = cy * RADIUS * 2 * SPRING_INITIAL_STRETCH + oy;

		x[i + start] = ax;
		y[i + start] = ay;

		r[i + start] = RADIUS;

		lx[i + start] = ax;
		ly[i + start] = ay;

		ids[i + start] = i + start;
	}

	inline void updateInput(float mx, float my, float *x, float *y, float *r, int size)
	{
		int tbp = 256;
		int blocks = Utility::intCeil(size, tbp);

		if (Input::getButton(0))
		{
			updateMouse<<<blocks, tbp>>>(mx, my, x, y, r, size);
		}
	}

	void updateParticles(CudaGLBuffer &buffer, CudaBuffer &mapBuffer, CudaBuffer &softBuffer, vec2 mouse, int size)
	{
		if (size == 0)
			return;

		float *x = (float *)buffer.hBuffers[0];
		float *y = (float *)buffer.hBuffers[1];
		float *r = (float *)buffer.hBuffers[2];
		float *lx = (float *)buffer.hBuffers[3];
		float *ly = (float *)buffer.hBuffers[4];

		int *hashes = (int *)mapBuffer.hBuffers[0];
		int *indices = (int *)mapBuffer.hBuffers[1];
		int *starts = (int *)mapBuffer.hBuffers[2];

		int *ids = (int *)softBuffer.hBuffers[0];
		int *revIds = (int *)softBuffer.hBuffers[1];

		int tbp = 256;
		int blocks = Utility::intCeil(size, tbp);

		updateInput(mouse.x, mouse.y, x, y, r, size);

		updatePosition<<<blocks, tbp>>>(x, y, r, lx, ly, size);

		updateReverseIds<<<blocks, tbp>>>(ids, revIds, size);
		updateConstraintsSlow<<<blocks, tbp>>>(x, y, revIds, size);

		updateCollision<<<blocks, tbp>>>(x, y, r, lx, ly, hashes, starts, size);

		cudaDeviceSynchronize();
	}

	int generateParticles(vec2 pos, float w, float h, int start, CudaGLBuffer &buffer, CudaBuffer &softBuffer, int size)
	{
		int rows = (int)(h / CELL_SIZE);
		int columns = (int)(w / CELL_SIZE);

		float *x = (float *)buffer.hBuffers[0];
		float *y = (float *)buffer.hBuffers[1];
		float *r = (float *)buffer.hBuffers[2];
		float *lx = (float *)buffer.hBuffers[3];
		float *ly = (float *)buffer.hBuffers[4];

		int *ids = (int *)softBuffer.hBuffers[0];

		dim3 cells(16, 16);
		dim3 blocks(Utility::intCeil(columns, cells.x), Utility::intCeil(rows, cells.y));

		int *dPtr = nullptr;

		cudaMalloc(&dPtr, sizeof(int));
		cudaMemcpy(dPtr, &start, sizeof(int), cudaMemcpyHostToDevice);

		generate<<<blocks, cells>>>(x, y, r, lx, ly, ids, pos.x - columns * CELL_SIZE / 2, pos.y - rows * CELL_SIZE / 2, rows, columns, start, dPtr, size);
		cudaDeviceSynchronize();

		cudaMemcpy(&start, dPtr, sizeof(int), cudaMemcpyDeviceToHost);
		cudaFree(dPtr);

		return start;
	}
}