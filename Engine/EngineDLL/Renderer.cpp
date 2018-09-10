#include "Renderer.h"
#include "GLFW/glfw3.h"

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
}
bool Renderer::Start(Window* windowPtr) {
	if (windowPtr != NULL) {
		window = windowPtr;
		glfwMakeContextCurrent((GLFWwindow*)window->GetWindow()); //Le dice cual es la ventana que va a usar
		cout << "Renderer::Start()" << endl;
		return true;
	}
	return false;
}
bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
	return false;
}
void Renderer::ClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::ClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
void Renderer::SwapBuffers() {
	glfwSwapBuffers((GLFWwindow*)window->GetWindow());
}