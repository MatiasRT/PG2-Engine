#include "ColorShape.h"

ColorShape::ColorShape(Renderer* renderer) : Entity(renderer) {
	shouldDispose = false;
	material = NULL;
	bufferId = -1;
	vtxCount = 0;
}

ColorShape::~ColorShape() {
	Dispose();
}

void ColorShape::SetVertices(float* vertex, int count) {
	Dispose();

	vtxCount = count;
	shouldDispose = true;

	bufferId = renderer->GenBuffer(vertex, sizeof(float) * count * 3);
}

void ColorShape::Draw() {
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(worldMatrix);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty(renderer->GetWVP());
	}
	renderer->BeginDraw(1);													// Le decimos al renderer que comience a dibujar
	renderer->BindBuffer(bufferId, 1);										// Unimos el buffer con el buffer binding point
	renderer->DrawBuffer(vtxCount, 1);											// El renderer dibuja el triangulo
	renderer->EndDraw(1);													// Deja de dibujar
}

void ColorShape::SetMaterial(Material* material) {
	this->material = material;
}

void ColorShape::Dispose() {
	if (shouldDispose) {
		renderer->DestroyBuffer(bufferId);
		shouldDispose = false;
	}
}