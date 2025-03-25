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
	//	Crear una clase "Render" de tamaño 640*480 píxeles, y llamar a su método “initGL”
	Render* r = new Render();
	r->initGLFW();

	//	Crear una variable "cubo" de tipo Object3D, y llamar a su método “loadFromFile” pasándole el
	//	Nombre del fichero “cubo.fiis” creado anteriormente.
	Object* cubo = new Object();
	cubo->loadFromFile("data/cuboCaras.fiis");
	//	Rotar el cubo 45º en el eje Z y 45º en el eje X.
	cubo->rot.z = 0;
	cubo->rot.x = 0;

	//	Crear una cámara, posicionarla en la coordenada <0, 0, -3> y que apunte a la coordenada <0, 0, 0>.
	//		Ángulo de apertura de 90º, planos zNear = 0.01, zFar = 100
	Camera* cam1 = new Camera({ 0,0,-3,1 }, { 0,0,0,0 }, { 0,0,0,1 }, { 0,1,0,0 }, 90, (640.0f / 480.0f), 0.01f, 100.0f);
	
	//	Añadirlos al render(putObject, putCamera), y mostrar el escenario por ventana(mainLoop)
	r->putCamera(cam1);
	r->putObject(cubo);
	r->mainLoop();

	r->deinitGLFW();
	return 0;
}