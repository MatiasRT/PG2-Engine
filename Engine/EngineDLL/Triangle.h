#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Triangle :public Shape {
public:
	Triangle(Renderer * renderer);
	~Triangle();
	void SetVertices(float* vertex, int vtxCount);
	void Draw() override;
	void Dispose();
};

