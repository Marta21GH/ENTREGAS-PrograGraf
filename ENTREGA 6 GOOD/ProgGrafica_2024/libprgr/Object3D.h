#pragma once
#include "common.h"
#include "vectorMath.h"
#include "vertex.h"
#include "GLProgram.h"
#include "Material.h"
#include "Collider.h"
#include "Sphere.h"

using namespace libPRGR;

class Object {
public:
    inline static int idCounter = 0;
    int id;

    Material* mat;
    Vector4f pos = { 0,0,0,1 };
    Vector4f rot = { 0,0,0,0 };
    Vector4f size = { 1,1,1,1 };

    std::vector<vertex_t> vertexList;
    std::vector<unsigned int> indexVertexList;
    GLProgram* program = nullptr;

    // NUEVO: Colisionador
    Collider* coll = nullptr;

    // NUEVO: Atributos para colisión tipo esfera
    Vector4f center;
    float radius = 0.0f;

    Object();
    Object(std::string file);

    virtual void update(float timeStep);
    Matrix4x4f computeModelMatrix();
    void updateCollider();

    void loadFromFile(std::string file);
    void leerVertices(std::ifstream& f);
    void leerNormales(std::ifstream& f);
    void leerTexturas(std::ifstream& f);
    void leerColores(std::ifstream& f);
    void leerCaras(std::ifstream& f);
    void leerProgramas(std::ifstream& f);

    // NUEVO: Calcular esfera englobante
    void computeBoundingSphere();
};
