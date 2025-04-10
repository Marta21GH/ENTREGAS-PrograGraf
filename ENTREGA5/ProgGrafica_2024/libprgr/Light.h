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
	Vector4f direction = { 0,0,0,0 }, position = { 0,0,3,1 }, color = { 1,1,1,1 };
	/*	Constantes de iluminación ambiental, difusa y especular, respectivamente	*/
	float ia, id, is;
	/*	Tipo de luz que se usará :
		▪ Direccional o punto de luz	*/
	LightType type;
	
	/*	Constructor de objeto de tipo luz, que recibe por parámetros los valores de sus
		atributos	*/
	Light(Vector4f direction = { 0,0,0,0 }, Vector4f position = { 0,0,3,1 }, Vector4f color = { 1,1,1,1 }, 
		float ia = 1.0f, float id = 1.0f, float is = 1.0f, LightType type = POINT) :
		direction(direction), position(position), color(color), ia(ia), id(id), is(is), type(type) {};
	
	/*	Método que actualiza la posición de la luz en función de un algoritmo de
		movimiento (por el momento, vacío)	*/
	void move(double timeStep);
};