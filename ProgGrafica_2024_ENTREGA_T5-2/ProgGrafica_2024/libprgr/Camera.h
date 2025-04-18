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

	Camera(Vector4f pos, Vector4f up, Vector4f lookAt) : pos(pos), up(up), lookAt(lookAt) {}

	Matrix4x4f computeViewMatrix();
	Matrix4x4f computeProjectionMatrix();
	void update();
};