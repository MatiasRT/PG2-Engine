#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 p, float w, float h, bool setStatic, bool setTrigger/*, Shape* shape*/) {
	pos = p;
	width = w;
	height = h;
	isStatic = setStatic;
	isTrigger = setTrigger;
	//boxShape = shape;
}