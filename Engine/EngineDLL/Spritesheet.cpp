#include "Spritesheet.h"

Spritesheet::Spritesheet(int tW, int tH, int col, int rows) {
	uvList = new list<float*>();

	int countFrames = rows * col;
	float wFrame = 1.0f / col;
	float hFrame = 1.0f / rows;
	float x;
	float y;

	for (int i = 0; i < countFrames; i++) {
		x = (i % countFrames) * wFrame;
		y = (i / countFrames) * hFrame;
		uvPositions = new float[8]{
			x / tW, 1 - ((y + hFrame) / tH),
			x / tW, 1 - y / tH,
			(x + wFrame) / tW , 1 - ((y + hFrame) / tH),
			(x + wFrame) / tW, 1 - y / tH
		};
		uvList->push_back(uvPositions);
	}
}

float * Spritesheet::GetSpritesheet(int frame) {
	int fr = 0;
	for (list<float*>::iterator i = uvList->begin; i != uvList->end(); i++)
		if (fr == frame)
			return *i;
		else fr++;
}