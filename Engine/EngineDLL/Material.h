#pragma once
#include "Exports.h"
class ENGINEDLL_API Material
{
private:
	unsigned int ProgramID;
public:
	Material();
	~Material();
	void Bind();//unsigned int programId);
	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};

