#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/render.h"
#include "libprgr/Object3D.h"
#include "libprgr/Camera.h"
#include "libprgr/EventManager.h"

using namespace libPRGR;

// 🔴 Definición global del puntero al render
Render* gRender = nullptr;

// Variable global para activar o desactivar el modo debug
bool debugDrawCollider = false;
bool tabKeyPressedLastFrame = false;

void drawCameraCollider(Camera* cam) {
	if (!cam->coll) return;

	auto* sphere = dynamic_cast<Sphere*>(cam->coll);
	if (!sphere) return;

	Vector4f c = sphere->center;
	float s = 0.25f;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 0, 0);

	glPushMatrix();
	glTranslatef(c.x, c.y, c.z);
	glScalef(s, s, s);

	glBegin(GL_LINES);
	glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv)
{
	std::cout << "🟡 Iniciando programa...\n";

	Render* r = new Render();
	if (!r) return 1;
	gRender = r;  // 🔴 inicializar puntero global

	r->initGLFW();

	Object* cubo = new Object();
	cubo->loadFromFile("data/blenderCube.fiis");
	cubo->updateCollider();

	cubo->rot = { 0, 0, 0, 0 };
	cubo->pos = { 0, 0, 0, 1 };

	Camera* cam1 = new Camera(
		{ 0,0,-3,1 },
		{ 0,0,0,0 },
		{ 0,0,0,1 },
		{ 0,1,0,0 },
		90,
		640.0f / 480.0f,
		0.01f,
		100.0f
	);

	cam1->setCollider();

	Light* light1 = new Light({ 0,0,-1,0 }, { 0,0,-3,1 }, { 1,1,1,1 }, 1.0f, 1.0f, 1.0f, LightType::DIRECTIONAL);

	r->putCamera(cam1);
	r->putLight(light1);
	r->putObject(cubo);

	std::cout << "▶ Iniciando mainLoop()\n";

	while (!glfwWindowShouldClose(r->window)) {
		glfwPollEvents();

		// Alternar modo debug con TAB
		if (EventManager::keyState[GLFW_KEY_TAB] && !tabKeyPressedLastFrame) {
			debugDrawCollider = !debugDrawCollider;
			std::cout << "[DEBUG] Visualización collider: " << (debugDrawCollider ? "ON" : "OFF") << std::endl;
		}
		tabKeyPressedLastFrame = EventManager::keyState[GLFW_KEY_TAB];

		cubo->updateCollider();
		cam1->move(0.1);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		r->drawGL(cubo);

		if (debugDrawCollider)
			drawCameraCollider(cam1);

		glfwSwapBuffers(r->window);
	}

	r->deinitGLFW();
	std::cout << "✅ GLFW finalizado\n";

	return 0;
}
