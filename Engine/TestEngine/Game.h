#include <Gamebase.h>
#include <CollisionManager.h>
#include <Triangle.h>
#include <Material.h>
#include <Rectangle.h>
#include <Circle.h>
#include <Importer.h>
#include <Sprite.h>
#include <Tilemap.h>
#include <Player.h>
#include <Collectable.h>
#include <iostream>

class Game : public Gamebase {
	int i;
	int f;
	float rotation;
	float translation;
	float speed;
	
	Material * mat1;
	Material * mat2;
	Material * mat3;

	Player * player1;

	Tilemap * tile;

	vector<Collectable*> * flags;
public:
	Game() { i = 0; };
	~Game() { };
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};