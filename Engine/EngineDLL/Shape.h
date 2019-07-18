#pragma once
#include "Entity.h"
#include "Material.h"
#include "Importer.h"
#define PRIMITIVE_QUAD 0x0007

class ENGINEDLL_API Shape : public Entity {
protected:
	Header header;
	unsigned int bufferId;
	unsigned int colorBufferId;
	bool shouldDispose;
	bool shouldDisposeColor;
	int vtxCount;
	int vtxColorCount;
	float* vertex;
	float* colorVertex;
	float* textureVertex;
	unsigned int txrBufferId;
	unsigned int UVBufferID;

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