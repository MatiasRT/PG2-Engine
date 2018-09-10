#include "Triangle.h"

Triangle::Triangle(Renderer* renderer): Entity(renderer){
	shouldDispose = false;
	material = NULL;
	vertex = NULL;
	bufferId = -1;

	vertex = new float[9]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	SetVertices(vertex, 3);
}
Triangle::~Triangle(){
	Dispose();
}
void Triangle::SetVertices(float* vertex, int count) {
	Dispose();

	vtxCount = count;

	bufferId = renderer->GenBuffer(vertex, sizeof(float) * count * 3);
}
void Triangle::Draw() {
	renderer->DrawBuffer(bufferId, vtxCount);
}
void Triangle::Dispose() {
	if (shouldDispose) {
		//renderer->DestroyBuffer(bufferId);
		delete[] vertex;
		shouldDispose = false;
	}
}