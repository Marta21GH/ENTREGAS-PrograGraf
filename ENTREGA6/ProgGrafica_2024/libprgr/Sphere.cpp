#include "Sphere.h"
#include <cmath>

Sphere::Sphere() {
    this->type = sphere;
    center = { 0, 0, 0, 1 };
    radius = 0;
}

void Sphere::addParticle(particle p) {
    partList.push_back(p);
}

void Sphere::update(Matrix4x4f mat) {
    if (partList.empty()) return;

    Vector4f min = partList[0].min;
    Vector4f max = partList[0].max;

    for (const auto& p : partList) {
        min.x = std::min(min.x, p.min.x);
        min.y = std::min(min.y, p.min.y);
        min.z = std::min(min.z, p.min.z);

        max.x = std::max(max.x, p.max.x);
        max.y = std::max(max.y, p.max.y);
        max.z = std::max(max.z, p.max.z);
    }

    center = {
        (min.x + max.x) / 2,
        (min.y + max.y) / 2,
        (min.z + max.z) / 2,
        1
    };

    radius = 0;
    for (const auto& p : partList) {
        Vector4f localCenter = {
            (p.min.x + p.max.x) / 2,
            (p.min.y + p.max.y) / 2,
            (p.min.z + p.max.z) / 2,
            1
        };
        float dist = std::sqrt(
            std::pow(localCenter.x - center.x, 2) +
            std::pow(localCenter.y - center.y, 2) +
            std::pow(localCenter.z - center.z, 2)
        );
        radius = std::max(radius, dist);
    }

    // Aplicar transformación al centro
    center = mat * center;
    // Para simplificar, ignoramos la escala en el radio (podemos multiplicar por norma de escalado si quieres precisión)
}

bool Sphere::test(Collider* c2) {
    if (c2->type != sphere) return false;

    Sphere* other = static_cast<Sphere*>(c2);
    float dist = std::sqrt(
        std::pow(center.x - other->center.x, 2) +
        std::pow(center.y - other->center.y, 2) +
        std::pow(center.z - other->center.z, 2)
    );

    return dist <= (radius + other->radius);
}
