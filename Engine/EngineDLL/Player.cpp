#include "Player.h"

Player::Player(Renderer * renderer, float anim, float spd, float h, float w, float posX, float posY, float posZ, Tilemap * tilemap) {
	sprite = new Sprite(renderer, anim, "F1Down.bmp");
	material = new Material();
	material->LoadShaders("VertexTexture.glsl", "FragmentTexture.glsl");
	sprite->SetMaterial(material);
	sprite->SetScale(2.0f, 2.0f, 0.0f);

	sprite->SetCollider(glm::vec3(0, 0, 0), 1, 1, player, false);
	sprite->SetTranslation(posX, posY, posZ);
	speed = spd;
	height = h;
	widht = w;
	tilemapToCollide = tilemap;

	animRightBuffer = sprite->LoadTexture("F1Right.bmp");
	animLeftBuffer = sprite->LoadTexture("F1Left.bmp");
	animUpBuffer = sprite->LoadTexture("F1Up.bmp");
	animDownBuffer = sprite->LoadTexture("F1Down.bmp");

	sprite->SetTextureBufferId(animDownBuffer);
	firstDraw = false;

}

void Player::SetCollisionEntity(Layers layer) {
	CollisionManager::Instance()->AddCollisionEntity(sprite, layer);
}

Player::~Player() {
	delete sprite;
	delete material;
}

void Player::Update() {
	if (!firstDraw) {
		sprite->UpdateAnim();
		firstDraw = true;
	}
	Movement();
	/*cout << "X:" << playerSprite->GetPos().x << endl;
	cout<<"Y:"<<playerSprite->GetPos().y<<endl;*/
}

void Player::Movement() {

	if (InputManager::Instance()->GetKeyDown(RightKey)) {
		sprite->SetTextureBufferId(animRightBuffer);
		
		sprite->SetTranslationX(sprite->GetTranslationX() + speed);

		if (tilemapToCollide->CheckCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht))
			sprite->SetTranslationX(sprite->GetTranslationX() - speed);
		
		if (tilemapToCollide->CheckModCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht)) {
			sprite->SetTranslationX(sprite->GetTranslationX() + 0.1);
			cout << "Right: " << speed << endl;
		}

		sprite->UpdateAnim();
	}
	else if (InputManager::Instance()->GetKeyDown(LeftKey)) {
		sprite->SetTextureBufferId(animLeftBuffer);
		
		sprite->SetTranslationX(sprite->GetTranslationX() - speed);

		if (tilemapToCollide->CheckCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht))
			sprite->SetTranslationX(sprite->GetTranslationX() + speed);
		
		if (tilemapToCollide->CheckModCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht)) {
			sprite->SetTranslationX(sprite->GetTranslationX() - 0.1);
			cout << "Left: " << speed << endl;
		}

		sprite->UpdateAnim();
	}
	else if (InputManager::Instance()->GetKeyDown(UpKey)) {
		sprite->SetTextureBufferId(animUpBuffer);
		
		sprite->SetTranslationY(sprite->GetTranslationY() + speed);

		if (tilemapToCollide->CheckCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht))
			sprite->SetTranslationY(sprite->GetTranslationY() - speed);
		
		if (tilemapToCollide->CheckModCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht)) {
			sprite->SetTranslationY(sprite->GetTranslationY() + 0.1);
			cout << "Up: " << speed << endl;
		}

		sprite->UpdateAnim();
	}
	else if (InputManager::Instance()->GetKeyDown(DownKey)) {
		sprite->SetTextureBufferId(animDownBuffer);
		
		sprite->SetTranslationY(sprite->GetTranslationY() - speed);

		if (tilemapToCollide->CheckCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht))
			sprite->SetTranslationY(sprite->GetTranslationY() + speed);
		
		if (tilemapToCollide->CheckModCollission(sprite->GetTranslationX(), sprite->GetTranslationY(), height, widht)) {
			sprite->SetTranslationY(sprite->GetTranslationY() - 0.1);
			cout << "Down: " << speed << endl;
		}

		sprite->UpdateAnim();
	}
}

void Player::Draw() {
	sprite->Draw();
}