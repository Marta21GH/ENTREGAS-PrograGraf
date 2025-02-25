#include "Object3D.h"
#include "EventManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace libPRGR;

Object::Object() {
	ObjectId = idCounter++;
	this->pos = { 0, 0, 0, 1 };
	this->vertexList.push_back({ { 0, 0.25, 0, 1 },{ 1,0,0,1 } });
	this->vertexList.push_back({ { -0.25, -0.25, 0, 1 },{ 1,0,1,1 } });
	this->vertexList.push_back({ { 0.25, -0.25, 0, 1 },{ 0,0,1,1 } });
	this->indexVertexList = { 0, 1, 2 };
}

Object::Object(const char* fileName) {
	ObjectId = idCounter++;
	this->pos = { 0, 0, 0, 1 };
	loadFromFile(fileName);
}

void Object::loadFromFile(const char* fileName)
{
	// Abrir fichero
	std::ifstream f(fileName);
	if (f.is_open()) {
		// leerVertices
		leerVertices(f);
		// leerColores
		leerColores(f);
		// leerCaras
		leerCaras(f);
	}
	else {
		cout << "ERROR: Fichero " << fileName << " no existe" << endl;
	}
}

void Object::leerVertices(std::ifstream& f)
{
	string linea="";
	// Mientras linea no "end"
	do {
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			// Separar en partes: identificador y posiciones
			std::stringstream l(linea);	//Crear stream
			string identificador;	//Crear dos variables string que contengan partes linea
			string posiciones;
			l >> identificador;		//Leer linea y almacenar palabras en variables
			l >> posiciones;
			std::vector<float> pos = splitString<float>(posiciones, ',');	//Separar posiciones segun comas ("1,2,3" -> "1" "2" "3")
			
			// asignar posiciones a nuevo vertice
			vertex_t v;
			v.vPos.x = pos[0];
			v.vPos.y = pos[1];
			v.vPos.z = pos[2];
			v.vPos.w = 1.0f;
			this->vertexList.push_back(v);
		}
	} while (linea != "end");	
}

void Object::leerColores(std::ifstream& f)
{
	string linea="";
	// Mientras linea no "end"
	do {
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			std::stringstream l(linea);
			string identificador;
			string colores;
			l >> identificador;
			l >> colores;
			std::vector<float> color = splitString<float>(colores, ',');

			//Sacar identificador
			int vertexId = splitString<int>(identificador, ':')[0];
			this->vertexList[vertexId - 1].vColor = { color[0], color[1], color[2], color[3] };
		}
	} while (linea != "end");	
}

void Object::leerCaras(std::ifstream& f)
{
	string linea="";
	// Mientras linea no "end"
	do {
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			std::stringstream l(linea);
			string identificador;
			string vertexIds;
			l >> identificador;
			l >> vertexIds;
			std::vector<int> vIds = splitString<int>(vertexIds, ',');

			//Sacar identificador
			this-> indexVertexList.push_back(vIds[0]-1);
			this-> indexVertexList.push_back(vIds[1]-1);
			this-> indexVertexList.push_back(vIds[2]-1);
		}
	} while (linea != "end");	
}

void Object::update() {
	if (EventManager::keyState[GLFW_KEY_LEFT]) {
		this->pos.x -= 0.001f;
	}

	if (EventManager::keyState[GLFW_KEY_RIGHT]) {
		this->pos.x += 0.001f;
	}

	float rotationSpeed = 0.001f;

	if (EventManager::keyState[GLFW_KEY_Q]) {
		this->rot.y -= rotationSpeed; //angulo de rotacion para el frame
	}

	if (EventManager::keyState[GLFW_KEY_E]) {
		this->rot.y += rotationSpeed;
	}
}

Matrix4x4f Object::computeModelMatrix() {
	Matrix4x4f model = make_identityf();
	model = make_translate(pos.x, pos.y, pos.z);
	model = model*make_rotation_xyz(rot.x, rot.y, rot.z);
	model = model*make_scale(size.x, size.y, size.z);
	return model;
}