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
		glfwMakeContextCurrent((GLFWwindow*)window->GetWindow());						//Le dice cual es la ventana que va a usar
		
		//GLuint VertexArrayID;
		if (glewInit() != GLEW_OK) {
			cout << "Fallo al inicializar GLEW\n" << endl;
			return -1;
		}
		glGenVertexArrays(1, &VertexArrayID);											//Creamos el Vertex Array Object. Esto debe hacerse antes de cualquier llamada a una funcion OpenGL
		glBindVertexArray(VertexArrayID);												//Creamos el Vertex Array Object

		ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

		ViewMatrix = glm::lookAt(
			glm::vec3(0, 0, 3),															//Camara en 0,0,3 en el World space
			glm::vec3(0, 0, 0),															//Mira hacia el origen
			glm::vec3(0, 1, 0)															//La cabeza esta hacia arriba (0, -1, 0 va a mirar dado vuelta) 
		);

		WorldMatrix = glm::mat4(1.0f);
		
		UpdateWVP();

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::ClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
void Renderer::SwapBuffers() {
	glfwSwapBuffers((GLFWwindow*)window->GetWindow());
}
unsigned int Renderer::GenBuffer(float* buffer, int size) {								// Aca creamos el buffer. Esto solo debe hacerse una vez

	unsigned int vertexbuffer;															// Identificamos el vertex buffer
	glGenBuffers(1, &vertexbuffer);														// Generamos un buffer, y ponemos el resultado en el vertexbuffer que acabamos de crear
																						 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);										// Los siguientes comandos le darán características especiales al 'vertexbuffer'
																					
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);						// Le damos a OpenGL nuestros vertices
	return vertexbuffer;
}

void Renderer::DrawBuffer(unsigned int vtxbuffer, int size) {							// Dibujamos en el buffer
	// 1rst attribute buffer : vértices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vtxbuffer);
	glVertexAttribPointer(
		0,																				// atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,																				// tamaño
		GL_FLOAT,																		// tipo
		GL_FALSE,																		// normalizado?
		0,																				// Paso
		(void*)0																		// desfase del buffer
	);
	// Dibujar el triángulo !
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
	glDisableVertexAttribArray(0);
}
void Renderer::DestroyBuffer(unsigned int buffer) {
	glDeleteBuffers(1, &buffer);														// Recibe el buffer que hay que eliminar, y lo hacemos con una funcion de OpenGL
}
void Renderer::LoadIdentityMatrix() {
	WorldMatrix = glm::mat4(1.0f);
}
void Renderer::SetModelMatrix(glm::mat4 mat) {
	WorldMatrix = mat;
	UpdateWVP();
}
void Renderer::MultiplyModelMatrix(glm::mat4 mat) {
	WorldMatrix *= mat;
	UpdateWVP();
}
void Renderer::UpdateWVP() {
	wvp = ProjectionMatrix * ViewMatrix * WorldMatrix;
}
void Renderer::BeginDraw(){

}
void Renderer::BindBuffer(){

}
void Renderer::EndDraw(){

}