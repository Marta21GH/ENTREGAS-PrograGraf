#include "Sphere.h"
#include <cmath>
#include <algorithm>

using namespace libPRGR;

float length(const libPRGR::Vector4f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void Sphere::addParticle(particle part)
{
    this->partList.push_back(part);

    // Calcular el centro de la partícula como media de min y max
    libPRGR::Vector4f center = {
        (part.min.x + part.max.x) * 0.5f,
        (part.min.y + part.max.y) * 0.5f,
        (part.min.z + part.max.z) * 0.5f,
        1.0f
    };

    // Calcular el radio como la mitad de la distancia entre min y max
    float radio = length(part.max - center);

    // Asignar como radio de la esfera si es mayor que el actual
    if (radio > this->radius)
        this->radius = radio;
}

void Sphere::computeBoundingSphere() {
    if (partList.empty()) return;

    Vector4f minTotal = partList[0].min;
    Vector4f maxTotal = partList[0].max;

    for (auto& p : partList) {
        minTotal.x = std::min(minTotal.x, p.min.x);
        minTotal.y = std::min(minTotal.y, p.min.y);
        minTotal.z = std::min(minTotal.z, p.min.z);

        maxTotal.x = std::max(maxTotal.x, p.max.x);
        maxTotal.y = std::max(maxTotal.y, p.max.y);
        maxTotal.z = std::max(maxTotal.z, p.max.z);
    }

    center = {
        (minTotal.x + maxTotal.x) / 2.0f,
        (minTotal.y + maxTotal.y) / 2.0f,
        (minTotal.z + maxTotal.z) / 2.0f,
        1.0f
    };

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
    float sumRadius = this->radius + other->radius;

    std::cout << "[TEST] dist: " << dist << " | r1: " << this->radius << " | r2: " << other->radius << std::endl;

    return dist <= sumRadius;
}
