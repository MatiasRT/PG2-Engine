#pragma once
#include "Exports.h"
#include "CollisionManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingBox {
	glm::vec2 pos;
	unsigned int width;
	unsigned int height;
	Layer layer;
public:
	BoundingBox(glm::vec2 pos, unsigned int width, unsigned int height);
	~BoundingBox() { };
	unsigned int GetInfo();
	glm::vec2 GetPos();
};