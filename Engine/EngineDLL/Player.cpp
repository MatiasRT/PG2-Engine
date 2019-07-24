#include "Player.h"

Player::Player(Renderer * _renderer, float _animation, float _speed, float _height, float _widht, float _positionX, float _positionY, float _positionZ, Tilemap * _tilemapToCollide) {
	playerSprite = new Sprite(_renderer, _animation, "F1Down.bmp");
	playerMaterial = new Material();
	playerMaterial->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	playerSprite->SetMaterial(playerMaterial);
	playerSprite->SetScale(2.0f, 2.0f, 0.0f);

	playerSprite->SetCollider(glm::vec3(0, 0, 0), 1, 1, player, false);
	playerSprite->SetTranslation(_positionX, _positionY, _positionZ);
	speed = _speed;
	height = _height;
	widht = _widht;
	tilemapToCollide = _tilemapToCollide;

	animationRightBuffer = playerSprite->LoadTexture("F1Right.bmp");
	animationLeftBuffer = playerSprite->LoadTexture("F1Left.bmp");
	animationUpBuffer = playerSprite->LoadTexture("F1Up.bmp");
	animationDownBuffer = playerSprite->LoadTexture("F1Down.bmp");

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
		
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() + speed);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationX(playerSprite->GetTranslationX() - speed);
		}
		playerSprite->UpdateAnim();
	}
	else if (InputManager::GetInstance()->GetKeyDown(LeftKey)) {
		playerSprite->SetTextureBufferId(animationLeftBuffer);
		
		playerSprite->SetTranslationX(playerSprite->GetTranslationX() - speed);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationX(playerSprite->GetTranslationX() + speed);
		}
		playerSprite->UpdateAnim();
	}
	else if (InputManager::GetInstance()->GetKeyDown(UpKey)) {
		playerSprite->SetTextureBufferId(animationUpBuffer);
		
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() + speed);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationY(playerSprite->GetTranslationY() - speed);
		}
		playerSprite->UpdateAnim();
	}
	else if (InputManager::GetInstance()->GetKeyDown(DownKey)) {
		playerSprite->SetTextureBufferId(animationDownBuffer);
		
		playerSprite->SetTranslationY(playerSprite->GetTranslationY() - speed);

		if (tilemapToCollide->NextTileIsCollider(playerSprite->GetTranslationX(), playerSprite->GetTranslationY(), height, widht)) {
			playerSprite->SetTranslationY(playerSprite->GetTranslationY() + speed);
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

