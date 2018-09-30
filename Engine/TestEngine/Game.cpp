#include "Game.h"
Game::Game() {
	i = 0;
}
Game::~Game() {

}
bool Game::OnStart() {

	translation = 0;
	rotation = 0;
	speed = 0;

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
bool Game::OnUpdate() {																			// Toda la logica va aca
	i++;

	//Triangulo N1
	tr1->SetPos(4.0f, 4.0f, 0.0f);

	//Triangulo N2
	tr2->SetPos(0.0f, -4.0f, 0.0f);																// Seteo la posicion del triangulo
	speed = 2.0f;																				// Creo una variable que voy a utilizar como velocidad
	rotation += speed * time;																	// le digo a la variable rotacion que se sume con la velocidad * time	
	tr2->SetRotZ(rotation);																		// le mando a la rotacion ese calculo para que pueda rotar hasta que se apague el programa
		
	//Rectangulo N1
	speed = 1.0f;
	translation += speed * time;
	rt1->SetPos(-4.0f, -10.0f + translation, 0.0f);

	cout<<"Game::OnUpdate(): "<<i<< endl;
	return true;
}
void Game::OnDraw() {
	tr1->Draw();																				// Le digo al Triangulo que se dibuje

	tr2->Draw();																				// Le digo al Triangulo que se dibuje

	rt1->Draw();																				// Le digo al Rectangulo que se dibuje

	cout << "Game::OnDraw(): " << i << endl;
}