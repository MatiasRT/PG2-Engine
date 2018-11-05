#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingCircle {
	glm::vec2 pos;
	unsigned int radius;
	Layers layer;
public:
	BoundingCircle(glm::vec2 pos, unsigned int radius);
	~BoundingCircle() { };
	glm::vec2 GetPos();
	unsigned int GetInfo();
};