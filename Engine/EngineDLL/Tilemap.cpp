#include "Tilemap.h"

Tilemap::Tilemap(Renderer* _renderer, float _tilemapWidth, float _tilemapHeight, const char* _filename, float _cantTilesX, float _cantTilesY, float _tileOffset, float _tileSize, vector<int>* _colliderTiles) : Shape(_renderer) {

	filename = _filename;
	tilemapWidth = _tilemapWidth;
	tilemapHeight = _tilemapHeight;
	cantTilesX = _cantTilesX;
	cantTilesY = _cantTilesY;
	tileOffset = _tileOffset;
	tileSize = _tileSize;
	vtxCount = _tilemapWidth * _tilemapHeight * 4 * 3;
	cantUVvertex = _tilemapWidth * _tilemapHeight * 4 * 2;


	mapIds = new vector<int>();
	LoadMapIDs(_filename);
	tilesWithCollides = new vector<int>();
	tilesWithCollides = _colliderTiles;
	tilesColliderData = new vector<TileColliderData>();
	int aux = 0;
	for (int i = 0; i < _tilemapHeight; i++) {
		for (int j = 0; j < _tilemapWidth; j++) {

			int col = j * 2;
			int row = i * 2;

			vertexArrayPos.push_back(-tileOffset + col);
			vertexArrayPos.push_back(tileOffset - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-tileOffset + col);
			vertexArrayPos.push_back((tileOffset - tileSize) - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);
			vertexArrayPos.push_back((tileOffset - tileSize) - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(-(tileOffset - tileSize) + col);
			vertexArrayPos.push_back(tileOffset - row);
			vertexArrayPos.push_back(0.0f);

			for (int k = 0; k < tilesWithCollides->size(); k++) {
				if (mapIds->at(aux) == tilesWithCollides->at(k)) {
					TileColliderData colliderAux;

					colliderAux.positionY = (tileOffset - row) - tileSize;
					colliderAux.positionX = (-tileOffset + col);
					//cout << colliderAux.positionX << " - " << colliderAux.positionY << endl;
					colliderAux.height = tileSize;
					colliderAux.width = tileSize;
					tilesColliderData->push_back(colliderAux);
				}
			}

			aux++;

		}
	}
	float* p = &vertexArrayPos[0];

	textureVertex = new float[cantUVvertex];
	LoadUVs();

	SetTilemapVertex(p, vtxCount);

	SetTextures(textureVertex, cantUVvertex);
}

Tilemap::~Tilemap() {

}

void Tilemap::SetTextures(float* vertex, int cant) {
	
	txrBufferId = renderer->GenBuffer(vertex, sizeof(float)* cant);
}

void Tilemap::LoadTexture(const char* name) {
	header = Importer::LoadBMP(name);
	UVBufferID = renderer->GenTextureBuffer(header.width, header.height, header.data);
}

void Tilemap::DrawMesh(int _drawType) {
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
	renderer->DrawBuffer(vtxCount, _drawType);
	renderer->EndDraw(0);
	renderer->EndDraw(1);
}

void Tilemap::Draw() {
	DrawMesh(PRIMITIVE_QUAD);
}

void Tilemap::LoadMapIDs(const char* _file) {
	string buffer;
	ifstream tileFile(_file);

	while (getline(tileFile, buffer, ',')) {
		mapIds->push_back(stoi(buffer));
	}
}

void Tilemap::LoadUVs() {
	float textureW = 1 / cantTilesX;
	float textureH = 1 / cantTilesY;

	int idIndex = 0;

	for (int i = 0; i < cantUVvertex; i = i + 8) {
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

		while (column >= cantTilesX) {
			column -= cantTilesX;
			row++;
		}

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

void Tilemap::SetTilemapVertex(float* _vertex, int _cant) {
	bufferId = renderer->GenBuffer(_vertex, sizeof(float) * _cant);
}


bool Tilemap::NextTileIsCollider(float _playerTranslationX, float _playerTranslationY, float _playerHeight, float _playerWidht) {

	float col = (((_playerTranslationX - GetPos().x) / tileSize) * tileSize) + GetPos().x;
	float row = (((_playerTranslationY + GetPos().y) / tileSize) * tileSize) - GetPos().y;

	for (int i = 0; i < tilesColliderData->size(); i++) {
		if (((col + (_playerWidht / 2)) >= tilesColliderData->at(i).positionX) && ((col - (_playerWidht / 2)) <= tilesColliderData->at(i).positionX + tilesColliderData->at(i).width) && (row + (_playerHeight / 2) >= tilesColliderData->at(i).positionY) && (row - (_playerHeight / 2) <= tilesColliderData->at(i).positionY + tilesColliderData->at(i).height)) {
			return true;
		}
	}
	return false;
}

void Tilemap::UpdateTilemapColliderPosition(float _diferenceX, float _diferenceY) {
	for (int i = 0; i < tilesColliderData->size(); i++) {
		tilesColliderData->at(i).positionX += _diferenceX;
		tilesColliderData->at(i).positionY += _diferenceY;
	}
}