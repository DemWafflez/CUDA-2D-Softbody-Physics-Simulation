#pragma once

namespace Settings {
	constexpr int WORLD_WIDTH = 40000;
	constexpr int WORLD_HEIGHT = WORLD_WIDTH / 4;
	constexpr int CENTER_X = WORLD_WIDTH / 2;
	constexpr int CENTER_Y = WORLD_HEIGHT / 2;

	constexpr int SUBSTEPS = 6;
	constexpr int MAX_CHECKS = 16;
	constexpr float DT = 1.0f / 120.0f / SUBSTEPS;

	constexpr int RADIUS = 10;
	constexpr int CELL_SIZE = RADIUS * 2;
	constexpr int ESTIMATED_COLUMS = WORLD_WIDTH / CELL_SIZE + 1;
	constexpr int ESTIMATED_ROWS = WORLD_HEIGHT / CELL_SIZE + 1;

	constexpr float G = 600.0f;
	constexpr double G_DT_DT = G * DT * DT;

	constexpr float MOUSE_FORCE = 0.05f * DT;
	constexpr float MOUSE_MAX_DISTANCE = RADIUS * 50;

	constexpr float MOUSE_SENSITIVITY = 2.5f;
	constexpr float MOUSE_ZOOM_SPEED = 1.25f;

	constexpr float SPRING_INITIAL_STRETCH = 1.001f;
	constexpr float SPRING_HARDNESS = 250 * DT;
	constexpr float MIN_SPRING_DISTANCE = 0.001f;
	constexpr float MAX_SPRING_DISTANCE = RADIUS * 0.3f;

	constexpr float MAX_VELOCITY = RADIUS * 0.6f;

	// fake air resistance and friction but it works
	constexpr float AIR_RESIST_SCALE = 0.15f;
	constexpr float FRICTION_SCALE = 0.15f;

	constexpr float FLOOR_HARDNESS = 80 * DT;
	constexpr float PARTICLE_HARDNESS = 80 * DT;
	constexpr int MAX_PARTICLES = 1 << 22;

	// fixed softbody size because cuda loves predictability! fuckkk 
	constexpr int R_BODY_COUNT = 64;
	constexpr int BODY_COUNT = R_BODY_COUNT * R_BODY_COUNT;

	constexpr int SLOWMO_SCALE = 4;
}