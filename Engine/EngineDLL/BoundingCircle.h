#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingCircle {
	glm::vec2 pos;
	unsigned int radius;
	bool staticCircle;
	Layers layer;
public:
	BoundingCircle(glm::vec2 pos, unsigned int radius, bool setStatic);
	~BoundingCircle() { };
	glm::vec2 GetPos();
	bool isStatic();
	unsigned int GetX();
	unsigned int GetY();
	unsigned int GetRadius();
};