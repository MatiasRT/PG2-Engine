#include "Triangle.h"

Triangle::Triangle(Renderer* renderer): Entity(renderer){
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;

	vertex = new float[9]{													//Este arreglo representa los tres vertices que tiene un triangulo (Acordate que X es a la derecha, e Y es arriba(dedos))
		-1.0f, -1.0f, 0.0f,													//Vertice 1: Lo estamos seteando en el (-1,-1) de la pantalla, que seria la esquina inferior izquierda de la pantalla
		1.0f, -1.0f, 0.0f,													//Vertice 2: Lo estamos seteando en el (1,-1) de la pantalla, que seria la esquina inferior derecha de la pantalla
		0.0f,  1.0f, 0.0f,													//Vertice 3: Lo estamos seteando en el (0, 1) de la pantalla, que seria en el medio en la partte superior
	};

	SetVertices(vertex, 3);

}
Triangle::~Triangle(){
	Dispose();
}
void Triangle::SetVertices(float* vertex, int count) {
	Dispose();

	vtxCount = count;
	shouldDispose = true;

	bufferId = renderer->GenBuffer(vertex, sizeof(float) * count * 3);
}
void Triangle::Draw() {

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
void Triangle::SetMaterial(Material* material) {
	this->material = material;
}
void Triangle::Dispose() {
	if (shouldDispose) {
		renderer->DestroyBuffer(bufferId);
		delete[] vertex;
		shouldDispose = false;
	}
}