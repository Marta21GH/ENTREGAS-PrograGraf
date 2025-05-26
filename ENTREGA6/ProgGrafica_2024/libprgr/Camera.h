#pragma once
#include "vectorMath.h"
#include "Collider.h"
#include "Sphere.h"
using namespace libPRGR;

class Camera {
public:
	Vector4f pos = { 0,0,0,1 };
	Vector4f up = { 0,1,0,0 };	//Verticalidad cámara
	Vector4f lookAt = { 0,0,0,1 }; //Punto al que miras
	Vector4f rot = { 0,0,0,0 };

	float fovy = 90;
	float aspectRatio = 640.0f / 480.0f;
	float zNear = 0.01f;
	float zFar = 100.0f;

	Collider* coll = nullptr; // 🟢 Colisionador de la cámara

	Camera(Vector4f pos, Vector4f rot, Vector4f lookAt, Vector4f up, float fovy, float aspectRatio, float zNear, float zFar)
		: pos(pos), rot(rot), lookAt(lookAt), up(up), fovy(fovy), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar) {
	}

	Matrix4x4f lookat();
	Matrix4x4f projection();
	void move(double timestep);

	void setCollider(); // 🟢 Inicializa su colisionador
};
