#pragma once
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "Exports.h"
#include "Window.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Renderer
{
private:
	unsigned int VertexArrayID;
	Window* window;
	glm::mat4 WorldMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
public:
	Renderer();
	~Renderer();
	bool Start(Window* windowPtr);
	bool Stop();
	void ClearScreen();
	void ClearColor(float r, float g, float b, float a);
	void SwapBuffers();
	unsigned int GenBuffer(float* buffer, int size);
	void DrawBuffer(unsigned int vtxbuffer, int size);
	void DestroyBuffer(unsigned int buffer);
};

