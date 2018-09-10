#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

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
		/*
		//GLuint VertexArrayID;
		//glGenVertexArrays(1, &VertexArrayID);
		//glBindVertexArray(VertexArrayID);
		*/
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
void Renderer::GenBuffer(float* buffer, int size) {
	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
}

void Renderer::DrawBuffer(unsigned int vtxbuffer, int size) {
	// 1rst attribute buffer : vértices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vtxbuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	// Dibujar el triángulo !
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
	glDisableVertexAttribArray(0);
}