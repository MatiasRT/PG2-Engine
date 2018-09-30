#include "Rectangle.h"

Rectangle::Rectangle(Renderer* renderer) : Entity(renderer) {
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;

	vertex = new float[12]{													//Este arreglo representa los cuatro vertices que tiene un rectangulo (Acordate que X es a la derecha, e Y es arriba(dedos))
		-1.0f, -1.0f, 0.0f,													//Vertice 1: Lo estamos seteando en el (-1,-1) de la pantalla, que seria la esquina inferior izquierda de la pantalla
		1.0f, -1.0f, 0.0f,													//Vertice 2: Lo estamos seteando en el (1,-1) de la pantalla, que seria la esquina inferior derecha de la pantalla
		-1.0f, 1.0f, 0.0f,													//Vertice 3: Lo estamos seteando en el (-1, 1) de la pantalla, que seria la esquina superior izquierda de la pantalla
		1.0f, 1.0f, 0.0f													//Vertice 4: Lo estamos seteando en el (1, 1) de la pantalla, que seria la esquina superior derecha de la pantalla
	};

	SetVertices(vertex, 4);
}

Rectangle::~Rectangle() {
	Dispose();
}

void Rectangle::SetVertices(float* vertex, int count) {
	Dispose();

	vtxCount = count;
	shouldDispose = true;

	bufferId = renderer->GenBuffer(vertex, sizeof(float) * count * 3);
}

void Rectangle::Draw() {
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(worldMatrix);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty(renderer->GetWVP());
	}
	renderer->BeginDraw(0);													// Le decimos al renderer que comience a dibujar
	renderer->BindBuffer(bufferId, 0);										// Unimos el buffer con el buffer binding point
	renderer->DrawBuffer(vtxCount);											// El renderer dibuja el triangulo
	renderer->EndDraw(0);													// Deja de dibujar
}

void Rectangle::SetMaterial(Material* material) {
	this->material = material;
}

void Rectangle::Dispose() {
	if (shouldDispose) {
		renderer->DestroyBuffer(bufferId);
		delete[] vertex;
		shouldDispose = false;
	}
}