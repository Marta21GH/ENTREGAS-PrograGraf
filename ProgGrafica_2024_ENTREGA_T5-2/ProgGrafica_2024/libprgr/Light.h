#pragma once
#include "vectorMath.h"
using namespace libPRGR;

typedef enum {
	DIRECTIONAL = 0,
	POINT = 1
} LightType;

class Light {
public:
	Vector4f dir = { 0,0,0,1 };
	Vector4f pos = { 0,0,3,1 };
	Vector4f color = { 1,1,1,1 };
	//float I = 1.0f;
	/*	Constantes de iluminación ambiental, difusa y especular, respectivamente	*/
	float Ia = 0.5f;
	float Id = 1.0f;
	float Is = 2.0f;
	LightType type = DIRECTIONAL;
	Light(Vector4f pos, Vector4f color, /*float I,*/ float Ia, float Id, float Is, LightType type) : 
		pos(pos), color(color), /*I(I),*/ Ia(Ia), Id(Id), Is(Is), type(type) {};
};

/*	Método que actualiza la posición de la luz en función de un algoritmo de
	movimiento (por el momento, vacío)	*/
void move(double timeStep);