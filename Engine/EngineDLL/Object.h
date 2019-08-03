#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"

class ENGINEDLL_API Object {
	Sprite * staticObjectSprite;
	Material * staticObjectMaterial;
	unsigned int textureBuffer;
public:
	Object(Renderer * _renderer, const char * _filename, float _animation, float _positionX, float _positionY, float _positionZ);
	~Object();
	void SetCollider(float _positionX, float _positionY, float _positionZ, float _height, float _widht);
	void Draw();
	void Update();
	Sprite * GetSprite();
};