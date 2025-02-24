#include "Object3D.h"

void Object3D::createTriangle()
{
	id = idCounter++;
	this->position = { 0, 0, 0, 1 };
	this->scale = { 1, 1, 1, 1 };
	this->vertexList.push_back({ 0, 0.25, 0, 1 });
	this->vertexList.push_back({ -0.25, -0.25, 0, 1 });
	this->vertexList.push_back({ 0.25, -0.25, 0, 1 });
	this->idList = { 0, 1, 2 };
}

void Object3D::updateModelMatrix()
{
	modelMatrix = make_rotation_xyz(this->rotation.x, this->rotation.y, this->rotation.z);

	modelMatrix = modelMatrix * make_translate(this->position.x, this->position.y, this->position.z);
	modelMatrix = modelMatrix * make_scale(this->scale.x, this->scale.y, this->scale.z);
}
