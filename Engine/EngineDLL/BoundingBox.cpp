#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec2 p, unsigned int w, unsigned int h, bool setStatic/*, Shape* shape*/) {
	pos = p;
	width = w;
	height = h;
	staticBox = setStatic;
	//boxShape = shape;
}

bool BoundingBox::isStatic() {
	return staticBox;
}

void BoundingBox::SetPos(int x, int y) {
	pos.x = x;
	pos.y = y;
	//boxShape->SetPos(x, y, 0);
}

unsigned int BoundingBox::GetX() {
	return pos.x;
}

unsigned int BoundingBox::GetY() {
	return pos.y;
}

unsigned int BoundingBox::GetWidth() {
	return width;
}

unsigned int BoundingBox::GetHeight() {
	return height;
}

glm::vec2 BoundingBox::GetPos() {
	return pos;
}