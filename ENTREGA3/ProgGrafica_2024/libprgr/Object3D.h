#pragma once
#include "common.h"
#include "vectorMath.h"
#include "vertex.h"

class Object {
public:
	inline static int idCounter = 0;
	int id;
	Vector4f pos = { 0,0,0,1 };
	Vector4f rot = { 0,0,0,0 };
	Vector4f size = { 1,1,1,1 };
	vector<vertex_t> vertexList;
	vector<unsigned int> indexVertexList;

	Object();

	Object(string file);

	void update();

	Matrix4x4f computeModelMatrix();

	void loadFromFile(string file);

	void leerVertices(std::ifstream& f);

	void leerColores(std::ifstream& f);

	void leerCaras(std::ifstream& f);
};