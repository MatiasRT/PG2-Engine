#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Rectangle: public Shape {
	/*unsigned int bufferId;
	bool shouldDispose;
	int vtxCount;
	float* vertex;
	float* colorVertex;
	Material * material;
	ColorShape * color;*/
public:
	Rectangle(Renderer * renderer);
	~Rectangle();
	void SetVertices(float* vertex, int vtxCount);
	void Draw() override;
	void Dispose();
};