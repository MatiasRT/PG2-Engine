#include "Game.h"
Game::Game()
{
	i = 0;
}
Game::~Game()
{
}
bool Game::OnStart() {
	cout << "Game::OnStart()" << endl;
	return true;
}
bool Game::OnStop() {
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate() {
	i++;
	cout << "Game::OnUpdate(): " <<i<< endl;
	//if (i > 5)
		//return false;
	return true;
}