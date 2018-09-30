#include <Gamebase.h>
#include <Triangle.h>
#include <Material.h>
#include <Rectangle.h>
#include <iostream>
class Game : public Gamebase{
	int i;
	float rotation;
	float translation;
	float speed;
	Triangle * tr1;
	Triangle * tr2;
	Rectangle * rt1;
	Material * mat1;
	Material * mat2;
public:
	Game() { i = 0; };
	~Game() { };
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};