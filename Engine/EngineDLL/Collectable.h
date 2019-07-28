#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"
#include "CollisionManager.h"

class ENGINEDLL_API Collectable {
	Sprite * sprite;
	Material * material;
	unsigned int textureBuffer;

	float height;
	float width;
public:
	Collectable(Renderer * render, const char * filename, float posX, float posY, float posZ, float h, float w);
	~Collectable();
	bool CheckCollision(float pTranslationX, float pTranslationY, float pHeight, float pWidht);
	void Draw();
};