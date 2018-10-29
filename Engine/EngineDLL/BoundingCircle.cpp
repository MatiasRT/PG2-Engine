#include "BoundingCircle.h"

BoundingCircle::BoundingCircle(glm::vec2 p, unsigned int r) {
	pos = p;
	radius = r;
}

glm::vec2 BoundingCircle::GetPos() {
	return pos;
}

unsigned int BoundingCircle::GetInfo() {
	return pos.x, pos.y, radius;
}