#include "Object3D.h"
#include "EventManager.h"
#include "Sphere.h"

using namespace libPRGR;

Object::Object() {
	id = idCounter++;
	this->pos = { 0, 0, 0, 1 };
}

Object::Object(string file) {
	id = idCounter++;
	this->pos = { 0, 0, 0, 1 };
	loadFromFile(file);
}

void Object::loadFromFile(string file)
{
	// Abrir fichero
	std::ifstream f(file);
	if (f.is_open()) {
		// leerVertices
		leerVertices(f);
		// leerColores
		leerColores(f);
		//leerNormales
		leerNormales(f);
		//leerTexturas
		leerTexturas(f);
		// leerCaras
		leerCaras(f);
		// leerProgramas
		leerProgramas(f);
	}
	else {
		cout << "ERROR: Fichero " << file << " no existe" << endl;
	}

	// Crear colisionador tipo esfera con partículas de los vértices
	Sphere* sphereColl = new Sphere();

	for (auto& v : vertexList) {
		Collider::particle p;
		p.min = v.vPos - Vector4f{ 0.005f, 0.005f, 0.005f, 0 };  // Pequeño volumen alrededor del vértice
		p.max = v.vPos + Vector4f{ 0.005f, 0.005f, 0.005f, 0 };
		sphereColl->addParticle(p);
	}

	coll = sphereColl;
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

void Object::leerNormales(std::ifstream& f)
{
	string linea = "";
	// Mientras linea no "end"
	do {
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			std::stringstream l(linea);
			string identificador;
			string normal;
			l >> identificador;
			l >> normal;
			std::vector<float> n = splitString<float>(normal, ',');

			//Sacar identificador
			int vertexId = splitString<int>(identificador, ':')[0];
			this->vertexList[vertexId - 1].vNormal = { n[0], n[1], n[2], n[3] };
		}
	} while (linea != "end");
}

void Object::leerTexturas(std::ifstream& f)
{
	string linea = "";
	// Mientras linea no "end"
	do {	//1er bucle: lee coords textura
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			std::stringstream l(linea);
			string identificador;
			string textureCoord;
			l >> identificador;
			l >> textureCoord;
			std::vector<float> tc = splitString<float>(textureCoord, ',');

			//Sacar identificador
			int vertexId = splitString<int>(identificador, ':')[0];
			this->vertexList[vertexId - 1].vTextureCoord = { tc[0], tc[1], -1, -1 };
		}
	} while (linea != "end");
	
	do {	//2do bucle: lee fichero textura
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			// fichero textura en linea
			this->mat = new Material(linea, 1.0f, 1.0f, 1);
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

void Object::leerProgramas(std::ifstream& f)
{
	std::vector<string> shaderList;
	string linea = "";
	// Mientras linea no "end"
	do {
		// Leer linea 
		std::getline(f, linea);
		// Ver si es comentario
		if ((linea[0] != '/' && linea[1] != '/') && (linea != "end")) {
			
			shaderList.push_back(linea);
		}
	} while (linea != "end");
	this->program = new GLProgram(shaderList);
}

void Object::update(float timeStep) {
	if (EventManager::keyState[GLFW_KEY_LEFT]) {
		this->pos.x -= 0.01f;
	}

	if (EventManager::keyState[GLFW_KEY_RIGHT]) {
		this->pos.x += 0.01f;
	}

	float rotationSpeed = 1.0f;
	//this->rot.y += rotationSpeed*timeStep;
}

Matrix4x4f Object::computeModelMatrix() {
	Matrix4x4f model = make_identityf();
	model = make_translate(pos.x, pos.y, pos.z);
	model = model*make_rotation_xyz(rot.x, rot.y, rot.z);
	model = model*make_scale(size.x, size.y, size.z);
	return model;
}

void Object::updateCollider() {
	if (!coll) return;

	Matrix4x4f modelMatrix = computeModelMatrix();
	coll->update(modelMatrix);
}
