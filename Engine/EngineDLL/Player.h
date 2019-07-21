#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"
#include "Tilemap.h"
#include "CollisionManager.h"
#include "InputManager.h"

class ENGINEDLL_API Player {

	Sprite * playerSprite;
	Material * playerMaterial;
	Tilemap * tilemapToCollide;
	float speed;
	float height;
	float widht;

	unsigned int animationRightBuffer;
	unsigned int animationLeftBuffer;
	unsigned int animationUpBuffer;
	unsigned int animationDownBuffer;

	bool firstDraw;
public:

	Player(Renderer * _renderer, float _animation, float _speed, float _height, float _widht, float _positionX, float _positionY, float _positionZ, Tilemap * _tilemapToCollide);
	~Player();
	void Update();
	void Movement();
	void SetCollisionEntity(Layers _layer);
	void Draw();
	float GetHeight();
	float GetWidht();
	Sprite* GetSprite();
};

