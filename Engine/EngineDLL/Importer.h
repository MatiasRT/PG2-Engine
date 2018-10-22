#pragma once
#include "Exports.h"
#include <fstream>
struct Header {
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
};
static class ENGINEDLL_API Importer {
public:
	unsigned char LoadBMP(const char * name);
	bool CheckFormat(const char * name, unsigned char header[], FILE * file);
};