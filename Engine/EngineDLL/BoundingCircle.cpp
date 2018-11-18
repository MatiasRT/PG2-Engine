#include "BoundingCircle.h"

BoundingCircle::BoundingCircle(glm::vec2 p, unsigned int r, bool setStatic, bool setTrigger) {
	pos = p;
	radius = r;
	isStatic = setStatic;
	isTrigger = setTrigger;
}