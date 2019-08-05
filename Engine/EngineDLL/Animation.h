#pragma once
#include "Exports.h"
#include "Time.h"
#include "Spritesheet.h"
#include <iostream>
using namespace std;

class ENGINEDLL_API Animation {

	int actualFrame;
	int cantFrames;

	float frameLenght;

	float timer;
	float fTimer;

	float * frame;

public:
	Animation(float frames);
	~Animation() { };
	float * UpdateFrame();
};