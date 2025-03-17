#pragma once
#include "vectorMath.h"
#include "common.h"
#include "Shader.h"

class Program {
public:
	typedef enum {
		integer,
		floatpoint,
		vector4,
		matrix4
	} dataType_e;

	unsigned int idProgram = -1;		// Variable que almacena el identificador de opengl asignado al programa
	std::vector<Shader*> shaderList;	// Lista de shaders necesarios para este programa.Debería almacenar al menos 
										// uno de vértices y uno de fragmentos
	std::map<std::string, unsigned int> varList; // Mapa de búsqueda para almacenar los identificadores de variables de los 
												 // shaders cargados anteriormente.Se buscarán las variables a partir de los 
												 // nombres de las mismas
	

	/*	Constructor por defecto de la clase.Inicializará la variable “idProgram” con un
		identificador de programa asignado por OpenGl */
	Program();
	
	/*	Método que, a partir de un nombre de fichero, crea un objeto de tipo Shader con los datos de ese fichero. Una vez 
		cargado, almacenará ese objeto en la lista “shaderList” */
	void addShader(std::string fileName);

	/*	Una vez añadidos todos los shaders al programa, se invocará este método para que linke todos los shaders y limpie 
		los datos de compilación.*/
	void linkProgram();

	/*	Método que mostrará errors encontrados durante la compilación y linkado del programa */
	void checkErrors();

	/*	Método para limpiar los datos de compilación una vez linkado el programa */
	void clean();

	/*	Método que inicializa los datos de la lista “varList” interrogando al programa para leer cada una de las variables 
		existents en el mismo */
	void readVarList();

	/*	Activa este programa para su uso en el render */
	void use();

	/*	Inician datos de GPU de tipo Atributo y uniform */
	void setUniformData(dataType_e tipo, void* dato, string nombre);
	void setAttributeData(string nombre, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);

};