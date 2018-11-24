#pragma once
#include "Exports.h"
#include "Spritesheet.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Animation {
	int firstFrame;
	int finalFrame;
	int currentFrame;
	float currentTime;
	float timeFrame;
	
	Spritesheet* sprite;
	
public:
	Animation(int col, int rows);
	~Animation();
	float* UpdateAnimation(float time);
	void SetAnimation(int firstF, int finalF, float timeF);
};