#pragma once
#include "vectorMath.h"
#include "vertex.h"
#include "InputManager.h"
using namespace libPRGR;

class Object3D {
public: 
	inline static int idCounter = 0;

	// Id asociado al objeto
	int id;

	Vector4f position;
	Vector4f rotation;
	Vector4f scale;
	Matrix4x4f modelMatrix;

	// Lista de vértices del objeto
	std::vector<Vertex> vertexList;
	// Lista con los índices que se usarán para dibujar la lista de vértices
	std::vector<int> idList;

	/*
		Método que inicializa la lista de vértices con 3 vértices formando un triángulo cuyo
		centro se encontrará en el origen de coordenadas(0, 0, 0)
	*/
	void createTriangle();
	
	/*
		Método virtual (podrá ser reescrito por clases herederas) que actualiza la
		posición / rotación / escalado del objeto.Deberá consultar el estado del teclado, y si se
		pulsa la tecla “D” aumentará el ángulo de giro en el eje Y.
		o Si se pulsa la tecla “A” disminuirá el ángulo de giro en el eje Y
	*/
	virtual void move(double timeStep) {
		//GLFWTimer ?????
		if (InputManager::keyState[GLFW_KEY_A]) {
			this->rotation.y -= 0.001f;
		}

		if (InputManager::keyState[GLFW_KEY_D]) {
			this->rotation.y += 0.001f;
		}
	}
	
	/*
		Método que actualiza la matriz modelo en base a los datos de posición, rotación y
		escalado de este objeto
	*/
	void updateModelMatrix();
};