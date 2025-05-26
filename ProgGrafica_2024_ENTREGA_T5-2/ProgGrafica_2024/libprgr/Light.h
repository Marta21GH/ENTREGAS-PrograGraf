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
	Light(Vector4f pos, Vector4f color, float Ia, float Id, float Is, LightType type) : 
		pos(pos), color(color), Ia(Ia), Id(Id), Is(Is), type(type) {};

	/*	Método que actualiza la posición de la luz en función de un algoritmo de
		movimiento (por el momento, vacío)	*/
	virtual void move(double timeStep) {}
};

class OrbitalLight : public Light {
public:
	Vector4f orbitPoint = { 0,0,0,1 };
	float orbitRadius = 1.0f;

	OrbitalLight(Vector4f pos, Vector4f color, float Ia, float Id, float Is, LightType type, Vector4f orbitPoint, float orbitRadius) :
		Light(pos, color, Ia, Id, Is, type), orbitPoint(orbitPoint), orbitRadius(orbitRadius) {};

	void move(double timeStep);
};