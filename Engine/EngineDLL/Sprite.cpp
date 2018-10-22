#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, const char * name) : Shape(renderer) {
	
	file = name;

	vertex = new float[12]{													//Este arreglo representa los cuatro vertices que tiene un rectangulo (Acordate que X es a la derecha, e Y es arriba(dedos))
		-1.0f, -1.0f, 0.0f,													//Vertice 1: Lo estamos seteando en el (-1,-1) de la pantalla, que seria la esquina inferior izquierda de la pantalla
		1.0f, -1.0f, 0.0f,													//Vertice 2: Lo estamos seteando en el (1,-1) de la pantalla, que seria la esquina inferior derecha de la pantalla
		-1.0f, 1.0f, 0.0f,													//Vertice 3: Lo estamos seteando en el (-1, 1) de la pantalla, que seria la esquina superior izquierda de la pantalla
		1.0f, 1.0f, 0.0f													//Vertice 4: Lo estamos seteando en el (1, 1) de la pantalla, que seria la esquina superior derecha de la pantalla
	};

	textureVertex = new float[8]{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	LoadBMP(file);

	SetVertices(vertex, 4);
	SetTextureVertices(4);
}

void Sprite::LoadBMP(const char * name) {
	header = Importer::LoadBMP(name);
}

void Sprite::SetTextureVertices(int count) {
	DisposeTexture();

	vtxTextureCount = count;
	shouldDisposeTexture = true;

	textureBufferId = renderer->GenTextureBuffer(header.width, header.height, header.data);
}

void Sprite::DrawMesh(int type) {
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(worldMatrix);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty(renderer->GetWVP());
	}
	renderer->BeginDraw(0);
	renderer->BeginDraw(1);																	// Le decimos al renderer que comience a dibujar
	renderer->BindBuffer(bufferId, 0);
	renderer->BindTextureBuffer(textureBufferId, 1);										// Unimos el buffer con el buffer binding point
	renderer->DrawBuffer(vtxTextureCount, type);											// El renderer dibuja el triangulo
	renderer->EndDraw(0);
	renderer->EndDraw(1);																	// Deja de dibujar
}

void Sprite::DisposeTexture() {
	if (shouldDisposeTexture) {
		renderer->DestroyBuffer(textureBufferId);
		shouldDisposeTexture = false;
	}
}

void Sprite::Draw() {
	DrawMesh(GL_TRIANGLE_STRIP);
}

Sprite::~Sprite() {
	delete[] vertex;
	delete[] textureVertex;
}

void Sprite::SetMaterial(Material* material) {
	this->material = material;
}