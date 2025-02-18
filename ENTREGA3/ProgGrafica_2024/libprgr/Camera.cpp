#include "Camera.h"
#include "InputManager.h"

Matrix4x4f Camera::computeViewMatrix()
{
    Matrix4x4f view = make_identityf();
    Vector4f f = normalize(lookAt - pos);
    Vector4f r = normalize(cross_product(f, normalize(up)));
    Vector4f u = normalize(cross_product(r, f));
    Vector4f p = { -(r * pos), -(u * pos), (f * pos), 1};

    //TODO: Rows y columns en vectormath.h

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

void Camera::update()
{
    if (InputManager::keyState[GLFW_KEY_W]) { this->pos.z += 0.01f; lookAt.z += 0.01; }
    if (InputManager::keyState[GLFW_KEY_S]) { this->pos.z -= 0.01f; lookAt.z -= 0.01; }
    if (InputManager::keyState[GLFW_KEY_A]) { this->pos.x += 0.01f; lookAt.x += 0.01; }
    if (InputManager::keyState[GLFW_KEY_D]) { this->pos.x -= 0.01f; lookAt.x -= 0.01; }
}
