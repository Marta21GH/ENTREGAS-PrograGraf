#pragma once
#include "libprgr/vectorMath.h"
#include <vector>

class Collider {
public:
    typedef struct {
        libPRGR::Vector4f min;
        libPRGR::Vector4f max;
    } particle;

    enum collTypes { SPHERE, AABB };

    collTypes type = SPHERE;  // Tipo de colisionador
    std::vector<particle> partList;  // Lista de partículas

    // Constructor vacío
    Collider() {}

    // Destructor virtual
    virtual ~Collider() {}

    // Añadir partícula al colisionador
    virtual void addParticle(particle part) = 0;

    // Test de colisión con otro colisionador
    virtual bool test(Collider* c2) = 0;

    // Actualizar el colisionador según una matriz de transformación
    virtual void update(libPRGR::Matrix4x4f mat) = 0;

    // (Opcional) Subdividir en jerarquía (si implementamos jerarquía más adelante)
    virtual void subdivide() {}

    // (Opcional) Hijos del volumen para jerarquía
    std::vector<Collider*> sons;
};
