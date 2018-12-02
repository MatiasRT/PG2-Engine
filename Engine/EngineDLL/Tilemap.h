#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Material.h"
#include "CollisionManager.h"
#include "Tile.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class ENGINEDLL_API Tilemap {

	int viewWidth;
	int viewHeight;
	int levelWidth;
	int levelHeight;
	float scrollX;
	float scrollY;

	int * view;

	Material * material;
	Renderer * render;
	CollisionManager * instance;

	glm::vec3 CameraPos;

	vector<vector<Tile*>*>* viewSprite;
	vector<vector<int>*>* level;
	//vector<int>* textures;

	void UploadSprite();
	void LoadView();

public:
	Tilemap(const char* filepath, int winWidth, int winHeight, Material * mat, Renderer * rend);
	~Tilemap();
	void DrawTilemap();
	void UpdateTilemap();
};