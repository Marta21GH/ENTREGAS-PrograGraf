#include "Sphere.h"
#include <cmath>  // Para sqrt

using namespace libPRGR;

void Sphere::addParticle(particle part) {
    partList.push_back(part);
    computeBoundingSphere();  // Recalcula centro y radio al añadir nueva partícula
}

void Sphere::computeBoundingSphere() {
    if (partList.empty()) return;

    Vector4f minTotal = partList[0].min;
    Vector4f maxTotal = partList[0].max;

    // Calcular los extremos del volumen
    for (auto& p : partList) {
        minTotal.x = std::min(minTotal.x, p.min.x);
        minTotal.y = std::min(minTotal.y, p.min.y);
        minTotal.z = std::min(minTotal.z, p.min.z);

        maxTotal.x = std::max(maxTotal.x, p.max.x);
        maxTotal.y = std::max(maxTotal.y, p.max.y);
        maxTotal.z = std::max(maxTotal.z, p.max.z);
    }

    // Centro = punto medio entre extremos
    center = {
        (minTotal.x + maxTotal.x) / 2.0f,
        (minTotal.y + maxTotal.y) / 2.0f,
        (minTotal.z + maxTotal.z) / 2.0f,
        1.0f
    };

    // Radio = distancia desde el centro al punto más alejado (max)
    float maxDist = 0.0f;
    for (auto& p : partList) {
        Vector4f point = {
            (p.min.x + p.max.x) / 2.0f,
            (p.min.y + p.max.y) / 2.0f,
            (p.min.z + p.max.z) / 2.0f,
            1.0f
        };
        float dist = distance(center, point);
        if (dist > maxDist) {
            maxDist = dist;
        }
    }
    radius = maxDist;
}

void Sphere::update(Matrix4x4f mat) {
    center = mat * center;

    // Estimar escalado desde la matriz (asumimos uniforme en x)
    float scaleX = std::sqrt(mat.matrix[0][0] * mat.matrix[0][0] +
        mat.matrix[1][0] * mat.matrix[1][0] +
        mat.matrix[2][0] * mat.matrix[2][0]);

    radius *= scaleX;
}

bool Sphere::test(Collider* c2) {
    if (c2->type != SPHERE) return false;

    Sphere* other = dynamic_cast<Sphere*>(c2);
    if (!other) return false;

    float dist = distance(this->center, other->center);
    return dist <= (this->radius + other->radius);
}
