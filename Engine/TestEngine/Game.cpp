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
	colliderTiles->push_back(19);
	colliderTiles->push_back(20);
	colliderTiles->push_back(21);
	colliderTiles->push_back(22);
	colliderTiles->push_back(23);
	colliderTiles->push_back(24);
	colliderTiles->push_back(25);
	colliderTiles->push_back(26);
	colliderTiles->push_back(27);
	colliderTiles->push_back(28);
	colliderTiles->push_back(29);
	colliderTiles->push_back(30);
	colliderTiles->push_back(31);
	colliderTiles->push_back(32);
	colliderTiles->push_back(33);
	colliderTiles->push_back(34);
	
	tile = new Tilemap(renderer, 40, 41, "mapv3.csv", 10.0f, 7.0f, 10.0f, 2.0f, colliderTiles);
	tile->SetMaterial(mat3);
	tile->LoadTexture("mapv3.bmp");

	InputManager::GetInstance()->SetWindow(window);

	CollisionManager* instance = CollisionManager::Instance();

	player1 = new Player(renderer, 3, 0.3f, 2.5f, 2.0f, -0.05f, -11.8f, 0, tile);
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
}

bool Game::OnStop() {
	delete mat1;
	delete mat2;
	delete tile;
	delete player1;
	cout << "Game::OnStop()" << endl;
	return false;
}