#include "Entity.h"

Entity::Entity(Renderer* rendererPTR) {
	renderer = rendererPTR;
	worldMatrix = glm::mat4(1.0f);															// Identidad
	translateMatrix = glm::mat4(1.0f);														// Translacion
	scaleMatrix = glm::mat4(1.0f);															// Escala
	rotationX = glm::mat4(1.0f);															// Rotacion en X
	rotationY = glm::mat4(1.0f);															// Rotacion en Y
	rotationZ = glm::mat4(1.0f);															// Rotacion en Z
	v3pos = glm::vec3(0.0f, 0.0f, 0.0f);													// Inicializacion de la posicion
	v3scale = glm::vec3(1.0f, 1.0f, 0.0f);													// Inicializacion de la escala
	v3rot = glm::vec3(0.0f, 0.0f, 0.0f);													// Inicializacion de la rotacion
}

void Entity::SetTranslation(float x, float y, float z) {
	v3pos[0] = x;
	v3pos[1] = y;
	v3pos[2] = z;

	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
}

void Entity::SetTranslationX(float x) {
	v3pos[0] = x;
	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
}

void Entity::SetTranslationY(float y) {
	v3pos[1] = y;
	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
}

void Entity::SetTranslationZ(float z) {
	v3pos[2] = z;
	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
}

void Entity::SetScale(float x, float y, float z) {
	v3scale[0] = x;
	v3scale[1] = y;
	v3scale[2] = z;

	scaleMatrix = glm::scale(glm::mat4(1.0f), v3scale);
	UpdateWorldMatrix();
}

void Entity::SetRotX(float x) {
	v3rot[0] = x;
	
	glm::vec3 axis;
	axis[2] = axis[1] = 0.0f;
	axis[0] = 1.0f;

	rotationX = glm::rotate(glm::mat4(1.0f), x, axis);
	
	UpdateWorldMatrix();
}

void Entity::SetRotY(float y) {
	v3rot[1] = y;

	glm::vec3 axis;
	axis[2] = axis[0] = 0.0f;
	axis[1] = 1.0f;

	rotationY = glm::rotate(glm::mat4(1.0f), y, axis);

	UpdateWorldMatrix();
}

void Entity::SetRotZ(float z) {
	v3rot[2] = z;
	
	glm::vec3 axis;
	axis[0] = axis[1] = 0.0f;
	axis[2] = 1.0f;

	rotationZ = glm::rotate(glm::mat4(1.0f), z, axis);

	UpdateWorldMatrix();
}

void Entity::UpdateWorldMatrix() {
	worldMatrix = (translateMatrix * rotationX * rotationY * rotationZ * scaleMatrix);
}

void Entity::SetCollider(glm::vec3 position, float height, float width, Layers layer, bool isStatic) {
	collider = new Collider(position, height, width, layer, isStatic);
}