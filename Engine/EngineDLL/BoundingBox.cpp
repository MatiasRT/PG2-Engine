#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 p, unsigned int w, unsigned int h) {
	pos = p;
	width = w;
	height = h;
}

unsigned int BoundingBox::GetInfo() {
	return pos.x, pos.y, width, height;
}

glm::vec2 BoundingBox::GetPos() {
	return pos;
}