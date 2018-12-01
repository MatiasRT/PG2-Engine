#include "Tilemap.h"

Tilemap::Tilemap(char* filepath, int winW, int winH) {		// Cargamos el archivo
	
	instance = CollisionManager::Instance();

	string buffer;


	
	int tileW = 10;
	int tileH = 10;
	viewW = int(winW / tileW) + 1;							// Tamaño de la vista ancho (mas una fila/columna para swapear)
	viewH = int(winH / tileH) + 1;							// Tamaño de la vista alto

	view = new int[viewH, viewW];							// Obtenemos la matriz de vista
	
	viewSprite = new vector<vector<Sprite*>*>();
	
	
	int lvlW = viewW * 10;
	int lvlH = viewH * 10;
}

Tilemap::~Tilemap() {

}

void Tilemap::DrawTilemap() {
	for (int i = 0; i < viewSprite->size(); i++) {
		for (int j = 0; j < viewSprite->size(); j++) {
			viewSprite->at(i)->at(j)->Draw();
		}
	}
}

void Tilemap::LoadLevel() {

}

void Tilemap::LoadView() {

	int vH = viewH + CameraPos.x;
	int vW = viewW + CameraPos.y;

	for (int i = 0; i < vH; i++) {
		for (int j = 0; j < vW; j++) {
			int offsetX = i + CameraPos.x;
			int offsetY = i + CameraPos.y;
			view[i, j] = level[offsetX, offsetY];
		}
	}
}

void Tilemap::UpdateTilemap() {
	instance->ClearLayer(Layers::Tile);
	instance->ClearLayer(Layers::ObjectTile);

}

void Tilemap::LoadViewSprite() {
	int posx = -15;
	int posy = 9;
	for (int i = 0; i < viewSprite->size(); i++) {
		posx = -11;
		Sprite * temp = new Sprite(render, 1, 1);
		temp->SetMaterial(material);
		temp->SetPos(posx, posy, 0);
		viewSprite->at(i)->at(j) = temp;
	}
	posy -= 2;
}