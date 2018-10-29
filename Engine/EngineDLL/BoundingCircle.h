#pragma once
#include "Exports.h"
#include "CollisionManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingCircle {
	glm::vec2 pos;
	unsigned int radius;
	Layer layer;
public:
	BoundingCircle(glm::vec2 pos, unsigned int radius);
	~BoundingCircle() { };
	glm::vec2 GetPos();
	unsigned int GetInfo();
};