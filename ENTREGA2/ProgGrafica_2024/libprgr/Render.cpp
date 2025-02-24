#include "Render.h"
#include "InputManager.h"

void Render::initGL()
{
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "ERROR" << endl;
		this->window = nullptr;
	}
	else {
		std::cout << "TODO BIEN" << endl;
	}

	GLFWwindow* win1 = glfwCreateWindow(this->width, this->height, "Ventana1", nullptr, nullptr);
	glfwMakeContextCurrent(win1);
	gladLoadGL(glfwGetProcAddress);

	InputManager::init(win1);

	this->window = win1;
}

void Render::putObject(Object3D* obj)
{
	this->objectList.push_back(obj);
	bufferObject bo;

	//Generar buffers de datos
	glGenVertexArrays(1, &bo.idArray); //id 1
	glGenBuffers(1, &bo.idVertexArray); //id 2
	glGenBuffers(1, &bo.idIndexArray); //id 3

	glBindVertexArray(bo.idArray);
	//Activar datos buffers
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	//Subir datos buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);
	//Activar datos buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);
	//Subir datos buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex) * obj->idList.size(), obj->idList.data(), GL_STATIC_DRAW);

	//Guardar bufferObject en mapa
	this->bufferObjects[obj->id] = bo;
}

void Render::removeObject(Object3D* obj)
{
	//recupera el bufferObjc correspondiente al obj que queremos eliminar
	bufferObject bo = bufferObjects[obj->id];

	//libera buffer de vertices e indices
	glDeleteBuffers(1, &bo.idVertexArray);
	glDeleteBuffers(1, &bo.idIndexArray);

	//libera el vertex array object 
	glDeleteVertexArrays(1, &bo.idArray);

	//elimina bufferObject del mapa bufferObjects 
	bufferObjects.erase(obj->id);

	//elimina objeto 3d de la lista de objetos 
	objectList.remove(obj);
	//remove() --> mueve obj al final de la lista
	//erase() --> posicion final donde quedo el objeto

	delete obj;
}

void Render::drawGL()
{
	for (Object3D* obj : this->objectList) {
		//Seleccionar malla
		auto model = obj->modelMatrix; //updatemodelmatrix

		//Activar buffers
		auto bo = bufferObjects[obj->id];
		glBindVertexArray(bo.idArray);
		glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

		glPushMatrix();
		glLoadIdentity();
		glMultTransposeMatrixf(&model.matrix[0][0]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, pos));

		glDrawElements(GL_TRIANGLES, obj->idList.size(), GL_UNSIGNED_INT, nullptr);

		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
}

void Render::mainLoop()
{
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Actualizar pos/rot/esc figuras
		for (auto obj : objectList) {
			obj->move(0.005);
			obj->updateModelMatrix();
		}

		//Mandar figuras a dibujar
		drawGL();

		//Cambiar buffers
		glfwSwapBuffers(window);
	}
}
