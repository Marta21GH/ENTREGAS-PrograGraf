#pragma once
#include "vectorMath.h"
using namespace libPRGR;

class Camera {
public:
	Vector4f pos = { 0,0,0,1 };
	Vector4f up = { 0,1,0,0 };	//Verticalidad cámara
	Vector4f lookAt = { 0,0,0,1 }; //Punto al que miras
	Vector4f rot = { 0,0,0,0 };	

	float fovy = 90;
	float aspectRatio = 640.0f / 480.0f; //Tamaño ventana hardcodeado (arreglar (evento redimensionado, avisar camara que aspecto ha cambiado, cambiar avriables ancho/alto) 
	float zNear = 0.01f; //Plano cercano
	float zFar = 100.0f; //Plano lejano

	Camera(Vector4f pos, Vector4f rot, Vector4f lookAt, Vector4f up, float fovy, float aspectRatio, float zNear, float zFar)
		: pos(pos), rot(rot), lookAt(lookAt), up(up), fovy(fovy), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar) {}

	Matrix4x4f lookat();
	Matrix4x4f projection();
	void move(double timestep);
};