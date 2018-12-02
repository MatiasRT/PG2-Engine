#include "Tilemap.h"

Tilemap::Tilemap(char* filepath, int winWidth, int winHeight, Material * material, Renderer * render) {		// Cargamos el archivo
	
	string buffer;
	ifstream tilemap(filepath);
	
	levelHeight = 1;
	levelWidth = 1;
	
	getline(tilemap, buffer);									// Extraemos la primera linea del archivo

	for (int i = 0; i < buffer.length(); i++)
		if (buffer[i] == ',')
			levelWidth++;										// Saco la cantidad de columnas
	
	while (getline(tilemap, buffer))
		levelHeight++;											// Saco la cantidad de filas

	tilemap.clear();											// Con esto eliminamos el estado de eof del stream, para que podamos seguir utilizandolo
	tilemap.seekg(0, std::ios::beg);							// Cambiamos la posicion del cursor en el archivo (primer parametro es el salto, y el segundo es el punto de partida)

	level = new vector<vector<int>*>(levelWidth);				// Inicializamos el vector con la cantidad de columnas totales
	
	for (int i = 0; i < levelWidth; i++)
		level->at(i) = new vector<int>(levelHeight);			// Le agrego las filas al vector
									
	for (int i = 0; i < levelWidth; i++) {						
			
		getline(tilemap, buffer);								// Obtengo la primera linea
		int levelW = 0;

		for (int j = 0; j < buffer.length(); j++) {				// Los archivos CSV tienen los valores 0 (hay informacion) y -1 (esta vacio)
			if (buffer[j] == '0') {								// Si la linea que leyó contiene un cero es que hay informacion 
				level->at(i)->at(levelW) = 1;					// Le mandamos al vector que en esa posicion hay un 1
				levelW++;										// Pasamos al siguiente caracter
			}
			else if (buffer[j] == '1') {						// Si la linea que leyó contiene un 1 (no importa el signo) es que esta vacio
				level->at(i)->at(levelW) = 0;					// Le asignamos un 0 en esa posicion del vector
				levelW++;										// Pasamos al siguiente caracter
			}
		}
	}
	tilemap.close();											// Una vez que leimos todo y llenamos el vector del nivel, cerramos el archivo.



	/*int tileW = 10;
	int tileH = 10;
	viewW = int(winW / tileW) + 1;							// Tamaño de la vista ancho (mas una fila/columna para swapear)
	viewH = int(winH / tileH) + 1;							// Tamaño de la vista alto

	view = new int[viewH, viewW];							// Obtenemos la matriz de vista
	
	viewSprite = new vector<vector<Sprite*>*>();
	
	
	int lvlW = viewW * 10;
	int lvlH = viewH * 10;*/
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

void Tilemap::UploadSprite() {

}

void Tilemap::LoadView() {
/*
	int vH = viewH + CameraPos.x;
	int vW = viewW + CameraPos.y;

	for (int i = 0; i < vH; i++) {
		for (int j = 0; j < vW; j++) {
			int offsetX = i + CameraPos.x;
			int offsetY = j + CameraPos.y;
			view[i, j] = level[offsetX, offsetY];
		}
	}
	*/
}

void Tilemap::UpdateTilemap() {
	instance->ClearLayer(Layers::Tile);
	instance->ClearLayer(Layers::ObjectTile);

}