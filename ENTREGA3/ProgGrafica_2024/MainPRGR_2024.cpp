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
	//Crear una clase "Render" de tamaño 640 * 480 píxeles, y llamar a su método “initGL”
	Render* rend = new Render(480, 640);
	rend->initGL();

	//Crear una variable "triangulo" de tipo Object3D, y llamar a su método “createTriangle” para que 
	//	almacene los vértices e identificadores de vértices para un triángulo
	Object3D* triangulo = new Object3D();
	triangulo->createTriangle();
	
	//Dibujarlo en el buffer(putObject), y mostrar el buffer por ventana(mainLoop)
	rend->putObject(triangulo);
	
	//Cuando se pulsen las teclas “A” o “D” el triángulo girará acorde con lo indicado en su método
	//	“update”.
	rend->mainLoop();

	//finalizar GLFW y liberar recursos
	glfwTerminate();

	return 0;
}