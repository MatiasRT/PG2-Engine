#pragma once
#include "Shape.h"
#include "Material.h"
#include "Importer.h"
#include "Animation.h"
class ENGINEDLL_API Sprite : public Shape {
protected:
	
	Animation * animation;
	const char* file;
	unsigned int textureId;
	
	bool shouldDisposeTexture;
	int vtxTextureCount;
	
	bool collision;
public:
	Sprite(Renderer* renderer, int _cantFrames);//, const char * name);
	~Sprite();
	void LoadBMP(const char * name);
	unsigned int LoadTexture(const char * _name);
	void DisposeTexture();
	void DrawMesh1(int type);
	void SetTextureBufferId(unsigned int _textureBufferId);
	void Draw() override;
	void SetTextureVertices(int count);
	void SetTextureVertices(float * _vertex, int _cant);
	void SetMaterial(Material* material);
	void UpdateAnim();
	void SetCollision() { collision = true; }
	bool GetCollision() { return collision; }
};