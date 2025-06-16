#pragma once
#include "vectorMath.h"
#include <vector>

class Collider {
public:
    struct particle {
        libPRGR::Vector4f min;
        libPRGR::Vector4f max;
    };

    enum collTypes { SPHERE, AABB };

    collTypes type = SPHERE;

    std::vector<particle> partList;

    Collider() {}
    virtual ~Collider() {}

    virtual void addParticle(particle part) = 0;
    virtual bool test(Collider* c2) = 0;
    virtual void update(libPRGR::Matrix4x4f mat) = 0;

    virtual void subdivide() {}
    std::vector<Collider*> sons;
};
