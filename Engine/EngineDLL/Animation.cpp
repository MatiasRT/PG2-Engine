#include "Animation.h"

Animation::Animation(float frames) {
	cantFrames = frames;
	actualFrame = 0;
	frameLenght = 1.0f / cantFrames;
	frame = new float[8];
	fTimer = 0.2;

	timer = fTimer;
}

float * Animation::UpdateFrame() {
	timer += 0.2f;

	if (timer > fTimer) {
		frame[0] = 0.0f;
		frame[1] = 0.0f;
		frame[2] = frameLenght;
		frame[3] = 0.0f;
		frame[4] = 0.0f;
		frame[5] = 1.0f;
		frame[6] = frameLenght;
		frame[7] = 1.0f;

		for (int i = 0; i < actualFrame; i++) {
			frame[0] += frameLenght;
			frame[2] += frameLenght;
			frame[4] += frameLenght;
			frame[6] += frameLenght;
		}

		actualFrame++;

		if (actualFrame >= cantFrames) {
			actualFrame = 0;
		}

		timer = 0;
	}

	return frame;
}