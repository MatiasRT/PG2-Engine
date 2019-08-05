#include "Object.h"



Object::Object(Renderer * renderer, const char * filename, float anim, float posX, float posY, float posZ) {
	sprite = new Sprite(renderer, anim, filename);
	material = new Material();
	material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	sprite->SetMaterial(material);

	sprite->SetTranslation(posX, posY, posZ);

	textureBuffer = sprite->LoadTexture(filename);
	sprite->SetTextureBufferId(textureBuffer);
}

void Object::SetCollider(float posX, float posY, float posZ, float height, float widht, Layers layer) {
	sprite->SetCollider(glm::vec3(posX, posY, posZ), height, widht, layer, true);
}

Object::~Object() {
	delete sprite;
	delete material;
}

void Object::Draw() {
	sprite->Draw();
}

void Object::Update() {
	sprite->UpdateAnim();
}