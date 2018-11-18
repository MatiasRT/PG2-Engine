#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingCircle {
	glm::vec2 pos;
	float radius;
	bool isStatic;
	bool isTrigger;

public:
	BoundingCircle(glm::vec2 pos, float radius, bool setStatic, bool setTrigger);
	~BoundingCircle() { };
	bool IsStatic() { return isStatic; };
	bool IsTrigger() { return isTrigger; };
	float GetX() { return pos.x; };
	float GetY() { return pos.y; };
	float GetRadius() { return radius; };
	glm::vec2 GetPos() { return pos; };
};