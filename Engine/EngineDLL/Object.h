#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"
#include "Tilemap.h"
#include "InputManager.h"

class ENGINEDLL_API Object {

	Sprite * sprite;
	Material * material;
	unsigned int textureBuffer;
	float height;
	float width;
	Tilemap * tilemap;
public:
	Object(Renderer * renderer, const char * filename, float anim, float posX, float posY, float posZ, float w, float h, Tilemap * tile);
	~Object();
	void SetCollider(float posX, float posY, float posZ, float height, float widht, Layers layer, bool isStatic);
	void CheckCollision(float speed);
	void Draw();
	void Update();

	Sprite * GetSprite() { return sprite; };
};