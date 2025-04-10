#include "Program.h"

Program::Program()
{
	//crear program id
	idProgram = glCreateProgram();
}

void Program::addShader(std::string fileName)
{
	Shader* shadAux = new Shader(fileName);
	if (shadAux->idShader == 0) {
		std::cerr << "ERROR: No se pudo cargar el shader " << fileName << std::endl;
		delete shadAux;
	}
	else {
		this->shaderList.push_back(shadAux);
	}
}

void Program::linkProgram()
{
	// Adjuntar shaders al programa antes de linkearlo
	//por cada archivo
	for (auto& shader : shaderList) {
		glAttachShader(this->idProgram, shader->idShader);
	}

	// Linkear el programa
	glLinkProgram(idProgram);

	// Verificar errores
	checkErrors();

	//lee variables del shader
	readVarList();

	// Una vez linkeado, podemos limpiar los shaders
	for (auto& shader : shaderList) {
		shader->clean();  // Liberar datos del shader
		delete shader;    // Liberar memoria
	}
	shaderList.clear();  // Vaciar la lista
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
	if (idProgram != -1) {
		glDeleteProgram(idProgram);
		idProgram = -1;
	}
}

void Program::readVarList()
{
	int numAttributes = 0;
	int numUniforms = 0;

	glGetProgramiv(this->idProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
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
		if (!varName.empty() && varName.back() == ']') {
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
		cout << "ERROR: Variable de shader '" << nombre << "' no encontrada" << endl;
		return;  // ← ⚠️ Esto evita el crash
	}

	cout << "✔ Enviando uniform: " << nombre << endl;

	switch (tipo) {
	case matrix4:
		glUniformMatrix4fv(varList[nombre], 1, GL_TRUE, (float*)dato);
		break;
	case vector4:
		glUniform4fv(varList[nombre], 1, (float*)dato);
		break;
	case floatpoint:
		glUniform1f(varList[nombre], *(float*)dato);
		break;
	case integer:
		glUniform1i(varList[nombre], *(int*)dato);
		break;
	default:
		cout << "ERROR: TIPO " << tipo << " NO VÁLIDO" << endl;
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
