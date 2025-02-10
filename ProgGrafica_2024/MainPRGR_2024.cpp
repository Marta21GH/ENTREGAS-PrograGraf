#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/InputManager.h"
#include "libprgr/Render.h"
#include "libprgr/Object3D.h"

using namespace libPRGR;

int main(int argc, char** argv)
{
	//Crear una clase "Render" de tama�o 640 * 480 p�xeles, y llamar a su m�todo �initGL�
	Render* rend = new Render(480, 640);
	rend->initGL();

	//Crear una variable "triangulo" de tipo Object3D, y llamar a su m�todo �createTriangle� para que 
	//	almacene los v�rtices e identificadores de v�rtices para un tri�ngulo
	Object3D* triangulo = new Object3D();
	triangulo->createTriangle();
	
	//Dibujarlo en el buffer(putObject), y mostrar el buffer por ventana(mainLoop)
	rend->putObject(triangulo);
	
	//Cuando se pulsen las teclas �A� o �D� el tri�ngulo girar� acorde con lo indicado en su m�todo
	//	�update�.
	rend->mainLoop();

	//finalizar GLFW y liberar recursos
	glfwTerminate();

	return 0;
}