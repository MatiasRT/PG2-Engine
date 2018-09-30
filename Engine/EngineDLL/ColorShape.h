#pragma once
#include "Entity.h"
#include "Material.h"
class ENGINEDLL_API ColorShape : Entity {
	unsigned int bufferId;
	bool shouldDispose;
	int vtxCount;
	float* vertex;
	Material * material;
public:
	ColorShape(Renderer * renderer);
	~ColorShape();
	void SetVertices(float* vertex, int count);
	void Draw() override;
	void Dispose();
	void SetMaterial(Material* material);
};