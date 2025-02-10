#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/InputManager.h"
#include "libprgr/Render.h"
#include "libprgr/Object3D.h"
using namespace libPRGR;

//class Object;
//class Bullet;
//
//GLFWwindow* initGLFW() {
//	if (glfwInit() != GLFW_TRUE) {
//		std::cout << "ERROR" << endl;
//		return nullptr;
//	}
//	else {
//		std::cout << "TODO BIEN" << endl;
//	}
//
//	GLFWwindow* window = glfwCreateWindow(1080, 720, "Ventana1", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//	gladLoadGL(glfwGetProcAddress);
//
//	EventManager::init(window);
//
//	return window;
//}
//
//void deinitGLFW() {
//	glfwTerminate();
//}
//
//
//typedef struct {
//	Vector4f vPos;
//	Vector4f vColor;
//} vertex_t;
//
//typedef struct {
//	unsigned int idArray;		//Identificador de grupos de arrays
//	unsigned int idVertexArray;	//Identificador de datos de vertices
//	unsigned int idIndexArray;	//Identificador de orden de vertices
//}bufferObject;
//
//class Object {
//public:
//	inline static int idCounter = 0;
//	int id;
//	Object() {
//		id = idCounter++;
//		this->pos = { 0, 0, 0, 1 };
//		this->vertexList.push_back({ {0, 0.25, 0, 1}, {1,0,0,1} });
//		this->vertexList.push_back({ {-0.25, -0.25, 0, 1}, {1,0,1,1} });
//		this->vertexList.push_back({ {0.25, -0.25, 0, 1}, {0,0,1,1} });
//		this->indexVertexList = { 0, 1, 2 };
//	}
//
//	virtual void update() {
//		if (EventManager::keyState[GLFW_KEY_LEFT]) {
//			this->pos.x -= 0.001f;
//		}
//
//		if (EventManager::keyState[GLFW_KEY_RIGHT]) {
//			this->pos.x += 0.001f;
//		}
//
//		if (EventManager::keyState[GLFW_KEY_SPACE]) {
//			setUpObject(new Bullet());
//		}
//	}
//
//	Vector4f pos;
//	vector<vertex_t> vertexList;
//	vector<unsigned int> indexVertexList;
//};
//
//class Bullet :public Object {
//public:
//	Bullet() :Object() {}
//
//	virtual void update() override {
//		this->pos.y += 0.001f;
//	}
//};
//
//map<int, bufferObject> bufferObjectList;
//list<Object*> objectList;
//
////void checkEvents(Object* obj) {
////	if (EventManager::keyState[GLFW_KEY_LEFT]) {
////		obj->pos.x -= 0.001f;
////	}
////
////	if (EventManager::keyState[GLFW_KEY_RIGHT]) {
////		obj->pos.x += 0.001f;
////	}
////}
//
//void setUpObject(Object* obj) {
//	objectList.push_back(obj);
//	bufferObject bo;
//
//	//Generar buffers de datos
//	glGenVertexArrays(1, &bo.idArray);
//	glGenBuffers(1, &bo.idVertexArray);
//	glGenBuffers(1, &bo.idIndexArray);
//
//	glBindVertexArray(bo.idArray);
//	//Activar datos buffers
//	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
//	//Subir datos buffer
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);
//	//Activar datos buffers
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);
//	//Subir datos buffer
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_t) * obj->indexVertexList.size(), obj->indexVertexList.data(), GL_STATIC_DRAW);
//
//	//Guardar bufferObject en mapa
//	bufferObjectList[obj->id] = bo;
//}
//
//void drawGL(Object* obj) {
//	//Seleccionar malla
//	auto model = makeTranslate(obj->pos.x, obj->pos.y, obj->pos.z);
//
//	//Activar buffers
//	auto bo = bufferObjectList[obj->id];
//	glBindVertexArray(bo.idArray);
//	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);
//
//	glPushMatrix();
//	glLoadIdentity();
//	glMultTransposeMatrixf(model.mat1);
//
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
//	glEnableClientState(GL_COLOR_ARRAY);
//	glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));
//
//	glDrawElements(GL_TRIANGLES, obj->indexVertexList.size(), GL_UNSIGNED_INT, nullptr);
//
//	/*//Avisar de que vamos a dibujar triangulo
//	glBegin(GL_TRIANGLES);
//	//Crear un vertice en cada punto del triangulo
//	for (auto p : obj->Triangulo) {
//		glVertex3f(p.x, p.y, p.z);
//	}
//	glEnd();*/
//	glPopMatrix();
//	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_COLOR_ARRAY);
//}

int main(int argc, char** argv)
{
	//GLFWwindow* window = initGLFW();
	//Object* obj = new Object();
	//setUpObject(obj);

	//Object* obj2 = new Object();
	//obj2->pos.x += 0.5f;
	//setUpObject(obj2);

	//Object* obj3 = new Object();
	//obj3->pos.x += 0.25f;
	//obj3->pos.y += 0.5f;
	//setUpObject(obj3);

	//while (!glfwWindowShouldClose(window)) {
	//	//Check eventos
	//	glfwPollEvents();
	//	for (auto obj : objectList) {
	//		obj->update();
	//	}
	//	//Dibujar
	//		//Limpiar buffer
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	//Mandar figura a dibujar
	//	for (auto obj : objectList) {
	//		drawGL(obj);
	//	}
	//	//Cambiar buffers
	//	glfwSwapBuffers(window);
	//	;
	//}

	//deinitGLFW();


	//Crear una clase "Render" de tamaño 640 * 480 píxeles, y llamar a su método “initGL”
	Render* rend = new Render(480, 640);
	rend->initGL();

	//Crear una variable "triangulo" de tipo Object3D, y llamar a su método “createTriangle” para que 
	//	almacene los vértices e identificadores de vértices para un triángulo
	
	//Dibujarlo en el buffer(putObject), y mostrar el buffer por ventana(mainLoop)
	
	//Cuando se pulsen las teclas “A” o “D” el triángulo girará acorde con lo indicado en su método
	//	“update”.

	rend->mainLoop();

	return 0;
}