#include "C2DController.h"

namespace C2DController
{
	Camera *camera;
	void connect(Camera *c)
	{
		camera = c;
	}
	void update(float sens, float zoomSpeed)
	{
		static vec2 lastPos;

		vec2 pos = Input::getMouse();

		if (Input::getButton(1) == GLFW_PRESS)
		{
			vec2 d = pos - lastPos;
			camera->translation -= d * sens / camera->zoom;
		}

		float s = Input::getScroll(true);

		if (s > 0)
		{
			camera->zoom *= zoomSpeed;
		}
		else if (s < 0)
		{
			camera->zoom /= zoomSpeed;
		}

		lastPos = pos;
	}
}