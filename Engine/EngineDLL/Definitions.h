#pragma once

#define GL_TRIANGLES			0x0004
#define GL_TRIANGLE_STRIP		0x0005
#define GL_TRIANGLE_FAN			0x0006

enum Layers {
	player,
	enemy,
	walkeable,
	not_walkeable,
	tiles,
	count
};

enum Directions {
	Up,
	Down,
	Left,
	Right
};