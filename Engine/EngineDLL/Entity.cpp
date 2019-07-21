#include "Entity.h"

Entity::Entity(Renderer* rendererPTR) {
	box = NULL;
	circle = NULL;
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

void Entity::SetPos(float x, float y, float z) {
	if (box == NULL || circle == NULL) {													// No hay caja de colision
		v3pos[0] = x;
		v3pos[1] = y;
		v3pos[2] = z;
	}
	else {
		if (box != NULL && !box->GetCollision()) {											// Hay caja/circunferencia de colision, verifica el resultado del getter de colision de la caja/circunferencia
			v3pos[0] = x;
			v3pos[1] = y;
			v3pos[2] = z;
			box->SetPos(v3pos[0], v3pos[1]);
			box->SetCollision(false);	
		}
		if (circle != NULL && !circle->GetCollision()) {
			v3pos[0] = x;
			v3pos[1] = y;
			v3pos[2] = z;
			circle->SetPos(v3pos[0], v3pos[1]);
			circle->SetCollision(false);
		}
	}

	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
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

	scaleMatrix = glm::scale(glm::mat4(1.0f), v3pos);
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

void Entity::TranslationBox(float x, float y, float z) {									// Usamos translation para mover a la entidad porque sino se pierde la posicion original ya que la estoy pisando todo el tiempo.
	if (box == NULL) {																		// No hay caja de colision
		v3pos[0] += x;
		v3pos[1] += y;
		v3pos[2] += z;
	}
	else if (!box->GetCollision()) {														// Hay caja de colision, verifica el resultado del getter de colision de la caja
		v3pos[0] += x;
		v3pos[1] += y;
		v3pos[2] += z;
		box->SetPos(v3pos[0], v3pos[1]);
		box->SetCollision(false);
	}
	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
}

void Entity::TranslationCircle(float x, float y, float z) {
	if (circle == NULL) {																	// No hay circunferencia de colision
		v3pos[0] += x;
		v3pos[1] += y;
		v3pos[2] += z;
	}
	else if (!circle->GetCollision()) {														// Hay circunferencia de colision, verifica el resultado del getter de colision de la caja
		v3pos[0] += x;
		v3pos[1] += y;
		v3pos[2] += z;
		circle->SetPos(v3pos[0], v3pos[1]);
		circle->SetCollision(false);
	}
	translateMatrix = glm::translate(glm::mat4(1.0f), v3pos);
	UpdateWorldMatrix();
}

void Entity::SetBoundingBox(float w, float h, float mass, bool setStatic, bool setTrigger) {
	box = new BoundingBox(glm::vec2(v3pos.x, v3pos.y), w, h, mass, setStatic, setTrigger);	// Seteamos los valores que va a tener la caja de colision de una entidad en particular
}

void Entity::SetBoundingCircle(float r, float mass, bool setStatic, bool setTrigger) {
	circle = new BoundingCircle(glm::vec2(v3pos.x, v3pos.y), r, mass, setStatic, setTrigger);// Seteamos los valores que va a tener la circunferencia de colision de una entidad en particular
}

void Entity::UpdateWorldMatrix() {
	worldMatrix = (translateMatrix * rotationX * rotationY * rotationZ * scaleMatrix);
}

void Entity::SetCollider(glm::vec3 _position, float _height, float _width, Layers _layer, bool _isStatic) {
	collider = new Collider(_position, _height, _width, _layer, _isStatic);
}

glm::vec3 Entity::GetTranslation() {
	return v3pos;
}
float Entity::GetTranslationX() {
	return v3pos[0];
}
float Entity::GetTranslationY() {
	return v3pos[1];
}
float Entity::GetTranslationZ() {
	return v3pos[2];
}

unsigned int Entity::GetColliderPivotX() {
	return collider->GetXPosition();
}

unsigned int Entity::GetColliderPivotY() {
	return collider->GetYPosition();
}

glm::vec2 Entity::GetColliderPivot() {
	return collider->GetPivot();
}

unsigned int Entity::GetColliderHeight() {
	return collider->GetHeight();
}

unsigned int Entity::GetColliderWidth() {
	return collider->GetWidth();
}

Layers Entity::GetColliderLayer() {
	return collider->GetLayer();
}

bool Entity::GetColliderIsStatic() {
	return collider->GetIsStatic();
}