#include "Player.h"

Player::Player(Renderer * _renderer, float _animation, float _speed, float _height, float _widht, float _positionX, float _positionY, float _positionZ, Tilemap * _tilemapToCollide) {
	playerSprite = new Sprite(_renderer, _animation, "SpriteSheetDown.bmp");
	playerMaterial = new Material();
	playerMaterial->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	playerSprite->SetMaterial(playerMaterial);

	playerSprite->SetCollider(glm::vec3(0, 0, 0), 1, 1, player, false);
	playerSprite->SetTranslation(_positionX, _positionY, _positionZ);
	speed = _speed;
	height = _height;
	widht = _widht;
	tilemapToCollide = _tilemapToCollide;

	animationRightBuffer = playerSprite->LoadTexture("SpriteSheetRight.bmp");
	animationLeftBuffer = playerSprite->LoadTexture("SpriteSheetLeft.bmp");
	animationUpBuffer = playerSprite->LoadTexture("SpriteSheetUp.bmp");
	animationDownBuffer = playerSprite->LoadTexture("SpriteSheetDown.bmp");

	playerSprite->SetTextureBufferId(animationDownBuffer);
	firstDraw = false;
	//playerSprite->SetPos(40, 1, 0);
}

void Player::SetCollisionEntity(Layers _layer) {
	//CollisionManager::Instance()->AddCollisionEntity(playerSprite, _layer);
}

Player::~Player() {
	delete playerSprite;
	delete playerMaterial;
}

void Player::Update() {
	if (!firstDraw) {
		playerSprite->UpdateAnim();
		firstDraw = true;
	}
	Movement();
}

void Player::Movement() {

	if (InputManager::GetInstance()->GetKeyDown(RightKey)) {
		playerSprite->SetTextureBufferId(animationRightBuffer);
		//playerSprite->SetTranslationX(playerSprite->GetTranslationX() + (Time::dt * speed));	// ORIGINAL
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() + 0.1f);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationX(playerSprite->GetTranslationX() - 0.1f);
		}
		playerSprite->UpdateAnim();
	}
	else if (InputManager::GetInstance()->GetKeyDown(LeftKey)) {
		playerSprite->SetTextureBufferId(animationLeftBuffer);
		//playerSprite->SetTranslationX(playerSprite->GetTranslationX() - (Time::dt * speed));	// ORIGINAL
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() - 0.1f);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationX(playerSprite->GetTranslationX() + 0.1f);
		}
		playerSprite->UpdateAnim();
	}
	else if (InputManager::GetInstance()->GetKeyDown(UpKey)) {
		playerSprite->SetTextureBufferId(animationUpBuffer);
		//playerSprite->SetTranslationY(playerSprite->GetTranslationY() + (Time::dt * speed));	// ORIGINAL
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() + 0.1f);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationY(playerSprite->GetTranslationY() - 0.1f);
		}
		playerSprite->UpdateAnim();
	}
	else if (InputManager::GetInstance()->GetKeyDown(DownKey)) {
		playerSprite->SetTextureBufferId(animationDownBuffer);
		//playerSprite->SetTranslationY(playerSprite->GetTranslationY() - (Time::dt * speed));	// ORIGINAL
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() - 0.1f);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationY(playerSprite->GetTranslationY() + 0.1f);
		}
		playerSprite->UpdateAnim();
	}
}

void Player::Draw() {
	playerSprite->Draw();
}

Sprite* Player::GetSprite() {
	return playerSprite;
}

float Player::GetHeight() {
	return height;
}
float Player::GetWidht() {
	return widht;
}

