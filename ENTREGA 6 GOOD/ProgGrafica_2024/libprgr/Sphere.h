#pragma once
#include "Collider.h"

class Sphere : public Collider {
public:
    libPRGR::Vector4f center = { 0, 0, 0, 1 };
    float radius = 0.0f;

    Sphere() {
        type = SPHERE;
    }

    void addParticle(particle part) override;
    bool test(Collider* c2) override;
    void update(libPRGR::Matrix4x4f mat) override;

private:
    void computeBoundingSphere();
};
