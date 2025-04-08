#pragma once
#include "Object3D.h"
#include "Camera.h"
#include "Light.h"

class Render {
public:
	typedef struct {
		unsigned int idArray;		//Identificador de grupos de arrays
		unsigned int idVertexArray;	//Identificador de datos de vertices
		unsigned int idIndexArray;	//Identificador de orden de vertices
	}bufferObject;

	map<int, bufferObject> bufferList;
	list<Object*> objectList;
	GLFWwindow* window = nullptr;

	Camera* cam = nullptr;
	Light* light = nullptr;

	Render();

	void initGLFW();

	void deinitGLFW();

	void putObject(Object* obj);

	void setUpObject(Object* obj);

	void drawGL(Object* obj);

	void putCamera(Camera* camj);

	void putLight(Light* light);

	void mainLoop();
};