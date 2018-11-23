#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
class ENGINEDLL_API BoundingBox {
	Layers layer;
	//Shape* boxShape;

	glm::vec2 pos;
	float width;
	float height;
	bool isStatic;
	bool isTrigger;
	bool collision;

public:
	BoundingBox(glm::vec2 pos, float width, float height, bool setStatic, bool setTrigger/*, Shape* shape*/);
	~BoundingBox() { };
	bool IsStatic() { return isStatic; };
	bool IsTrigger() { return isTrigger; };
	void SetPos(float x, float y) { pos.x = x; pos.y = y; };
	void SetCollision(bool setCollision) { collision = setCollision; };
	float GetX() { return pos.x; };
	float GetY() { return pos.y; };
	float GetWidth() { return width; };
	float GetHeight() { return height; };
	glm::vec2 GetPos() { return pos; };
	bool GetCollision() { return collision; };
};