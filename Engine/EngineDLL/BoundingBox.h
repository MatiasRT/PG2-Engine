#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingBox {
	glm::vec2 pos;
	unsigned int width;
	unsigned int height;
	Layers layer;
public:
	BoundingBox(glm::vec2 pos, unsigned int width, unsigned int height);
	~BoundingBox() { };
	unsigned int GetInfo();
	glm::vec2 GetPos();
};