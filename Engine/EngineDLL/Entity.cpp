#include "Entity.h"

Entity::Entity(Renderer* rendererPTR)
{
	renderer = rendererPTR;
	worldMatrix = glm::mat4(1.0f); //Identidad
	rotationMatrix = glm::mat4(1.0f);
	translateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
}
void Entity::SetPos(float x, float y, float z) {
	v3pos[0] = x;
	v3pos[1] = y;
	v3pos[2] = z;
}

void Entity::SetScale(float x, float y, float z) {

}

void Entity::SetRot(float x, float y, float z) {
	v3rot[0] = x;
	v3rot[1] = y;
	v3rot[2] = z;

	glm::vec3 axis1;
	axis1[2] = axis1[1] = 0.0f;
	axis1[0] = 1.0f;

	glm::vec3 axis2;
	axis2[2] = axis2[0] = 0.0f;
	axis2[1] = 1.0f;

	glm::vec3 axis3;
	axis3[0] = axis3[1] = 0.0f;
	axis3[2] = 1.0f;

	//rotateX = glm::rotate(glm::mat4(1.0f), x, axis1);
	//rotateY = glm::rotate(glm::mat4(1.0f), x, axis2);
	//rotateZ = glm::rotate(glm::mat4(1.0f), x, axis3);

	UpdateWorldMatrix();

}

void Entity::UpdateWorldMatrix() {
	worldMatrix = (translateMatrix * rotationMatrix * scaleMatrix);
}
glm::vec3 Entity::GetPos() {
	return v3pos;
}
glm::vec3 Entity::GetRot() {
	return v3rot;
}
glm::vec3 Entity::GetScale() {
	return v3scale;
}