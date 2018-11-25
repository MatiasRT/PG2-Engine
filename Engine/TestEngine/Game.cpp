#include "Game.h"

bool Game::OnStart() {

	translation = 0;
	rotation = 0;
	speed = 1;

	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int textureID = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	CollisionManager* instance = CollisionManager::Instance();

	//tr1 = new Triangle(renderer);																// Creo un Triangulo, y le paso como parametro el renderer, asi se puede dibujar
	//tr1->SetMaterial(mat1);																	// Llamo al metodo SetMaterial para decirle al Triangulo cual es el material que tiene que utilizar

	//rt1 = new Rectangle(renderer);															// Creo un Rectangulo, y le paso como parametro el renderer, asi se puede dibujar
	//rt1->SetMaterial(mat1);																	// Llamo al metodo SetMaterial para decirle al Rectangulo cual es el material que tiene que utilizar

	//cr1 = new Circle(renderer, 1, 30);														// Creo un Rectangulo, y le paso como parametro el renderer, asi se puede dibujar, y le paso tambien el radio que va atener, y la cantidad de triangulos que quiero que formen el circulo (TRIANGLE_FAN, a lo paraguas)
	//cr1->SetMaterial(mat1);

	sp1 = new Sprite(renderer, 8, 8);
	sp1->SetMaterial(mat2);
	sp1->LoadBMP("asteroid.bmp");
	sp1->SetPos(0.0f, -6.0f, 0.0f);
	sp1->SetBoundingBox(2.0f, 2.0f, false, false);
	instance->FillingBoxList(Player_layer, sp1);
	sp1->SetAnimation(0, 63, 0.1f);

	sp2 = new Sprite(renderer, 6, 8);
	sp2->SetMaterial(mat2);
	sp2->LoadBMP("character.bmp");
	sp2->SetPos(0.0f, 6.0f, 0.0f);
	sp2->SetBoundingBox(2.0f, 2.0f, false, false);
	instance->FillingBoxList(Enemy_layer, sp2);
	sp2->SetAnimation(0, 47, 0.1f);

	//tr1->SetPos(9.0f, 0.0f, 0.0f);
	//rt1->SetPos(0.0f, 0.0f, 0.0f);
	//cr1->SetPos(-9.0f, 0.0f, 0.0f);

	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	CollisionManager::Instance()->BoxCollisionDetector();
	//i++;
	//speed = 1.0f;
	//rotation += speed * time;
	//rt1->SetRotZ(rotation);
	//tr1->SetRotY(rotation);
	//cr1->SetRotX(rotation);

	//translation += speed * time;
	//tr1->SetPos(9.0f - translation, 0.0f, 0.0f);
	//cr1->SetPos(-9.0f + translation, 0.0f, 0.0f);
	sp1->UpdateAnim(time);
	sp2->UpdateAnim(time);

	sp1->TranslationBox(0.0f, speed * time * 4.0f, 0.0f);											// Movemos con translation asi no pisamos la posicion original
	sp2->TranslationBox(0.0f, -speed * time * 2.0f, 0.0f);

	//cout<<"Game::OnUpdate(): "<<i<< endl;
	return true;
}

void Game::OnDraw() {
	//tr1->Draw();																				// Le digo al Triangulo que se dibuje
	//rt1->Draw();																				// Le digo al Rectangulo que se dibuje
	//cr1->Draw();																				// Le digo al Circulo que se dibuje
	sp1->Draw();
	sp2->Draw();

	//cout << "Game::OnDraw(): " << i << endl;
}

bool Game::OnStop() {
	//delete tr1;
	//delete rt1;
	//delete cr1;
	delete sp1;
	delete sp2;
	delete mat1;
	delete mat2;
	cout << "Game::OnStop()" << endl;
	return false;
}