#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Material.h"
#include "Shape.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class ENGINEDLL_API Tilemap : public Shape {
	
	struct TileColliderData {
		float positionX;
		float width;
		float positionY;
		float height;
	};

	const char* filename;

	int tilemapWidth;
	int tilemapHeight;

	int cantUVvertex;

	float cantTilesX;
	float cantTilesY;

	float tileOffset;
	float tileSize;

	vector<int>* mapIds;
	vector<float> vertexArrayPos;
	vector<vector<int>> bidimensionalIDs;

	vector<int>* tilesWithCollides;
	vector<int>* modTilesWithCollides;


	vector<TileColliderData>* tilesColliderData;
	vector<TileColliderData>* modTilesColliderData;
public:
	Tilemap(Renderer* renderer, float tWidth, float tHeight, const char* fName, float tilesX, float tilesY, float tOffset, float tSize, vector<int>* cTiles, vector<int>* modTiles);
	~Tilemap() {};
	void CreateGrid(float h, float w);
	void Draw() override;
	void DrawMesh(int drawType);
	void SetTextures(float* vertex, int cant);
	void LoadTexture(const char* name);
	void LoadUVs();
	void LoadMapIDs(const char* file);
	void SetTilemapVertex(float* vertex, int cant);

	bool CheckCollission(float pTranslationX, float pTranslationY, float pHeight, float pWidht);

	bool CheckModCollission(float pTranslationX, float pTranslationY, float pHeight, float pWidht);

	void UpdateTilemapColliderPosition(float diffX, float diffY);
};