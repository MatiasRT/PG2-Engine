#pragma once
#include "Exports.h"
#include "Window.h"
//class Window;

enum Key {
	RightKey = 262,
	LeftKey = 263,
	DownKey = 264,
	UpKey = 265,
	QKey = 81,
	WKey = 87,
	EKey = 69,
	AKey = 65,
	SKey = 83,
	DKey = 68,
	Space = 32,
	Escape = 256

};


class ENGINEDLL_API InputManager {

	static InputManager* instance;
	Window* window;

	InputManager();
	~InputManager();
public:
	static InputManager* GetInstance();

	void SetWindow(Window* _window);
	bool GetKeyDown(Key _key);
};