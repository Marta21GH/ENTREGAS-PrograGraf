#include "Camera.h"
#include "EventManager.h"
#include "Sphere.h"
#include "Object3D.h"
#include "Render.h"

using namespace libPRGR;

Matrix4x4f Camera::computeViewMatrix()
{
    Matrix4x4f view = make_identityf();
    Vector4f f = normalize(lookAt - pos);
    Vector4f r = normalize(cross_product(f, normalize(up)));
    Vector4f u = normalize(cross_product(r, f));
    Vector4f p = { -(r * pos), -(u * pos), (f * pos), 1 };

    view.matrix[0][0] = r.x;
    view.matrix[0][1] = r.y;
    view.matrix[0][2] = r.z;

    view.matrix[1][0] = u.x;
    view.matrix[1][1] = u.y;
    view.matrix[1][2] = u.z;

    view.matrix[2][0] = -1.0f * f.x;
    view.matrix[2][1] = -1.0f * f.y;
    view.matrix[2][2] = -1.0f * f.z;

    view.matrix[0][3] = p.x;
    view.matrix[1][3] = p.y;
    view.matrix[2][3] = p.z;

    return view;
}

Matrix4x4f Camera::computeProjectionMatrix()
{
    Matrix4x4f proj = make_identityf();
    double fovyRad = toRadians(this->fovy);

    proj.matrix[0][0] = 1.0f / (aspectRatio * std::tan(fovyRad * 0.5f));
    proj.matrix[1][1] = 1.0f / std::tan(fovyRad * 0.5f);
    proj.matrix[2][2] = -1.0f * ((zFar + zNear) / (zFar - zNear));
    proj.matrix[2][3] = 2.0f * zFar * zNear / (zFar - zNear);
    proj.matrix[3][3] = 1;
    proj.matrix[3][2] = -1;
    return proj;
}

Camera::Camera(Vector4f pos, Vector4f up, Vector4f lookAt) : pos(pos), up(up), lookAt(lookAt) {
    Sphere* sphereColl = new Sphere();
    Collider::particle p;
    p.min = pos - Vector4f{ 0.125f, 0.125f, 0.125f, 0 };
    p.max = pos + Vector4f{ 0.125f, 0.125f, 0.125f, 0 };
    sphereColl->addParticle(p);
    coll = sphereColl;
    originalCenter = (p.min + p.max) * 0.5f;
}

void Camera::update()
{
    Vector4f prevPos = pos;
    Vector4f prevLookAt = lookAt;

    float moveSpeed = 0.005f;
    if (EventManager::keyState[GLFW_KEY_W] || EventManager::keyState[GLFW_KEY_UP]) { pos.z += moveSpeed; lookAt.z += moveSpeed; }
    if (EventManager::keyState[GLFW_KEY_S] || EventManager::keyState[GLFW_KEY_DOWN]) { pos.z -= moveSpeed; lookAt.z -= moveSpeed; }
    if (EventManager::keyState[GLFW_KEY_A] || EventManager::keyState[GLFW_KEY_LEFT]) { pos.x += moveSpeed; lookAt.x += moveSpeed; }
    if (EventManager::keyState[GLFW_KEY_D] || EventManager::keyState[GLFW_KEY_RIGHT]) { pos.x -= moveSpeed; lookAt.x -= moveSpeed; }

    Matrix4x4f modelMatrix = make_translate(pos.x, pos.y, pos.z);
    Sphere* sphere = dynamic_cast<Sphere*>(coll);
    if (sphere) {
        sphere->center = modelMatrix * originalCenter;
        sphere->radius = 0.125f;
    }

    if (!Render::objectList.empty()) {
        Object* target = Render::objectList.front();
        std::cout << "[DEBUG] Probando colisión contra objeto ID: " << target->id << std::endl;
        if (coll && target && target->coll && coll->test(target->coll)) {
            pos = prevPos;
            lookAt = prevLookAt;

            modelMatrix = make_translate(pos.x, pos.y, pos.z);
            if (sphere) {
                sphere->center = modelMatrix * originalCenter;
                sphere->radius = 0.125f;
            }
        }
    }
}
