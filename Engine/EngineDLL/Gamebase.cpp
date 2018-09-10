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
	if (!render->Start(window))
		return false;
	render->ClearColor(0.0f, 0.0f, 4.0f, 0.0f);
	return OnStart();
}
void Gamebase::Loop() {
	bool loop = true;
	while (loop && !window->ShouldClose()) {
		loop = OnUpdate();

		render->ClearScreen();
		render->SwapBuffers();


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