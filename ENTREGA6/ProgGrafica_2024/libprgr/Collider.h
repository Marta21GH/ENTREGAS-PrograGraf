#pragma once
#include "vectorMath.h"
#include <vector>

using namespace libPRGR;

class Collider {
public:
    enum collTypes { sphere, AABB };

    struct particle {
        libPRGR::Vector4f min;
        libPRGR::Vector4f max;
    };

    collTypes type = sphere;
    std::vector<particle> partList;

    Collider() {}
    virtual ~Collider() {}

    virtual void addParticle(particle p) = 0;
    virtual bool test(Collider* c2) = 0;
    virtual void update(libPRGR::Matrix4x4f mat) = 0;

    // opcional si hicieras jerarquía (no obligatorio en esta entrega)
    virtual void subdivide() {}
};
#pragma once
