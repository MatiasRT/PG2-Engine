#pragma once
#include "Exports.h"
#include "Renderer.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Entity
{
	glm::vec3 v3pos;
	glm::vec3 v3scale;
	glm::vec3 v3rot;
	

protected:
	Renderer * renderer;
	glm::mat4 worldMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
public:
	virtual void Draw() = 0;
	Entity(Renderer* rendererPtr);
	void SetPos(float x, float y, float z);
	glm::vec3 GetPos();
	void SetScale(float x, float y, float z);
	glm::vec3 GetScale();
	void SetRot(float x, float y, float z);
	glm::vec3 GetRot();
	void UpdateWorldMatrix();
};

