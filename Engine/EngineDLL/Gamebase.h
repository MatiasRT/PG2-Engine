#include "Exports.h"
#include "Renderer.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Gamebase {
private:
	Renderer* render;
public:
	Gamebase();
	~Gamebase();
	bool Start();
	bool Stop();
	void Loop();
protected:
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
};

