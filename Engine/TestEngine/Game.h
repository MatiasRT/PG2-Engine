#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include <iostream>
class Game : public Gamebase{
	int i;
	Triangle * tr1;
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};