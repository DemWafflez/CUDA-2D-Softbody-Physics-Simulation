#include "CircleVao.h"

CircleVao::CircleVao(int maxCircles) : Vao(maxCircles, 5), maxCircles(maxCircles), size(0) {
	initAttribs();
}

void CircleVao::initAttribs() {
	Vao::initAttribs();

	setAttrib(0, 1, 0);
	setAttrib(1, 1, 0);
	setAttrib(2, 1, 0);
	setAttrib(3, 1, 0);
	setAttrib(4, 1, 0);
}