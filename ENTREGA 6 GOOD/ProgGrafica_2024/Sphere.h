#pragma once
#include "Collider.h"

class Sphere : public Collider {
public:
    Vector4f center = { 0, 0, 0, 1 };
    float radius = 0.0f;

    Sphere() {
        type = SPHERE;
    }

    // Añadir una partícula al partList
    void addParticle(particle part) override;

    // Test de colisión con otro colisionador
    bool test(Collider* c2) override;

    // Actualizar centro y radio según matriz de transformación
    void update(Matrix4x4f mat) override;

private:
    // Método auxiliar para recalcular centro y radio
    void computeBoundingSphere();
};
