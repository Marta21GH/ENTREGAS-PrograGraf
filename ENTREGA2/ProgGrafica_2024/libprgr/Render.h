#pragma once
#include "vectorMath.h"
#include "Object3D.h"
#include "bufferObject.h"
using namespace libPRGR;

class Render {
public: 
	int height;
	int width;

	// Atributo que almacena una referencia a la ventana de opengl que usaremos para dibujar
	GLFWwindow* window;
	
	// Lista de objetos que se dibujaran en la ventana de openGl
	std::vector<Object3D*> objectList;

	// Lista de identificadores de buffer
	std::map<int, bufferObject> bufferObjects;

	Render(int h, int w) {
		height = h;
		width = w;
	}
	
	/* 
		La clase render recibia en su constructor el tamano del frameBuffer(coincide con la
		resolucion de la pantalla o tamano de la ventana).Este metodo se usara para crear una
		ventana de openGL con esos datos, e inicializar el sistema de renderizado.
		o Tambien llamara al metodo “initInputManager” de la clase InputManager para poder
		inicializar los eventos de teclado con la ventana creada anteriormente.
	*/
	void initGL();
	
	/* 
		Metodo que anade un objeto a la lista de objetos.Debe crear su bufferObject y
		almacenar en el mapa bufferObjets los identificadores de buffers creados / cargados en
		GPU
	*/
	void putObject(Object3D* obj);
	
	/*
		Metodo que elimina un objeto a la lista de objetos.Debe destruir su bufferObject y
		buffers creados / cargados en GPU.
	*/
	void removeObject(Object3D * obj);

	/*
		Metodo que dibuja los objetos en la ventana de openGL.Este metodo recorre la lista de
		objetos, y por cada uno de ellos los carga en GPU y dibuja sus datos de vertices
	*/
	void drawGL();

	/*
		Metodo que se mantiene en un bucle mientras este abierta la ventana de OpenGL.
		El bucle seguira el patron visto en clase :
			- Limpiar frameBuffer
			- Actualizar los eventos de ventana
			- Actualizar el estado de los objetos llamando a su metodo “move”
			- Dibujar esos objetos en pantalla
			- Intercambiar buffers de imagen
	*/
	void mainLoop();
};