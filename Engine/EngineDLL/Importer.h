#pragma once
#include "Exports.h"
#include <fstream>
static class ENGINEDLL_API Importer {
	struct Header {
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
	};
public:
	unsigned char LoadBMP(const char * name);
	bool CheckFormat(const char * name, unsigned char header[], FILE * file);
};