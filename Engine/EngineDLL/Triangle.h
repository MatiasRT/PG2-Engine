#pragma once
#include "Entity.h"
#include "Material.h"
class ENGINEDLL_API Triangle :public Entity
{
private:
	unsigned int bufferId;
	bool shouldDispose;
	int vtxCount;
	float* vertex;
	Material * material;
public:
	Triangle(Renderer * renderer);
	~Triangle();
	void SetVertices(float* vertex, int vtxCount);
	void Draw() override;
	void Dispose();
};

