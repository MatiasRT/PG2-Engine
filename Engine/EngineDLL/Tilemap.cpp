#include "Tilemap.h"

Tilemap::Tilemap(const char* filepath, int winWidth, int winHeight, Material * mat, Renderer * rend) {		// Cargamos el archivo
	
	render = rend;																			// Inicializamos variables
	material = mat;
	scrollX = 0;
	scrollY = 0;
	levelHeight = 1;
	levelWidth = 1;
	lastPosX = 0;
	lastPosY = 0;
	LastCameraPos = glm::vec3(0, 0, 0);
	CurrentCameraPos = glm::vec3(0, 0, 0);
	DeltaCameraPos = glm::vec3(0, 0, 0);

	instance = CollisionManager::Instance();												// Hacemos una instacia del CM porque los tiles van a utilizar cajas de colision

	string buffer;
	ifstream tilemap(filepath);																// Abrimos el archivo
	
	getline(tilemap, buffer);																// Extraemos la primera linea del archivo

	for (int i = 0; i < buffer.length(); i++)
		if (buffer[i] == ',')
			levelWidth++;																	// Saco la cantidad de columnas
	
	while (getline(tilemap, buffer)) {
		levelHeight++;																		// Saco la cantidad de filas
	}

	tilemap.clear();																		// Con esto eliminamos el estado de eof del stream, para que podamos seguir utilizandolo
	tilemap.seekg(0, std::ios::beg);														// Cambiamos la posicion del cursor en el archivo (primer parametro es el salto, y el segundo es el punto de partida)

	level = new vector<vector<int>*>(levelWidth);											// Inicializamos el vector con la cantidad de columnas totales
	for (int i = 0; i < levelWidth; i++)
		level->at(i) = new vector<int>(levelHeight);										// Le agrego las filas al vector
		
	if (tilemap.is_open()) {																// Preguntamos si el archivo esta abierto
		for (int i = 0; i < levelWidth; i++) {												// Recorremos por la cantidad de columnas, por el ancho

			getline(tilemap, buffer);														// Obtengo la primera linea
			int levelW = 0;

			for (int j = 0; j < buffer.length(); j++) {										// Los archivos CSV tienen los valores 0 (hay informacion) y -1 (esta vacio)
				if (buffer[j] == '0') {														// Si la linea que ley� contiene un cero es que hay informacion
					level->at(i)->at(levelW) = 1;											// Le mandamos al vector que en esa posicion hay un 1
					levelW++;																// Pasamos al siguiente caracter
				}
				else if (buffer[j] == '1') {												// Si la linea que ley� contiene un 1 (no importa el signo) es que esta vacio
					level->at(i)->at(levelW) = 0;											// Le asignamos un 0 en esa posicion del vector
					levelW++;																// Pasamos al siguiente caracter
				}
			}
		}
	}
	tilemap.close();																		// Una vez que leimos todo y llenamos el vector del nivel, cerramos el archivo.

	int tileHeight = 64;																	// Alto y ancho de cada tile
	int tileWidht = 64;

	viewHeight = (winHeight / tileHeight) + 4;												// La altura de la vista va a ser determinada por la ventana que utilizemos y el tama�o de los tiles, mas las dos columnas que necesitamos para swapear
	viewWidth = (winWidth / tileWidht) + 4;													// Lo mismo de lo de arriba, lo que cambia es que es para el ancho.

	xLevel = viewHeight;																	// Me guardo la altura y el ancho para usarlo mas tarde
	yLevel = viewWidth;

	//view = new int[viewWidth, viewHeight];												// Esta es la vista total
	view = new vector<vector<int>*>(viewWidth);												// Inicializo el vector con la cantidad de columnas totales
	for (int i = 0; i < viewWidth; i++)
		view->at(i) = new vector<int>(viewHeight);											// Le agrego las filas al vector

	viewSprite = new vector<vector<Tile*>*>(viewWidth);										// Inicializamos el vector con la cantidad de columnas totales
	for (int i = 0; i < viewWidth; i++)
		viewSprite->at(i) = new vector<Tile*>(viewHeight);									// Le agrego las filas al vector

	UploadSprite();
	LoadView();
}
	
void Tilemap::UploadSprite() {																// Aca cargamos los sprites
	for (int i = 0; i < viewWidth; i++) {													// Recorremos cada posicion de la grilla de tiles
		for (int j = 0; j < viewHeight; j++) {
			viewSprite->at(i)->at(j) = new Tile(render, 1, 1);								// Creo en esa posicion un tile
			viewSprite->at(i)->at(j)->SetMaterial(material);								// Le asigno el material
			viewSprite->at(i)->at(j)->SetBoundingBox(2.0f, 2.0f, 110.0f, false, false);		// Le asigno una bounding box
			viewSprite->at(i)->at(j)->UploadTexture("empty.bmp");							// Le cargo la textura con la que no va a colisionar
			viewSprite->at(i)->at(j)->UploadTexture("pastote.bmp");							// Le cargo la textura con la que si va a colisionar
		}
	}
}

void Tilemap::LoadView() {																	// Cargamos la vista
	int posX = -12;
	int posY = 9;

	for (int i = 0; i < levelWidth; i++) {
		posX = -13;																			// Posicion de x al comenzar
		for (int j = 0; j < levelHeight; j++) {
			if (i < viewWidth && j < viewHeight) {
				view->at(i)->at(j) = level->at(i)->at(j);									// Le asigno la posicion del nivel a la vista de un tile especifico
				if (view->at(i)->at(j) == 0) {												// Si hay un 0 en esa posicion no deberia colisionar 
					viewSprite->at(i)->at(j)->ChangeTexture(0);								// Cambiamos la textura
					instance->FillingBoxList(Layers::Tiles, viewSprite->at(i)->at(j));		// Le asignamos una layer
				}
				if (view->at(i)->at(j) == 1) {												// Si hay un 1 en esa posicion deberia colisionar 
					viewSprite->at(i)->at(j)->ChangeTexture(1);								// Cambiamos la textura
					instance->FillingBoxList(Layers::ObjectTile, viewSprite->at(i)->at(j));	// Le asignamos una layer
				}
				posX += 2;																	// Le sumo las dos columnas que swapean
				viewSprite->at(i)->at(j)->SetPos(posX, posY, 0);							// En la posicion especifica del tile le agrego una posicion de una entidad
			}
		}
		posY -= 2;																			// Se las resto
	}
}

void Tilemap::DrawTilemap() {
	for (int i = 0; i < viewWidth; i++) {													// Recorro el archo de la vista
		for (int j = 0; j < viewHeight; j++) {												// Recorro el largo de la vista
			viewSprite->at(i)->at(j)->Draw();												// Dibujo en cada posicion el valor que haya en la misma
		}
	}
}

void Tilemap::UpdateViewX() {
	int posX = 10;
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
		
	posX = 12;
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

Tilemap::~Tilemap() {																		// Libero memoria de las cosas creadas en el constructor
	for (int i = 0; i < viewWidth; i++) {
		for (int j = 0; j < viewHeight; j++) {
			delete viewSprite->at(i)->at(j);
		}
		delete viewSprite->at(i);
	}

	for (int i = 0; i < levelWidth; i++) {
		delete level->at(i);
	}
	delete level;

	for (int i = 0; i < viewWidth; i++) {
		delete view->at(i);
	}
	delete view;
}