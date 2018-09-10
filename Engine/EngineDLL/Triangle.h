#pragma once
#include "Entity.h"
#include "Material.h"
class ENGINEDLL_API Triangle :public Entity
{
private:
	Renderer * render;
	Material * material;
public:
	Triangle();
	~Triangle();
	void SetVertices();
	void Draw();
};

