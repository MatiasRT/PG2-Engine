#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"

class ENGINEDLL_API Object {

	Sprite * sprite;
	Material * material;
	unsigned int textureBuffer;
public:
	Object(Renderer * renderer, const char * filename, float anim, float posX, float posY, float posZ);
	~Object();
	void SetCollider(float posX, float posY, float posZ, float height, float widht, Layers layer);
	void Draw();
	void Update();

	Sprite * GetSprite() { return sprite; };
};