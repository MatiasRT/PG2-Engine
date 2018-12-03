#include "Tilemap.h"

Tilemap::Tilemap(const char* filepath, int winWidth, int winHeight, Material * mat, Renderer * rend) {		// Cargamos el archivo
	
	render = rend;													// Inicializamos variables
	material = mat;
	scrollX = 0;
	scrollY = 0;
	levelHeight = 1;
	levelWidth = 1;
	xLevel = viewHeight;
	yLevel = viewWidth;
	LastCameraPos = glm::vec3(0,0,0);
	CurrentCameraPos = glm::vec3(0, 0, 0);
	DeltaCameraPos = glm::vec3(0, 0, 0);

	instance = CollisionManager::Instance();						// Hacemos una instacia del CM porque los tiles van a utilizar cajas de colision
	
	string buffer;
	ifstream tilemap(filepath);
	
	getline(tilemap, buffer);										// Extraemos la primera linea del archivo

	for (int i = 0; i < buffer.length(); i++)
		if (buffer[i] == ',')
			levelWidth++;											// Saco la cantidad de columnas
	
	while (getline(tilemap, buffer)) {
		levelHeight++;												// Saco la cantidad de filas
	}

	tilemap.clear();												// Con esto eliminamos el estado de eof del stream, para que podamos seguir utilizandolo
	tilemap.seekg(0, std::ios::beg);								// Cambiamos la posicion del cursor en el archivo (primer parametro es el salto, y el segundo es el punto de partida)

	level = new vector<vector<int>*>(levelWidth);					// Inicializamos el vector con la cantidad de columnas totales
	for (int i = 0; i < levelWidth; i++)
		level->at(i) = new vector<int>(levelHeight);				// Le agrego las filas al vector
		
	if (tilemap.is_open()) {
		for (int i = 0; i < levelWidth; i++) {

			getline(tilemap, buffer);								// Obtengo la primera linea
			int levelW = 0;

			for (int j = 0; j < buffer.length(); j++) {				// Los archivos CSV tienen los valores 0 (hay informacion) y -1 (esta vacio)
				switch (buffer[j]) {
				case '0':
					level->at(i)->at(levelW) = 1;
					levelW++;
					break;
				case '1':
					level->at(i)->at(levelW) = 0;
					levelW++;
					break;
				}
				/*if (buffer[j] == '0') {							// Si la linea que leyó contiene un cero es que hay informacion
					level->at(i)->at(levelW) = 1;					// Le mandamos al vector que en esa posicion hay un 1
					levelW++;										// Pasamos al siguiente caracter
				}
				else if (buffer[j] == '1') {						// Si la linea que leyó contiene un 1 (no importa el signo) es que esta vacio
					level->at(i)->at(levelW) = 0;					// Le asignamos un 0 en esa posicion del vector
					levelW++;										// Pasamos al siguiente caracter
				}*/
			}
		}
	}
	tilemap.close();												// Una vez que leimos todo y llenamos el vector del nivel, cerramos el archivo.

	int tileHeight = 256 / 4;										// Alto y ancho de cada tile
	int tileWidht = 256 / 4;

	viewHeight = (winHeight / tileHeight) + 4;						// La altura de la vista va a ser determinada por la ventana que utilizemos y el tamaño de los tiles, mas las dos columnas que necesitamos para swapear
	viewWidth = (winWidth / tileWidht) + 4;							// Lo mismo de lo de arriba, lo que cambia es que es para el ancho.

	//view = new int[viewWidth, viewHeight];						// Esta es la vista total
	view = new vector<vector<int>*>(viewWidth);
	for (int i = 0; i < viewWidth; i++)
		view->at(i) = new vector<int>(viewHeight);

	viewSprite = new vector<vector<Tile*>*>(viewWidth);				// Inicializamos el vector con la cantidad de columnas totales
	for (int i = 0; i < viewWidth; i++)
		viewSprite->at(i) = new vector<Tile*>(viewHeight);			// Le agrego las filas al vector

	UploadSprite();
	LoadView();
}
	
void Tilemap::UploadSprite() {
	for (int i=0;i<viewWidth; i++)
		for (int j = 0; j < viewHeight; j++) {
			viewSprite->at(i)->at(j) = new Tile(render, 1, 1);
			viewSprite->at(i)->at(j)->SetMaterial(material);
			viewSprite->at(i)->at(j)->SetBoundingBox(2.0f, 2.0f, 0, true, true);
			viewSprite->at(i)->at(j)->UploadTexture("empty.bmp");
			viewSprite->at(i)->at(j)->UploadTexture("sample2.bmp");
		}
}

void Tilemap::LoadView() {
	int posX = -12;
	int posY = 9;
	lastPosX = 0;
	lastPosY = 0;

	for (int i = 0; i < levelWidth; i++) {
		posX = -12;
		for (int j = 0; j < levelHeight; j++) {
			if (i < viewWidth && j < viewHeight) {
				view->at(i)->at(j) = level->at(i)->at(j);
				if (view->at(i)->at(j) == 0) {
					viewSprite->at(i)->at(j)->ChangeTexture(0);
					instance->FillingBoxList(Layers::Tiles, viewSprite->at(i)->at(j));
				}
				if (view->at(i)->at(j) == 1) {
					viewSprite->at(i)->at(j)->ChangeTexture(1);
					instance->FillingBoxList(Layers::ObjectTile, viewSprite->at(i)->at(j));
				}
				posX += 2;
				viewSprite->at(i)->at(j)->SetPos(posX, posY, 0);
			}
		}
		posY -= 2;
	}
}

void Tilemap::DrawTilemap() {
	for (int i = 0; i < viewWidth; i++) {						// Recorro el archo de la vista
		for (int j = 0; j < viewHeight; j++) {					// Recorro el largo de la vista
			viewSprite->at(i)->at(j)->Draw();					// Dibujo en cada posicion el valor que haya en la misma
		}
	}
}

void Tilemap::UpdateViewX() {
	int posX = 12;
	int posY = 9;
																// Updateamos x
	for (int i = 0; i < viewWidth; i++) {
		for (int j = 1; j < viewHeight; j++) {
			view->at(i)->at(j - 1) = view->at(i)->at(j);
		}
	}
	for (int i = 0; i < viewWidth; i++) {
		int pos = level->at(i)->at(xLevel);
		view->at(i)->at(viewHeight - 1) = pos;
	}
																// volver a dibujar
	for (int j = 0; j < viewWidth; j++) {
		if (view->at(j)->at(viewHeight - 1) == 0) {
			viewSprite->at(j)->at(lastPosX)->ChangeTexture(0);
			instance->FillingBoxList(Layers::Tiles, viewSprite->at(j)->at(lastPosX));
		}
		if (view->at(j)->at(viewHeight - 1) == 1) {
			viewSprite->at(j)->at(lastPosX)->ChangeTexture(1);
			instance->FillingBoxList(Layers::ObjectTile, viewSprite->at(j)->at(lastPosX));
		}
		viewSprite->at(j)->at(lastPosX)->SetPos(posX + LastCameraPos.x, posY, 0);
		posY -= 2;
	}
	if (lastPosX < viewHeight - 1) 
		lastPosX++;
	else 
		lastPosX = 0;
}

void Tilemap::UpdateTilemap() {
	CurrentCameraPos = render->GetCameraPos();
	DeltaCameraPos = CurrentCameraPos - LastCameraPos;
	LastCameraPos = CurrentCameraPos;
																//UpdateX
	scrollX += DeltaCameraPos.x;
	if (scrollX >= 2) {
		if (xLevel < levelWidth - 1)
			xLevel++;
		UpdateViewX();
		scrollX = 0;
	}
	else {
		if (scrollX <= -2) {
			if (xLevel < 0)
				xLevel--;
			UpdateViewX();
			scrollX = 0;
		}
	}
}

Tilemap::~Tilemap() {											// Libero memoria de las cosas creadas en el constructor
	/*for (int i = 0; i < viewWidth; i++) {
		for (int j = 0; j < viewWidth; j++) {
			delete viewSprite->at(i)->at(j);
		}
		delete viewSprite->at(i);
		delete level->at(i);
	}
	delete view;*/
}