#pragma once
#include "Exports.h"
#include "Renderer.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Entity
{
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
public:
	virtual void Draw() = 0;
	Entity(Renderer* rendererPtr);
	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	glm::vec3 GetPos();
	glm::vec3 GetScale();
	glm::vec3 GetRotX();
	glm::vec3 GetRotY();
	glm::vec3 GetRotZ();
	void UpdateWorldMatrix();
};