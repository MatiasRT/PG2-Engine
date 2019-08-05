#pragma once
#include "Definitions.h"
#include "Exports.h"
#include "Renderer.h"
#include "Collider.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Entity {
protected:
	Renderer * renderer;

	glm::vec3 v3pos;
	glm::vec3 v3scale;
	glm::vec3 v3rot;

	glm::mat4 worldMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;

	Collider * collider;

public:
	virtual void Draw() = 0;
	Entity(Renderer* rendererPtr);
	void UpdateWorldMatrix();

	void SetTranslation(float x, float y, float z);
	void SetTranslationX(float x);
	void SetTranslationY(float y);
	void SetTranslationZ(float z);

	void SetScale(float x, float y, float z);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	void SetCollider(glm::vec3 position, float height, float width, Layers layer, bool isStatic);
	
	glm::vec3 GetPos() { return v3pos; };
	glm::vec3 GetScale() { return v3scale; };
	glm::vec3 GetRot() { return v3rot; };


	float GetTranslationX() { return v3pos[0]; };
	float GetTranslationY() { return v3pos[1]; };
	float GetTranslationZ() { return v3pos[2]; };

	unsigned int GetColliderPivotX() { return collider->GetXPosition(); };
	unsigned int GetColliderPivotY() { return collider->GetYPosition(); };

	glm::vec2 GetColliderPivot() { return collider->GetPivot(); };

	unsigned int GetColliderHeight() { return collider->GetHeight(); };
	unsigned int GetColliderWidth() { return collider->GetWidth(); };

	Layers GetColliderLayer() { return collider->GetLayer(); };

	bool GetColliderIsStatic() { return collider->GetIsStatic(); };
};