#pragma once
#include "Object3D.h"
#include "Camera.h"

class Render {
public:
	typedef struct {
		unsigned int idArray;		//Identificador de grupos de arrays
		unsigned int idVertexArray;	//Identificador de datos de vertices
		unsigned int idIndexArray;	//Identificador de orden de vertices
	}bufferObject;

	map<int, bufferObject> bufferObjectList;
	list<Object*> objectList;
	GLFWwindow* window = nullptr;

	Camera* cam = nullptr;

	Render();

	GLFWwindow* initGLFW();

	void deinitGLFW();

	void setUpObject(Object* obj);

	void drawGL(Object* obj);
};