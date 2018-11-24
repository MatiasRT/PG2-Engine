#pragma once
#include "Exports.h"
#include "Spritesheet.h"

class ENGINEDLL_API Animation {
	int firstFrame = 0;
	int finalFrame = 0;
	int currentFrame = 0;
	float currentTime = 0.0f;
	float timeFrame = 0.1;
	
	Spritesheet* sprite;
	
public:
	Animation(int col, int rows);
	~Animation();
	float* UpdateAnimation(float time);
	void SetAnimation(int firstF, int finalF, float timeF);
};