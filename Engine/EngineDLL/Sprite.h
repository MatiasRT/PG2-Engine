#pragma once
#include "Shape.h"
#include "Material.h"
#include "Importer.h"
class ENGINEDLL_API Sprite : public Shape {
	Header header;
	const char* file;
	unsigned int textureBufferId;
	bool shouldDisposeTexture;
	int vtxTextureCount;
	float* textureVertex;
public:
	Sprite(Renderer* renderer, const char * name);
	~Sprite();
	void LoadBMP(const char * name);
	void SetTextureVertices(int count);
	void DisposeTexture();
	void DrawMesh(int type);
	void Draw() override;
	void SetMaterial(Material* material);
};