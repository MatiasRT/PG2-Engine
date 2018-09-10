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

	renderer = new Renderer();
	if (!renderer->Start(window))
		return false;
	renderer->ClearColor(0.0f, 0.0f, 4.0f, 0.0f);
	return OnStart();
}
void Gamebase::Loop() {
	bool loop = true;
	while (loop && !window->ShouldClose()) {
		loop = OnUpdate();

		renderer->ClearScreen();
		OnDraw();
		renderer->SwapBuffers();


		window->PollEvents();
	}
}
bool Gamebase::Stop() {
	cout << "Gamebase::Stop()" << endl;
	OnStop();
	renderer->Stop();
	window->Stop();

	delete renderer;
	delete window;
	return true;
}