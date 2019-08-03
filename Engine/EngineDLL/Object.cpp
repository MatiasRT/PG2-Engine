#include "Object.h"



Object::Object(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ) {
	staticObjectSprite = new Sprite(_renderer, _animation, _filename);
	staticObjectMaterial = new Material();
	staticObjectMaterial->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	staticObjectSprite->SetMaterial(staticObjectMaterial);

	staticObjectSprite->SetTranslation(_positionX, _positionY, _positionZ);

	textureBuffer = staticObjectSprite->LoadTexture(_filename);
	staticObjectSprite->SetTextureBufferId(textureBuffer);
}

void Object::SetCollider(float _positionX, float _positionY, float _positionZ, float _height, float _widht) {
	staticObjectSprite->SetCollider(glm::vec3(_positionX, _positionY, _positionZ), _height, _widht, not_walkeable, true);
}

Object::~Object() {
	delete staticObjectSprite;
	delete staticObjectMaterial;
}

void Object::Draw() {
	staticObjectSprite->Draw();
}

void Object::Update() {
	staticObjectSprite->UpdateAnim();
}

Sprite* Object::GetSprite() {
	return staticObjectSprite;
}
