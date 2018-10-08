#include <Gamebase.h>
#include <Triangle.h>
#include <Material.h>
#include <Rectangle.h>
#include <Circle.h>
#include <Importer.h>
#include <iostream>
class Game : public Gamebase {
	int i;
	float rotation;
	float translation;
	float speed;
	Triangle * tr1;
	Rectangle * rt1;
	Circle * cr1;
	Material * mat1;
public:
	Game() { i = 0; };
	~Game() { };
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};