#pragma once
#include "Shape.h"
#include "Material.h"
#include "Importer.h"
class ENGINEDLL_API Sprite : public Shape {
	Header header;
public:
	Sprite(Renderer* renderer, const char * name);
	~Sprite();
};