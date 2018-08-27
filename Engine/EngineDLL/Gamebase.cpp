#include "Gamebase.h"

Gamebase::Gamebase(){
	
}
Gamebase::~Gamebase(){
}
bool Gamebase::Start() {
	cout << "Gamebase::Start()" << endl;

	window = new Window();
	if (!window->Start(800,600, " "))
		return false;

	render = new Renderer();
	if (!render->Start())
		return false;
	return OnStart();
}
void Gamebase::Loop() {
	bool loop = true;
	while (loop && !window->ShouldClose()) {
		loop = OnUpdate();



		window->PollEvents();
	}
}
bool Gamebase::Stop() {
	cout << "Gamebase::Stop()" << endl;
	OnStop();
	render->Stop();
	window->Stop();

	delete render;
	delete window;
	return true;
}