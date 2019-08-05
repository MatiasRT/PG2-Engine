#pragma once
#include "Exports.h"
#include "Window.h"

enum Key {
	RightKey = 262,
	LeftKey = 263,
	DownKey = 264,
	UpKey = 265,
	Space = 32,
	Escape = 256

};

class ENGINEDLL_API InputManager {

	static InputManager* instance;
	Window* window;

	InputManager() {};
	~InputManager() {};
public:
	static InputManager* Instance();

	void SetWindow(Window* w);
	bool GetKeyDown(Key key);
};