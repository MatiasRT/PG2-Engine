#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
using namespace std;

class ENGINEDLL_API Collider {

	float height;
	float width;
	bool isStatic;

	glm::vec2 pivotPosition;

	Layers layer;
public:
	Collider(glm::vec2 pPosition, float h, float w, Layers l, bool stc);
	~Collider() {};
	
	unsigned int GetHeight() { return height; }
	unsigned int GetWidth() { return width; }
	unsigned int GetXPosition() { return pivotPosition.x; }
	unsigned int GetYPosition() { return pivotPosition.y; }
	bool GetIsStatic() { return isStatic; }
	glm::vec2 GetPivot() { return pivotPosition; }
	Layers GetLayer() { return layer; }
};

