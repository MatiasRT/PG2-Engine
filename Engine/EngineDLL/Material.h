#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Exports.h"
class ENGINEDLL_API Material {
protected:
	unsigned int ProgramID;
	unsigned int MatrixID;
	unsigned int TextureID;
public:
	void Bind();
	void Bind(const char * texName, unsigned int texture);
	
	void BindTexture();

	unsigned int LoadShaders(const char* vertexFile, const char* fragmentFile);

	void SetMatrixProperty(glm::mat4& mat);
};