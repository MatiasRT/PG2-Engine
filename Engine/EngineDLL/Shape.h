#pragma once
#include "Entity.h"
#include "Material.h"
#include "ColorShape.h"

#define GL_TRIANGLES			0x0004
#define GL_TRIANGLE_STRIP		0x0005
#define GL_TRIANGLE_FAN			0x0006


class ENGINEDLL_API Shape : public Entity {
protected:
	unsigned int bufferId;
	unsigned int colorId;
	bool shouldDispose;
	int vtxCount;
	float* vertex;
	float* colorVertex;
	Material * material;
	ColorShape * color;
public:
	Shape(Renderer * renderer);
	~Shape() { Dispose(); };
	void SetVertices(float* vertex, int vtxCount);
	virtual void Draw() = 0;
	void DrawMesh(int type);
	void Dispose();
	void SetMaterial(Material* material);
};