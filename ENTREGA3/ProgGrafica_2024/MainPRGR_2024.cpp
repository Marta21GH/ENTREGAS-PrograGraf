#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/render.h"
using namespace libPRGR;

class Object;
class Bullet;



int main(int argc, char** argv)
{
	Render* r = new Render();
	r->cam = new Camera({0,0,-3,1}, { 0,0,0,0 }, {0,0,0,1}, {0,1,0,0}, 90, (640.0f / 480.0f), 0.01f, 100.0f);
	GLFWwindow* window = r->initGLFW();

	Object* objf = new Object("data/cubo.fiis");
	r->setUpObject(objf);

	while (!glfwWindowShouldClose(window)) {
		//Check eventos
		glfwPollEvents();
		for (auto obj : r->objectList) {
			obj->update();
			r->cam->move(0.1);
		}
		//Dibujar
			//Limpiar buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//Mandar figura a dibujar
			for (auto obj : r->objectList) {
				r->drawGL(obj);
			}
		//Cambiar buffers
		glfwSwapBuffers(window);
		;
	}

	r->deinitGLFW();
	return 0;
}