#pragma once
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "Exports.h"
class ENGINEDLL_API Material
{
private:
	unsigned int ProgramID;
	unsigned int matrixID;

	Material(unsigned int programID);
	static bool LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
public:
	~Material();
	void Bind();//unsigned int programId);

	static Material* LoadMaterial(const char* vtxShaderPath, const char* frgShaderPath);

	void SetMatrixProperty(const char* name, glm::mat4& mat);

	//unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	//void SetMatrixProperty(const char* name, glm::mat4& mat)
};

