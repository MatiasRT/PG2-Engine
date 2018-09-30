#pragma once
#include "Entity.h"
#include "Material.h"
class ENGINEDLL_API Rectangle: public Entity {
	unsigned int bufferId;
	bool shouldDispose;
	int vtxCount;
	float* vertex;
	Material * material;
public:
	Rectangle(Renderer * renderer);
	~Rectangle();
	void SetVertices(float* vertex, int vtxCount);
	void Draw() override;
	void Dispose();
	void SetMaterial(Material* material);
};

