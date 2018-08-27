#include "Gamebase.h"

Gamebase::Gamebase(){
	
}
Gamebase::~Gamebase(){
}
bool Gamebase::Start() {
	cout << "Gamebase::Start()" << endl;
	render = new Renderer();
	if (!render->Start())
		return false;
	return OnStart();
}
void Gamebase::Loop() {
	bool loop = true;
	while(loop) {
		loop = OnUpdate();
	}
}
bool Gamebase::Stop() {
	cout << "Gamebase::Stop()" << endl;
	OnStop();
	render->Stop();
	delete render;
	return true;
}