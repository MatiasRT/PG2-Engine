#include "Triangle.h"

Triangle::Triangle(){

}
Triangle::~Triangle(){

}
void Triangle::SetVertices() {
	static const float g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
}
void Triangle::Draw() {

}