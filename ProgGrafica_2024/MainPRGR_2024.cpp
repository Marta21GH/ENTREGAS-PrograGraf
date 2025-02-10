#include <iostream>
#include "libprgr/vectorMath.h"
using namespace libPRGR;
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/EventManager.h"

GLFWwindow* initGLFW()
{
	if (glfwInit() != GLFW_TRUE) {
		cout << "Error GLFW\n";
		return nullptr;
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	GLFWwindow* window = glfwCreateWindow(1080, 720, "Ventana 1", nullptr, nullptr);
	
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	EventManager::init(window);

	return window;
}

void deinitGLFW()
{
	glfwTerminate();
}

typedef struct {
	vector4f vPos;
	vector4f vColor;

}vertex_t;

class Object {
public:
	vector4f pos;
	vector<vertex_t> vertexList;
	vector<unsigned int> indexVertexList;

	inline static int idCounter = 0;
	int id;

	Object() {
		id = idCounter++;
		this->pos = { 0,0,0,1 };
		this->vertexList.push_back({ {0, 0.5, 0, 1}, {1,0,0,1} });
		this->vertexList.push_back({ {-0.5, -0.5, 0, 1}, {0,1,0,1} });
		this->vertexList.push_back({ {0.5, -0.5, 0, 1}, {0,0,1,1} });

		this->indexVertexList = {0, 1, 2};
	}

	void update() {
		if (EventManager::keyState[GLFW_KEY_LEFT]) {
			this->pos.x -= 0.001f;
			cout << "Tecla izquierda pulsada!\n";
		}

		if (EventManager::keyState[GLFW_KEY_RIGHT]) {
			this->pos.x += 0.001f;
			cout << "Tecla derecha pulsada!\n";
		}
	}

};

typedef struct {
	unsigned int idArray; //identificador de grupos de arrays
	unsigned int idVertexArray; //identificador datos de vertice
	unsigned int idIndexArray; //identificador de orden de vertices
}bufferObject;

map<int, bufferObject> bufferObjectList;
list<Object*> objectList;

void setupObject(Object* obj)
{
	objectList.push_back(obj);
	bufferObject bo;
	//generar buffers de datos
	glGenVertexArrays(1, &bo.idArray);
	glGenBuffers(1, &bo.idVertexArray);
	glGenBuffers(1, &bo.idIndexArray);
	//por cada buffer
	glBindVertexArray(bo.idArray);
		//actiar buffer
		glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
		// subir por buffer sus datos
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);

		//actiar buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);
		// subir por buffer sus datos
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * obj->indexVertexList.size(), obj->indexVertexList.data(), GL_STATIC_DRAW);

	//guardar bufferObject en mapa
		bufferObjectList[obj->id] = bo;
}

void drawGL(Object* obj)
{
	//Seleccionar malla
	auto model = makeTranslate(obj->pos.x, obj->pos.y, obj->pos.z);

	//acticar buffers
	auto bo = bufferObjectList[obj->id];
	glBindVertexArray(bo.idArray);
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	glPushMatrix();
	glLoadIdentity();
	glMultTransposeMatrixf(model.mat1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));

	glDrawElements(GL_TRIANGLES, obj->indexVertexList.size(), GL_UNSIGNED_INT, nullptr);

	/*
	glBegin(GL_TRIANGLES);
	for (auto p : obj -> Triangulo)
	{
		p = model * p;
		glVertex3f(p.x, p.y, p.z);
	}

	glEnd();
	*/

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

int main(int argc, char** argv)
{
	GLFWwindow* window = initGLFW();
	Object* obj = new Object;
	setupObject(obj);

	Object* obj2 = new Object;
	obj2->pos.x += 0.25f;
	setupObject(obj2);

	while (!glfwWindowShouldClose(window))
	{
		//Check eventos
		glfwPollEvents();
		for (auto obj : objectList) {
			obj->update();
		}
		//Dibujar
			//Limpiar buffers
			glClear(GL_COLOR_BUFFER_BIT);
			//Mandar Triangulos
			for (auto obj : objectList) {
				drawGL(obj);
			}
		//cambiarBuffers
		glfwSwapBuffers(window);
	}

	return 0;
}