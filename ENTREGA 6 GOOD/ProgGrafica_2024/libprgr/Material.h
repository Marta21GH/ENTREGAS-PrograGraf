#pragma once
#include "common.h"

class Material {
public: 
	typedef struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} pixel_t;

	string fileName = "";
	std::vector<pixel_t> pixels;
	int width = 0;
	int height = 0;
	/*	Constantes de iluminación del material	*/
	float Ka, Kd, Ks;

	//datos opengl
	unsigned int textureID = -1;
	
	Material(string fileName, float Ka, float Kd, float Ks);

	void bind();
};