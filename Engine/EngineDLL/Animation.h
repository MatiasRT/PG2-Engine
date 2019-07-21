#pragma once
#include "Exports.h"
#include "Time.h"
#include "Spritesheet.h"
#include <iostream>
using namespace std;

class ENGINEDLL_API Animation {
	int actualFrame;
	int cantFrames;
	float frameWidth;
	float timer;
	float frameTimer;
	float * frame;

public:
	Animation(float _cantFrames);
	~Animation();
	float * UpdateFrame();
};