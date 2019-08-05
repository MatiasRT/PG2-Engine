#include "Collectable.h"

Collectable::Collectable(Renderer * render, const char * filename, float posX, float posY, float posZ, float h, float w) {

	height = h;
	width = w;

	sprite = new Sprite(render, 1.0f, filename);
	material = new Material();

	material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	sprite->SetMaterial(material);
	sprite->SetTranslation(posX, posY, posZ);

	textureBuffer = sprite->LoadTexture(filename);
	sprite->SetTextureBufferId(textureBuffer);
}

Collectable::~Collectable() {
	delete sprite;
	delete material;
}

bool Collectable::CheckCollision(float pTranslationX, float pTranslationY, float pHeight, float pWidht) {

	sprite->UpdateAnim();
	if (((pTranslationX + (pWidht / 2)) >= (sprite->GetTranslationX() - (width / 2))) &&
		((pTranslationX - (pWidht / 2)) <= (sprite->GetTranslationX() + (width / 2))) &&
		(pTranslationY + (pHeight / 2) >= (sprite->GetTranslationY() - (height / 2))) &&
		(pTranslationY - (pHeight / 2) <= (sprite->GetTranslationY() + (height / 2)))) {
		return true;
	}
	return false;
}

void Collectable::Draw() {
	sprite->Draw();
}