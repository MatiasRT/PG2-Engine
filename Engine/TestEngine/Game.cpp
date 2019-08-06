#include "Game.h"

bool Game::OnStart() {
	i = 0;
	translation = 0;
	rotation = 0;
	speed = 0.3f;
	f = 22;

	mat1 = new Material();																		// Creo un Material
	unsigned int programID = mat1->LoadShaders("VertexColor.glsl", "FragmentColor.glsl");		// Le digo al Material cuales van a ser los shaders que tiene que utilizar. El VS se ejecuta una vez x cada pixel, y el FS se ejecuta una vez x muestra

	mat2 = new Material();
	unsigned int textureID = mat2->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");

	mat3 = new Material();
	unsigned int tileID = mat3->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");


	vector<int> * colliderTiles = new vector<int>();											// Vector con los tiles con los que colisiona el jugador 
	for (int i = 19; i < 35; i++) 
		colliderTiles->push_back(i);

	vector<int> * modColliderTiles = new vector<int>();
	//for (int i = 43; i < 50; i++)
		//modColliderTiles->push_back(i);

	flags = new vector<Collectable*>();
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", -0.05f, -17.5f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 0.55f, -24.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 10.0f, -24.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 20.0f, -24.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 26.05f, -31.6f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 23.05f, -40.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 21.55f, 40.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 9.55f, 40.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 3.25f, 40.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", -3.65f, 40.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", -3.95f, -46.6f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", -3.95f, 59.8f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", -4.25f, 58.29f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 2.05f, -66.0999f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 20.35f, -66.0999f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 49.4499f, -66.0999f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 58.14f, -49.89f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 58.14f, -22.6f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 52.7499f, -13.9f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 35.95f, -13.9f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 22.15f, -9.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 35.95f, -4.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 52.7499f, -4.0f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 62.0499f, 0.2f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 52.7499f, 4.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 35.95f, 4.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", 14.35f, 4.1f, 0.0f, 0.5f, 0.5f));
	flags->push_back(new Collectable(renderer, "raceFlag.bmp", -0.05f, 3.8f, 0.0f, 0.5f, 0.5f));
	

	object = new vector<Object*>();

	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, -2.75f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, -0.75f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 1.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 3.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 5.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 7.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 9.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 11.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 13.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 15.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 17.25f, -29.0f, 0.0f, 4.0f, 4.0f, tile));

	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, -2.75f, -31.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, -2.75f, -33.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, -2.75f, -35.0f, 0.0f, 4.0f, 4.0f, tile));

	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, -0.75f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 1.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 3.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 5.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 7.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 9.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 11.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 13.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 15.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 17.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));


	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 17.25f, -31.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 17.25f, -33.0f, 0.0f, 4.0f, 4.0f, tile));
	object->push_back(new Object(renderer, "Tires.bmp", 1.0f, 17.25f, -35.0f, 0.0f, 4.0f, 4.0f, tile));

	for (int i = 0; i < object->size(); i++) {
		object->at(i)->SetCollider(0.0f, 0.0f, 0.0f, 4.0f, 4.0f, not_walkeable, true);
		CollisionManager::Instance()->AddCollisionEntity(object->at(i)->GetSprite(), not_walkeable);
	}


	object2 = new vector<Object*>();

	object2->push_back(new Object(renderer, "Tires.bmp", 1.0f, 19.25f, -32.0f, 0.0f, 4.0f, 4.0f, tile));
	for (int i = 0; i < object2->size(); i++) {
		object2->at(i)->SetCollider(0.0f, 0.0f, 0.0f, 4.0f, 4.0f, not_walkeable, false);
		CollisionManager::Instance()->AddCollisionEntity(object2->at(i)->GetSprite(), not_walkeable);
	}
	
	tile = new Tilemap(renderer, 40, 41, "mapv3.csv", 10.0f, 7.0f, 10.0f, 2.0f, colliderTiles, modColliderTiles);
	tile->SetMaterial(mat3);
	tile->LoadTexture("mapv3.bmp");

	InputManager::Instance()->SetWindow(window);

	//CollisionManager* instance = CollisionManager::Instance();

	player1 = new Player(renderer, 3, speed, 2.5f, 2.0f, -0.05f, -11.8f, 0, tile);
	player1->SetCollisionEntity(player);


	cout<<"Game::OnStart()"<<endl;
	return true;
}

bool Game::OnUpdate() {																			// Toda la logica va aca
	//CollisionManager::Instance()->BoxCollisionDetector();
	speed += time * 0.3f;


	player1->Update();

	renderer->CameraFollow(player1->GetSprite()->GetPos());
	CollisionManager::Instance()->CollisionDetector();
	
	for (int i = 0; i < object->size(); i++) {
		object->at(i)->Update();
	}

	for (int i = 0; i < object2->size(); i++) {
		object2->at(i)->Update();
		//object2->at(i)->CheckCollision(0.3f);
	}

	for (int i = 0; i < flags->size(); i++) {
		if (flags->at(i)->CheckCollision(player1->GetSprite()->GetTranslationX(), player1->GetSprite()->GetTranslationY(), player1->GetHeight(), player1->GetWidht())) {

			flags->erase(flags->begin() + i);
			f = f - 1;
			//cout << "Hola" << endl;
			break;
		}
		if (f == 0) {
			flags->push_back(new Collectable(renderer, "raceFlag.bmp", -0.05f, -15.1f, 0.0f, 0.5f, 0.5f));
			//cout << "Hola" << endl;
			f = f - 1;
			break;
		}

		// F = -2 WIN
	}

	if (f == -2) {
		cout << "WIN!" << endl;
	}

	//cout << f << endl;
	return true;
}

void Game::OnDraw() {
	tile->Draw();
	player1->Draw();

	for (int i = 0; i < flags->size(); i++)
		flags->at(i)->Draw();

	for (int i = 0; i < object->size(); i++)
		object->at(i)->Draw();

	for (int i = 0; i < object2->size(); i++)
		object2->at(i)->Draw();
}

bool Game::OnStop() {
	delete mat1;
	delete mat2;
	delete tile;
	delete player1;
	delete flags;
	delete object;
	delete object2;
	cout << "Game::OnStop()" << endl;
	return false;
}