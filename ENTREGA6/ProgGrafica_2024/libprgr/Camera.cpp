#include "Camera.h"
#include "EventManager.h"
#include "render.h"

Matrix4x4f Camera::lookat()
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

	view.matrix[2][0] = -f.x;
	view.matrix[2][1] = -f.y;
	view.matrix[2][2] = -f.z;

	view.matrix[0][3] = p.x;
	view.matrix[1][3] = p.y;
	view.matrix[2][3] = p.z;

	return view;
}

Matrix4x4f Camera::projection()
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

void Camera::setCollider() {
	this->coll = new Sphere();

	Collider::particle p;
	float sz = 0.25f;
	p.min = { -sz / 2, -sz / 2, -sz / 2, 1 };
	p.max = { sz / 2,  sz / 2,  sz / 2, 1 };
	this->coll->addParticle(p);

	this->coll->update(make_translate(pos.x, pos.y, pos.z));
}

void Camera::move(double timestep) {
	Vector4f previousPos = pos;
	Vector4f previousLook = lookAt;

	if (EventManager::keyState[GLFW_KEY_UP]) { this->pos.z += 0.005f; lookAt.z += 0.005f; }
	if (EventManager::keyState[GLFW_KEY_DOWN]) { this->pos.z -= 0.005f; lookAt.z -= 0.005f; }
	if (EventManager::keyState[GLFW_KEY_LEFT]) { this->pos.x += 0.005f; lookAt.x += 0.005f; }
	if (EventManager::keyState[GLFW_KEY_RIGHT]) { this->pos.x -= 0.005f; lookAt.x -= 0.005f; }

	this->lookAt.x = -1 * (EventManager::mouseState.x - 320) / 40;
	this->lookAt.y = -1 * (EventManager::mouseState.y - 240) / 40;

	if (this->coll)
		this->coll->update(make_translate(pos.x, pos.y, pos.z));

	extern Render* gRender;
	for (auto obj : Render::getAllObjects(gRender)) {
		if (obj->coll && this->coll && this->coll->test(obj->coll)) {
			std::cout << "💥 Colisión con objeto ID: " << obj->ObjectId << std::endl;
			this->pos = previousPos;
			this->lookAt = previousLook;
			this->coll->update(make_translate(pos.x, pos.y, pos.z));
			break;
		}
	}
}