#include "Game.h"

bool Game::OnStart() {

	translation = 0;
	rotation = 0;
	speed = 0;

	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int textureID = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	tr1 = new Triangle(renderer);																// Creo un Triangulo, y le paso como parametro el renderer, asi se puede dibujar
	tr1->SetMaterial(mat1);																		// Llamo al metodo SetMaterial para decirle al Triangulo cual es el material que tiene que utilizar

	rt1 = new Rectangle(renderer);																// Creo un Rectangulo, y le paso como parametro el renderer, asi se puede dibujar
	rt1->SetMaterial(mat1);																		// Llamo al metodo SetMaterial para decirle al Rectangulo cual es el material que tiene que utilizar

	cr1 = new Circle(renderer, 1, 30);															// Creo un Rectangulo, y le paso como parametro el renderer, asi se puede dibujar, y le paso tambien el radio que va atener, y la cantidad de triangulos que quiero que formen el circulo (TRIANGLE_FAN, a lo paraguas)
	cr1->SetMaterial(mat1);

	sp1 = new Sprite(renderer);
	sp1->SetMaterial(mat2);
	sp1->LoadBMP("sample2.bmp");

	tr1->SetPos(9.0f, 0.0f, 0.0f);
	rt1->SetPos(0.0f, 0.0f, 0.0f);
	cr1->SetPos(-9.0f, 0.0f, 0.0f);

	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	i++;
	speed = 1.0f;
	rotation += speed * time;
	rt1->SetRotZ(rotation);
	tr1->SetRotY(rotation);
	cr1->SetRotX(rotation);

	translation += speed * time;
	tr1->SetPos(9.0f - translation, 0.0f, 0.0f);
	cr1->SetPos(-9.0f + translation, 0.0f, 0.0f);

	cout<<"Game::OnUpdate(): "<<i<< endl;
	return true;
}

void Game::OnDraw() {
	tr1->Draw();																				// Le digo al Triangulo que se dibuje
	rt1->Draw();																				// Le digo al Rectangulo que se dibuje
	cr1->Draw();																				// Le digo al Circulo que se dibuje
	sp1->Draw();

	cout << "Game::OnDraw(): " << i << endl;
}

bool Game::OnStop() {
	delete tr1;
	delete rt1;
	delete cr1;
	delete sp1;
	delete mat1;
	cout << "Game::OnStop()" << endl;
	return false;
}