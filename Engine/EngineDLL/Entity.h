#pragma once
#include "Exports.h"
#include "Renderer.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Entity
{
protected:
	Renderer * renderer;
public:
	virtual void Draw() = 0;
	Entity(Renderer* rendererPtr);
};

