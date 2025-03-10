#include "Program.h"

Program::Program()
{
	//crear program id
	idProgram = glCreateProgram();
}

void Program::addShader(std::string fileName)
{
	Shader* shadAux = new Shader(fileName);	
	this->shaderList.push_back(shadAux);
}

void Program::linkProgram()
{
	glLinkProgram(idProgram);
}

void Program::checkErrors()
{
	GLint program_linked;
	glGetProgramiv(idProgram, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(idProgram, 1024, &log_length, message);
		std::cout << "ERROR \n" << message << "\n\n";
	}
}

void Program::clean()
{
}

void Program::readVarList()
{
	int numAttributes = 0;
	int numUniforms = 0;

	glGetProgramiv(idProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
	for (int i = 0; i < numAttributes; i++)
	{
		char varName[100];
		int bufSize = 100, length = 0, size = 0;
		GLenum type = -1;
		glGetActiveAttrib(idProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
		varList[std::string(varName)] = glGetAttribLocation(idProgram, varName);
	}

	glGetProgramiv(idProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
	for (int i = 0; i < numUniforms; i++)
	{
		string varName; varName.resize(100);
		int bufSize = 100, length = 0, size = 0;
		GLenum type = -1;
		glGetActiveUniform(idProgram, (GLuint)i, bufSize, &length, &size, &type, varName.data());
		varName = std::string(varName.c_str()); //interrogar con nombre
		if (varName[varName.length() - 1] == ']') { //si es de tipo array
			std::string arrName = varName.substr(0, varName.find('['));
			for (int i = 0; i < size; i++) //conseguir la lista completa de nombres
			{
				std::string arrNameIdx = arrName + "[" + std::to_string(i) + "]";
				varList[arrNameIdx] = glGetUniformLocation(idProgram, arrNameIdx.c_str());
			}
		}
		else {
			varList[varName] = glGetUniformLocation(idProgram, varName.c_str());
		}
	}
}

void Program::use()
{
	glUseProgram(idProgram);
}

void Program::setUniformData(dataType_e tipo, void* dato, string nombre)
{
	if (varList.find(nombre) == varList.end()) {
		cout << "ERROR: Variable de shader " << nombre << " no encontrada" << endl;
	}
	else {
		switch (tipo) {
		case matrix4:
			glUniformMatrix4fv(varList[nombre], 1, GL_TRUE, (float*)dato);
			break;
		case vector4:
			break;
		case floatpoint:
			break;
		case integer:
			break;
		default:
			cout << "ERROR: TIPO " << tipo << "NO VÁLIDO" << endl;
		}
	}
}

void Program::setAttributeData(string nombre, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	if (varList.find(nombre) == varList.end()) {
		cout << "ERROR: Variable de shader " << nombre << " no encontrada" << endl;
	}
	else {
		unsigned int index = varList[nombre];
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
}
