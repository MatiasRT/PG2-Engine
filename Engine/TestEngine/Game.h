#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Rectangle.h"
#include <iostream>
class Game : public Gamebase{
	int i;
	Triangle * tr1;
	Triangle * tr2;
	Rectangle * rt1;
	Material * mat1;
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};