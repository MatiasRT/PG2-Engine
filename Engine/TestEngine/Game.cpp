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


	vector<int> * colliderTiles = new vector<int>();
	colliderTiles->push_back(3);
	colliderTiles->push_back(4);
	colliderTiles->push_back(5);
	colliderTiles->push_back(6);
	colliderTiles->push_back(10);
	colliderTiles->push_back(13);
	colliderTiles->push_back(14);
	colliderTiles->push_back(15);
	colliderTiles->push_back(16);
	colliderTiles->push_back(17);

	tile = new Tilemap(renderer, 40, 40, "TileMapFinal.csv", 10.0f, 7.0f, 10.0f, 2.0f, colliderTiles);
	tile->SetMaterial(mat3);
	tile->LoadTexture("TileMap.bmp");

	InputManager::GetInstance()->SetWindow(window);

	CollisionManager* instance = CollisionManager::Instance();

	player1 = new Player(renderer, 9, PLAYER_SPEED, 1.6f, 1.0f, 0, 0, 0, tile);
	//player1->SetCollisionEntity(player);


	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	CollisionManager::Instance()->BoxCollisionDetector();
	speed = 1.0f;


	player1->Update();

	renderer->CameraFollow(player1->GetSprite()->GetTranslation());
	//CollisionManager::Instance()->CollisionDetector();

	/*for (size_t i = 0; i < bones->size(); i++)
	{
		if (bones->at(i)->CheckCollision(player1->GetSprite()->GetTranslationX(), player1->GetSprite()->GetTranslationY(), player1->GetHeight(), player1->GetWidht()))
		{
			bones->at(i)->~CollectableItem();
			bones->erase(bones->begin() + i);
			break;
		}
	}*/


	return true;
}

void Game::OnDraw() {
	tile->Draw();
	player1->Draw();
	
	/*sp1->Draw();
	sp2->Draw();
	sp3->Draw();
	sp4->Draw();
	sp5->Draw();
	sp6->Draw();
	sp7->Draw();*/
}

bool Game::OnStop() {
	delete mat1;
	delete mat2;
	delete tile;
	delete player1;
	cout << "Game::OnStop()" << endl;
	return false;
}