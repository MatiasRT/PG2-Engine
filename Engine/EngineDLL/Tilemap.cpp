#include "Tilemap.h"

Tilemap::Tilemap(Renderer* renderer, float tWidth, float tHeight, const char* fName, float tilesX, float tilesY, float tOffset, float tSize, vector<int>* cTiles, vector<int>* modTiles) : Shape(renderer) {

	filename = fName;
	tilemapWidth = tWidth;
	tilemapHeight = tHeight;
	cantTilesX = tilesX;
	cantTilesY = tilesY;
	tileOffset = tOffset;
	tileSize = tSize;
	vtxCount = tWidth * tHeight * 4 * 3;
	cantUVvertex = tWidth * tHeight * 4 * 2;


	mapIds = new vector<int>();
	LoadMapIDs(fName);

	tilesWithCollides = new vector<int>();
	tilesWithCollides = cTiles;

	modTilesWithCollides = new vector<int>();
	modTilesWithCollides = modTiles;

	tilesColliderData = new vector<TileColliderData>();
	modTilesColliderData = new vector<TileColliderData>();

	CreateGrid(tHeight, tWidth);

	float* positions = &vertexArrayPos[0];

	textureVertex = new float[cantUVvertex];
	LoadUVs();

	SetTilemapVertex(positions, vtxCount);

	SetTextures(textureVertex, cantUVvertex);
}

void Tilemap::CreateGrid(float h, float w) {
	int aux = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {

			int row = i * 2;
			int col = j * 2;
			// Aca creo la grilla del tilemap. Son cuatro por las cuatro esquinas

			vertexArrayPos.push_back(-tileOffset + col);					// Aca guardo las coordenadas x
			vertexArrayPos.push_back(tileOffset - row);						// Aca guardo las coordenadas y
			vertexArrayPos.push_back(0.0f);									// Aca guardo las coordenadas z

			vertexArrayPos.push_back(-tileOffset + col);					// Aca guardo las coordenadas x
			vertexArrayPos.push_back((tileOffset - tileSize) - row);		// Aca guardo las coordenadas y
			vertexArrayPos.push_back(0.0f);									// Aca guardo las coordenadas z

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);		// Aca guardo las coordenadas x
			vertexArrayPos.push_back((tileOffset - tileSize) - row);		// Aca guardo las coordenadas y
			vertexArrayPos.push_back(0.0f);									// Aca guardo las coordenadas z

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);		// Aca guardo las coordenadas x
			vertexArrayPos.push_back(tileOffset - row);						// Aca guardo las coordenadas y
			vertexArrayPos.push_back(0.0f);									// Aca guardo las coordenadas z

			for (int k = 0; k < tilesWithCollides->size(); k++) {
				if (mapIds->at(aux) == tilesWithCollides->at(k)) {
					// Creo una segunda grilla para las colisiones
					TileColliderData colliderAux;

					colliderAux.positionX = (-tileOffset + col);			// Coordenadas x
					colliderAux.positionY = (tileOffset - row) - tileSize;	// Coordenadas y

					colliderAux.height = tileSize;
					colliderAux.width = tileSize;
					tilesColliderData->push_back(colliderAux);
				}
			}

			for (int k = 0; k < modTilesWithCollides->size(); k++) {
				if (mapIds->at(aux) == modTilesWithCollides->at(k)) {
					TileColliderData modColliderAux;

					modColliderAux.positionY = (tileOffset - row) - tileSize;
					modColliderAux.positionX = (-tileOffset + col);

					modColliderAux.height = tileSize;
					modColliderAux.width = tileSize;
					modTilesColliderData->push_back(modColliderAux);
				}
			}

			aux++;

		}
	}
	float* positions = &vertexArrayPos[0];

	textureVertex = new float[cantUVvertex];
}

void Tilemap::LoadUVs() {
	float textureW = 1 / cantTilesX;
	float textureH = 1 / cantTilesY;

	int idIndex = 0;

	for (int i = 0; i < cantUVvertex; i = i + 8) {	// Cargo las UV a cada vertice
		textureVertex[i] = 0.0f;
		textureVertex[i + 1] = 1.0f;

		textureVertex[i + 2] = 0.0f;
		textureVertex[i + 3] = 1.0f - textureH;

		textureVertex[i + 4] = textureW;
		textureVertex[i + 5] = 1.0f - textureH;

		textureVertex[i + 6] = textureW;
		textureVertex[i + 7] = 1.0f;

		int row = 0;
		int column = mapIds->at(idIndex);

		while (column >= cantTilesX) {				// Si llego a la cantidad de columnas, bajo a la siguente linea
			column -= cantTilesX;
			row++;
		}
													// Sumo por el alto y ancho de la imagen para que se dibujen todos los tiles
		textureVertex[i] += textureW * column;
		textureVertex[i + 1] -= textureH * row;

		textureVertex[i + 2] += textureW * column;
		textureVertex[i + 3] -= textureH * row;

		textureVertex[i + 4] += textureW * column;
		textureVertex[i + 5] -= textureH * row;

		textureVertex[i + 6] += textureW * column;
		textureVertex[i + 7] -= textureH * row;

		idIndex++;
	}
}

void Tilemap::SetTextures(float* vertex, int cant) {
	txrBufferId = renderer->GenBuffer(vertex, sizeof(float)* cant);			// Genero buffer de texture
}

void Tilemap::LoadTexture(const char* name) {
	header = Importer::LoadBMP(name);
	UVBufferID = renderer->GenTextureBuffer(header.width, header.height, header.data);
}

void Tilemap::Draw() {
	DrawMesh(PRIMITIVE_QUAD);
}

void Tilemap::DrawMesh(int drawType) {
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(worldMatrix);


	if (material != NULL) {
		material->Bind(filename, UVBufferID);
		material->SetMatrixProperty(renderer->GetWVP());
		//material->BindTexture();
	}

	renderer->BeginDraw(0);
	renderer->BeginDraw(1);
	renderer->BindBuffer(bufferId, 0);
	renderer->BindTextureBuffer(txrBufferId, 1);
	renderer->DrawBuffer(vtxCount, drawType);
	renderer->EndDraw(0);
	renderer->EndDraw(1);
}

void Tilemap::LoadMapIDs(const char* file) {
	string buffer;
	ifstream tileFile(file);

	while (getline(tileFile, buffer, ',')) {
		mapIds->push_back(stoi(buffer));			// Leo el .csv y me lo guardo en el buffer
	}
}

void Tilemap::SetTilemapVertex(float* vertex, int cant) {
	bufferId = renderer->GenBuffer(vertex, sizeof(float) * cant);				// Genero el buffer
}

bool Tilemap::CheckCollission(float pTranslationX, float pTranslationY, float pHeight, float pWidht) {

	for (int i = 0; i < tilesColliderData->size(); i++) {
		if (((pTranslationX + (pWidht / 2)) >= tilesColliderData->at(i).positionX) &&
			((pTranslationX - (pWidht / 2)) <= tilesColliderData->at(i).positionX + tilesColliderData->at(i).width) &&
			(pTranslationY + (pHeight / 2) >= tilesColliderData->at(i).positionY) &&
			(pTranslationY - (pHeight / 2) <= tilesColliderData->at(i).positionY + tilesColliderData->at(i).height)) {
			return true;
		}
	}
	return false;
}

bool Tilemap::CheckModCollission(float pTranslationX, float pTranslationY, float pHeight, float pWidht) {

	for (int i = 0; i < modTilesColliderData->size(); i++) {
		if (((pTranslationX + (pWidht / 2)) >= modTilesColliderData->at(i).positionX) &&
			((pTranslationX - (pWidht / 2)) <= modTilesColliderData->at(i).positionX + modTilesColliderData->at(i).width) &&
			(pTranslationY + (pHeight / 2) >= modTilesColliderData->at(i).positionY) &&
			(pTranslationY - (pHeight / 2) <= modTilesColliderData->at(i).positionY + modTilesColliderData->at(i).height)) {
			return true;
		}
	}
	return false;
}


void Tilemap::UpdateTilemapColliderPosition(float diffX, float diffY) {
	for (int i = 0; i < tilesColliderData->size(); i++) {
		tilesColliderData->at(i).positionX += diffX;
		tilesColliderData->at(i).positionY += diffY;
	}
	for (int i = 0; i < modTilesColliderData->size(); i++) {
		modTilesColliderData->at(i).positionX += diffX;
		modTilesColliderData->at(i).positionY += diffY;
	}
}