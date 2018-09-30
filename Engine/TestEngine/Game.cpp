#include "Game.h"
Game::Game()
{
	i = 0;
}
Game::~Game()
{
}
bool Game::OnStart() {
	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexShader.txt", "FragmentShader.txt");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int colorID = mat2->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");

	tr1 = new Triangle(renderer);																// Creo un Triangulo, y le paso como parametro el renderer, asi se puede dibujar
	tr1->SetMaterial(mat1);																		// Llamo al metodo SetMaterial para decirle al Triangulo cual es el material que tiene que utilizar

	tr2 = new Triangle(renderer);																// Creo un Triangulo, y le paso como parametro el renderer, asi se puede dibujar
	tr2->SetMaterial(mat1);																		// Llamo al metodo SetMaterial para decirle al Triangulo cual es el material que tiene que utilizar
	
	rt1 = new Rectangle(renderer);																// Creo un Rectangulo, y le paso como parametro el renderer, asi se puede dibujar
	rt1->SetMaterial(mat2);																		// Llamo al metodo SetMaterial para decirle al Rectangulo cual es el material que tiene que utilizar

	cout<<"Game::OnStart()"<<endl;
	return true;
}
bool Game::OnStop() {
	cout<<"Game::OnStop()"<<endl;
	return false;
}
bool Game::OnUpdate() {
	i++;

	tr2->SetPos(-4.0f, -4.0f, 0.0f);															// Seteo la posicion del triangulo
	rt1->SetPos(4.0f, 4.0f, 0.0f);																// Seteo la posicion del rectangulo

	cout<<"Game::OnUpdate(): "<<i<< endl;
	return true;
}
void Game::OnDraw() {
	tr1->Draw();																				// Le digo al Triangulo que se dibuje

	tr2->Draw();																				// Le digo al Triangulo que se dibuje

	rt1->Draw();																				// Le digo al Rectangulo que se dibuje

	cout << "Game::OnDraw(): " << i << endl;
}