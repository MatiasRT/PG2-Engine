#include "Animation.h"

Animation::Animation(int col, int rows) {
	sprite = new Spritesheet(1, 1, col, rows);
}

Animation::~Animation() {
	delete sprite;
}

float * Animation::UpdateAnimation(float time) {
	currentTime += time;
	if (currentTime > timeFrame) {
		currentTime = 0.0f;
		if (currentFrame < finalFrame)
			currentFrame++;
		else currentFrame = firstFrame;
	}
	return sprite->GetSpritesheet(currentFrame);
}

void Animation::SetAnimation(int firstF, int finalF, float timeF) {
	if (firstF >= 0 && finalF < sprite->GetSize() && timeF > 0) {
		firstFrame = firstF;
		finalFrame = finalF;
		timeFrame = timeF;
		currentTime = 0.0f;
		currentFrame = firstFrame;
	}
}