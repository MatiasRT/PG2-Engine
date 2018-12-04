#include "Game.h"

bool Game::OnStart() {
	i = 0;
	translation = 0;
	rotation = 0;
	speed = 0;

	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int textureID = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	mat3 = new Material();
	unsigned int tileID = mat3->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	tile = new Tilemap("level.csv", 800, 600, mat3, renderer);

	CollisionManager* instance = CollisionManager::Instance();

	/*sp1 = new Sprite(renderer, 8, 8);
	sp1->SetMaterial(mat2);
	sp1->LoadBMP("asteroid.bmp");
	sp1->SetPos(150.0f, 6.0f, 0.0f);
	sp1->SetBoundingBox(2.0f, 2.0f, 30.0f, false, false);
	instance->FillingBoxList(Player_layer, sp1);
	sp1->SetAnimation(0, 63, 0.1f);*/

	sp2 = new Sprite(renderer, 6, 8);
	sp2->SetMaterial(mat2);
	sp2->LoadBMP("character.bmp");
	sp2->SetPos(0.0f, 0.0f, 0.0f);
	sp2->SetBoundingBox(2.0f, 2.0f, 10.0f, false, false);
	instance->FillingBoxList(Enemy_layer, sp2);
	sp2->SetAnimation(0, 47, 0.1f);


	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	CollisionManager::Instance()->BoxCollisionDetector();

	tile->UpdateTilemap();
	//renderer->TranslateCamera(glm::vec3(speed * time, 0, 0));

	//sp1->UpdateAnim(time);
	sp2->UpdateAnim(time);

	speed = 1.0f;
	/* Movimiento vertical */
	//sp1->TranslationBox(0.0f, -speed * time, 0.0f);											// Movemos con translation asi no pisamos la posicion original
	//sp2->TranslationBox(0.0f, -speed * time, 0.0f);

	/* Movimineto horizontal */
	//sp1->TranslationBox(-speed * time, 0.0f, 0.0f);												// Movemos con translation asi no pisamos la posicion original
	//sp2->TranslationBox(speed * time, 0.0f, 0.0f);


	/*if (!tile->CollisionMath(sp2->GetBoundingBox(), Directions::Up))
		sp2->TranslationBox( 0.0f, speed * time, 0.0f);*/

	/*if (!tile->CollisionMath(sp2->GetBoundingBox(), Down)) 
		sp2->TranslationBox( 0.0f, -speed * time, 0.0f);*/
	
	/*if (!tile->CollisionMath(sp2->GetBoundingBox(), Directions::Left)) 
		sp2->TranslationBox(-speed * time, 0.0f, 0.0f);*/

	/*if (!tile->CollisionMath(sp2->GetBoundingBox(), Right))
		sp2->TranslationBox(speed * time, 0.0f, 0.0f);*/

	return true;
}

void Game::OnDraw() {
	tile->DrawTilemap();

	//sp1->Draw();
	sp2->Draw();
}

bool Game::OnStop() {
	//delete sp1;
	delete sp2;
	delete mat1;
	delete mat2;
	delete tile;
	cout << "Game::OnStop()" << endl;
	return false;
}