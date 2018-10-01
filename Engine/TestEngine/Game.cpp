#include "Game.h"

bool Game::OnStart() {

	translation = 0;
	rotation = 0;
	speed = 0;

	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	tr1 = new Triangle(renderer);																// Creo un Triangulo, y le paso como parametro el renderer, asi se puede dibujar
	tr1->SetMaterial(mat1);																		// Llamo al metodo SetMaterial para decirle al Triangulo cual es el material que tiene que utilizar

	rt1 = new Rectangle(renderer);																// Creo un Rectangulo, y le paso como parametro el renderer, asi se puede dibujar
	rt1->SetMaterial(mat1);																		// Llamo al metodo SetMaterial para decirle al Rectangulo cual es el material que tiene que utilizar

	tr1->SetPos(5, 0, 0);
	rt1->SetPos(0, 0, 0);

	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnStop() {
	delete tr1;
	delete rt1;
	delete mat1;
	cout<<"Game::OnStop()"<<endl;
	return false;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	i++;
	speed = 1.0f;
	rotation += speed * time;
	rt1->SetRotZ(rotation);

	cout<<"Game::OnUpdate(): "<<i<< endl;
	return true;
}

void Game::OnDraw() {
	tr1->Draw();																				// Le digo al Triangulo que se dibuje
	rt1->Draw();																				// Le digo al Rectangulo que se dibuje
	cout << "Game::OnDraw(): " << i << endl;
}