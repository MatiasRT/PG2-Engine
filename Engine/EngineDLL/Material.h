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
	//unsigned int programId);
	void BindTexture();
	void BindTexture(const char * name, unsigned int textureBufferId);
	unsigned int LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	void SetMatrixProperty(glm::mat4& mat);
};