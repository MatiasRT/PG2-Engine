#include "Object.h"



Object::Object(Renderer * renderer, const char * filename, float anim, float posX, float posY, float posZ, float w, float h, Tilemap * tile) {
	sprite = new Sprite(renderer, anim, filename);
	material = new Material();
	material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	sprite->SetMaterial(material);

	sprite->SetTranslation(posX, posY, posZ);

	textureBuffer = sprite->LoadTexture(filename);
	sprite->SetTextureBufferId(textureBuffer);

	height = h;
	width = w;
	tilemap = tile;
}

void Object::SetCollider(float posX, float posY, float posZ, float height, float widht, Layers layer, bool isStatic) {
	sprite->SetCollider(glm::vec3(posX, posY, posZ), height, widht, layer, isStatic);
}

void Object::CheckCollision(float speed) {
	if (tilemap->CheckCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, width)) {
		if (InputManager::Instance()->GetKeyDown(RightKey)) {
			sprite->SetTranslationX(sprite->GetTranslationX() - speed);
		}
		else if (InputManager::Instance()->GetKeyDown(LeftKey)) {
			sprite->SetTranslationX(sprite->GetTranslationX() + speed);
		}
		else if (InputManager::Instance()->GetKeyDown(UpKey)) {
			sprite->SetTranslationY(sprite->GetTranslationY() - speed);
		}
		else if (InputManager::Instance()->GetKeyDown(DownKey)) {
			sprite->SetTranslationY(sprite->GetTranslationY() + speed);
		}
	}
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

