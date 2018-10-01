#pragma once
#include "Entity.h"
#include "Material.h"

#define GL_TRIANGLES			0x0004
#define GL_TRIANGLE_STRIP		0x0005
#define GL_TRIANGLE_FAN			0x0006

class ENGINEDLL_API Shape : public Entity {
protected:
	unsigned int bufferId;
	unsigned int colorBufferId;
	bool shouldDispose;
	bool shouldDisposeColor;
	int vtxCount;
	int vtxColorCount;
	float* vertex;
	float* colorVertex;
	Material * material;
public:
	Shape(Renderer * renderer);
	~Shape() { Dispose(); DisposeColor(); };
	void SetVertices(float* vertex, int count);
	void SetColorVertices(float* vertex, int count);
	virtual void Draw() = 0;
	void DrawMesh(int type);
	void Dispose();
	void DisposeColor();
	void SetMaterial(Material* material);
};