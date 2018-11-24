#pragma once
#include "Exports.h"
#include <list>
using namespace std;

class ENGINEDLL_API Spritesheet {

	list<float*> * uvList; //vertices de uv
	float* uvPositions;

public:
	Spritesheet(int tW, int tH, int col, int rows);
	~Spritesheet() {/* delete uvList;*/ };
	int GetSize() { return uvList->size(); };
	float * GetSpritesheet(int frame);
};