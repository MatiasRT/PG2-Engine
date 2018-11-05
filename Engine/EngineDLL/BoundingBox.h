#pragma once
#include "Exports.h"
#include "Definitions.h"
#include "Shape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingBox {
	Layers layer;
	//Shape* boxShape;

	glm::vec2 pos;
	unsigned int width;
	unsigned int height;
	bool staticBox;
public:
	BoundingBox(glm::vec2 pos, unsigned int width, unsigned int height, bool setStatic/*, Shape* shape*/);
	~BoundingBox() { };
	bool isStatic();
	void SetPos(int x, int y);
	unsigned int GetX();
	unsigned int GetY();
	unsigned int GetWidth();
	unsigned int GetHeight();
	glm::vec2 GetPos();
};