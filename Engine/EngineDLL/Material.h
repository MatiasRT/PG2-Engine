#pragma once
#include "../external/glm-0.9.9.0/glm/gtc/matrix_transform.hpp"
#include "../external/glm-0.9.9.0/glm/glm.hpp"
#include "Exports.h"
class ENGINEDLL_API Material
{
protected:
	unsigned int ProgramID;
	unsigned int MatrixID;
public:

	void Bind();//unsigned int programId);
	unsigned int LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	void SetMatrixProperty(glm::mat4& mat);
};