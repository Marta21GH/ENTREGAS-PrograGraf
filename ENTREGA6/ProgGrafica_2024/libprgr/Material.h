#pragma once
#include "vectorMath.h"
#include "common.h"

class Material {
public:
	typedef struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} pixel_t;

	/*	Array de pixeles que se usará para pasar la textura a GPU	*/
	std::vector<pixel_t> pixels;

	/*	Nombre del fichero de textura que se usará para colorear el objeto	*/
	std::string textureName;
	/*	Identificador de la textura cargada en OpenGL	*/
	unsigned int textureId = -1;
	/*	Tamaños en píxeles de la textura cargada	*/
	int width, height;
	/*	Constantes de iluminación del material	*/
	float Ka, Kd, Ks;
	
	/*	Constructor de la clase, a partir de un nombre de fichero de textura y sus constantes
		de iluminación.Una vez invocado, cargará los datos de textura del fichero que
		recibe por parámetros, usando los métodos de opengl vistos en clase.	*/
	Material(std::string textureName, float Ka, float Kd, float Ks);

	/*	Método que inicializa una unidad de texturado usando como índice el número que
		se le pasa por parámetros	*/
	void bind(int textureUnit);
};