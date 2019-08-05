#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"
#include "Tilemap.h"
#include "CollisionManager.h"
#include "InputManager.h"

class ENGINEDLL_API Player {

	Sprite * sprite;
	Material * material;
	Tilemap * tilemapToCollide;

	float speed;
	float height;
	float widht;

	unsigned int animRightBuffer;
	unsigned int animLeftBuffer;
	unsigned int animUpBuffer;
	unsigned int animDownBuffer;

	bool firstDraw;
public:

	Player(Renderer * renderer, float anim, float spd, float h, float w, float posX, float posY, float posZ, Tilemap * tilemap);
	~Player();
	void Update();
	void Movement();
	void SetCollisionEntity(Layers layer);
	void Draw();

	float GetHeight() { return height; };
	float GetWidht() { return widht; };
	Sprite* GetSprite() { return sprite; };
};

