#pragma once
#include "Entity.h"
#include "Material.h"
#include "ColorShape.h"
class ENGINEDLL_API Rectangle: public Entity {
	unsigned int bufferId;
	bool shouldDispose;
	int vtxCount;
	float* vertex;
	float* colorVertex;
	Material * material;
	ColorShape * color;
public:
	Rectangle(Renderer * renderer);
	~Rectangle();
	void SetVertices(float* vertex, int vtxCount);
	void Draw() override;
	void Dispose();
	void SetMaterial(Material* material);
};

