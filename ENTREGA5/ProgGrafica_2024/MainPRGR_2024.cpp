#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/render.h"
using namespace libPRGR;

int main(int argc, char** argv)
{
	std::cout << "🟡 Iniciando programa...\n";

	// Crear render
	Render* r = new Render();
	if (!r) {
		std::cerr << "❌ Error al crear el objeto Render\n";
		return 1;
	}
	std::cout << "✅ Render creado\n";

	// Inicializar GLFW y OpenGL
	r->initGLFW();
	std::cout << "✅ initGLFW ejecutado\n";

	// Cargar objeto
	Object* cubo = new Object();
	if (!cubo) {
		std::cerr << "❌ No se pudo crear el objeto 3D\n";
		return 2;
	}

	std::cout << "🔄 Cargando modelo desde cuboCaras.fiis...\n";
	cubo->loadFromFile("data/cuboCaras.fiis");
	std::cout << "✅ Modelo cargado\n";

	// Rotaciones iniciales
	cubo->rot.z = 45.0;
	cubo->rot.x = 45.0;

	// Crear cámara
	Camera* cam1 = new Camera(
		{ 0,0,-3,1 },   // posición
		{ 0,0,0,0 },    // centro
		{ 0,0,0,1 },    // rotación
		{ 0,1,0,0 },    // up
		90,             // FOV
		640.0f / 480.0f,
		0.01f,
		100.0f
	);
	std::cout << "✅ Cámara creada\n";

	// Crear luz
	Light* light1 = new Light(
		{ 0,0,-1,0 },   // dirección
		{ 0,0,3,1 },    // posición
		{ 1,1,1,1 },    // color
		1.0f,           // ia
		1.0f,           // id
		1.0f,           // is
		LightType::POINT
	);
	std::cout << "✅ Luz creada\n";

	// Agregar elementos al render
	r->putCamera(cam1);
	r->putLight(light1);
	r->putObject(cubo);
	std::cout << "✅ Elementos añadidos al render\n";

	// Entrar en el bucle principal
	std::cout << "▶ Iniciando mainLoop()\n";
	r->mainLoop();
	std::cout << "⏹ mainLoop finalizado\n";

	// Terminar GLFW
	r->deinitGLFW();
	std::cout << "✅ GLFW finalizado\n";

	return 0;
}
