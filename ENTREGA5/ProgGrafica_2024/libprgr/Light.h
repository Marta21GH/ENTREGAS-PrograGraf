#pragma once
#include "vectorMath.h"
#include "common.h"
using namespace libPRGR;

typedef enum {
	DIRECTIONAL = 0,
	POINT = 1
} LightType;

class Light {
public:
	Vector4f direction, position, color;
	/*	Constantes de iluminación ambiental, difusa y especular, respectivamente	*/
	float ka, kd, ks;
	/*	Tipo de luz que se usará :
		▪ Direccional o punto de luz	*/
	LightType type;
	
	/*	Constructor de objeto de tipo luz, que recibe por parámetros los valores de sus
		atributos	*/
	Light(Vector4f direction = { 0,0,0,0 }, Vector4f position, Vector4f color, float ka, float kd, float ks, LightType type) : 
		direction(direction), position(position), color(color), ka(ka), kd(kd), ks(ks), type(type) {};
	
	/*	Método que actualiza la posición de la luz en función de un algoritmo de
		movimiento (por el momento, vacío)	*/
	void move(double timeStep);
};