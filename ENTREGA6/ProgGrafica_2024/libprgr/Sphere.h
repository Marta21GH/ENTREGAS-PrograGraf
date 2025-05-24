#pragma once
#include "Collider.h"

class Sphere : public Collider {
public:
    Vector4f center;
    float radius;

    Sphere();
    void addParticle(particle p) override;
    bool test(Collider* c2) override;
    void update(Matrix4x4f mat) override;
};
