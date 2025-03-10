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
	f.close();
	this->source = linea;
}

void Shader::compileShader()
{
	unsigned int tipo = -1;
	if (this->fileName.ends_with(".vert")) {
		tipo = GL_VERTEX_SHADER;
	}
	else if (this->fileName.ends_with(".frag")) {
		tipo = GL_FRAGMENT_SHADER;
	}

	//leer archivos
	string code;
	std::ifstream f(this->fileName);
	if (f.is_open()) {
		code = std::string(std::istreambuf_iterator<char>(f), {});
	}
	else {
		std::cout << "ERROR: FICHERO NO ENCONTRADO " <<
			__FILE__ << ":" << __LINE__ << " " << this->fileName << "\n";
	}

	//compilar
	const char* shaderCode = code.c_str();
	int shaderID = glCreateShader(tipo);
	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);

	//checkshadererror()
	checkErrors();
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

	if (idShader != 0) {
		glDeleteShader(idShader);
		idShader = 0;
	}

}
