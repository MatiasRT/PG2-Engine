#include "BoundingCircle.h"

BoundingCircle::BoundingCircle(glm::vec2 p, unsigned int r, bool setStatic) {
	pos = p;
	radius = r;
	staticCircle = setStatic;
}

glm::vec2 BoundingCircle::GetPos() {
	return pos;
}

bool BoundingCircle::isStatic() {
	return staticCircle;
}

unsigned int BoundingCircle::GetX() {
	return pos.x;
}

unsigned int BoundingCircle::GetY() {
	return pos.y;
}

unsigned int BoundingCircle::GetRadius() {
	return radius;
}