#include "InputManager.h"
#include <GLFW\glfw3.h>

InputManager* InputManager::instance = 0;

InputManager* InputManager::GetInstance() {
	if (instance == 0) {
		instance = new InputManager();
	}
	return instance;
}


void InputManager::SetWindow(Window* _window) {
	window = _window;
}

bool InputManager::GetKeyDown(Key _key) {
	return (glfwGetKey((GLFWwindow*)window->GetWindow(), _key) == GLFW_PRESS);
}


InputManager::InputManager() {

}

InputManager::~InputManager() {

}
