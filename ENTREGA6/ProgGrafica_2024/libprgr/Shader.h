#pragma once
#include "vectorMath.h"
#include "common.h"
#include "vertex.h"

class Shader {
public: 
	unsigned int idShader = -1;	// Variable que almacena el identificador de OpenGL para este shader
	std::string fileName;		// Variable que almacena el nombre del fichero de texto con el código de este shader
	GLenum type;				// Variable que almacea el tipo de shader que se ha creado: GL_VERTEX_SHADER o GL_FRAGMENT_SHADER
	std::string source;			// Variable que almacena el código del shader

	
	/*	Constructor de la clase, recibe por parámetros el nombre de fichero, lo cargará y compilará llamando al resto de 
		métodos	de clase */
	Shader(std::string fileName);
	
	/*	Método que abre elfichero de código de shader, lo lee y lo almacena en la variable “source” */
	void readSource();

	/*	Método que compila el shader */
	void compileShader();

	/*	Método que muestra si hay cualquier error tras compilar el shader */
	void checkErrors();

	/*	Método que libera los datos de compilación y código del shader. Es invocado	desde la clase “program” una vez se han 
		linkado los datos del shader */
	void clean();
 };