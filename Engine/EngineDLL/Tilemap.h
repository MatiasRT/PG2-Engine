#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Material.h"
#include "CollisionManager.h"
#include <vector>
#include <fstream>

class ENGINEDLL_API Tilemap {
	
	Sprite * layers;
	Material * material;
	Renderer * render;

	glm::vec3 CameraPos;

	CollisionManager * instance;


	int viewW;
	int viewH;

	int * level;
	int * view;
	vector<vector<Sprite*>*>* viewSprite;
public:
	Tilemap(char* filepath, int winW, int winH);
	~Tilemap();
	void DrawTilemap();
	void UpdateTilemap();
	void LoadViewSprite();
	void LoadLevel();
	void LoadView();
};