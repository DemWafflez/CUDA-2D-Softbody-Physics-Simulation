#pragma once

#include "Vao.h"

class CircleVao : public Vao {
public:
	CircleVao(int maxCircles);

	void initAttribs() override;

	const int maxCircles;
	int size;
private:
};