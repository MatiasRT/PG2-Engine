#include "Renderer.h"

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
}
bool Renderer::Start() {
	cout << "Renderer::Start()" << endl;
	//this->window = window
	//window = gldwmakecurrent algo
	return true;
}
bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
	return false;
}