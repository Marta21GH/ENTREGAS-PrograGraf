#include "Shader.h"
using namespace libPRGR;

Shader::Shader(std::string fileName)
{
}

void Shader::readSource()
{
	string lAux = "";
	string linea = "";
	std::ifstream f(this->fileName);
	// Mientras linea no "end"
	do {
		// Leer linea 
		std::getline(f, lAux);
		// Ver si es comentario
		if ((lAux[0] != '/' && lAux[1] != '/') && (lAux != "end")) {
			linea.append(lAux);
		}
	} while (linea != "end");
	this->source = linea;
}

void Shader::compileShader()
{
}

void Shader::checkErrors()
{
	GLint retCode;
	char errorLog[1024];
	GLint fragment_compiled;
	glGetShaderiv(idShader, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(idShader, 1024, &log_length, message);
		std::cout << "ERROR " << fileName << "\n" << message << "\n\n";
	}
}

void Shader::clean()
{
}
