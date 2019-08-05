#include "InputManager.h"
#include <GLFW\glfw3.h>

InputManager* InputManager::instance = 0;

InputManager* InputManager::Instance() {
	if (instance == 0) {
		instance = new InputManager();
	}
	return instance;
}

void InputManager::SetWindow(Window* w) {
	window = w;
}

bool InputManager::GetKeyDown(Key key) {
	return (glfwGetKey((GLFWwindow*)window->GetWindow(), key) == GLFW_PRESS);
}