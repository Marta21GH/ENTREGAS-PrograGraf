#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/render.h"
using namespace libPRGR;

int main(int argc, char** argv)
{
	Render* r = new Render();
	Camera* cam1 = new Camera({0,0,-3,1}, {0,1,0,0}, {0,0,0,1});
	Light* light1 = new Light({ 0,0,-3,1 }, { 1,1,1,1 }, 0.5, 1.0, 2.0, LightType::DIRECTIONAL);
	GLFWwindow* window = r->initGLFW();

	Object* objf = new Object();
	objf->loadFromFile("data/cubeSplit.fiis");
	r->setUpObject(objf);
	r->putCamera(cam1);
	r->putLight(light1);

	r->mainLoop();

	r->deinitGLFW();
	return 0;
}