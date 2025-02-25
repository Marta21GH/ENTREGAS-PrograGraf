#include "render.h"
#include "EventManager.h"

Render::Render()
{
}

GLFWwindow* Render::initGLFW() {
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "ERROR" << endl;
		return nullptr;
	}
	else {
		std::cout << "TODO BIEN" << endl;
	}

	GLFWwindow* window = glfwCreateWindow(1080, 720, "Ventana1", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	EventManager::init(window);
	glEnable(GL_DEPTH_TEST);

	return window;
}

void Render::deinitGLFW() {
	glfwTerminate();
}

void Render::setUpObject(Object* obj) {
	objectList.push_back(obj);
	bufferObject bo;

	//Generar buffers de datos
	glGenVertexArrays(1, &bo.idArray);
	glGenBuffers(1, &bo.idVertexArray);
	glGenBuffers(1, &bo.idIndexArray);

	glBindVertexArray(bo.idArray);
	//Activar datos buffers
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	//Subir datos buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);
	//Activar datos buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);
	//Subir datos buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_t) * obj->indexVertexList.size(), obj->indexVertexList.data(), GL_STATIC_DRAW);

	//Guardar bufferObject en mapa
	bufferObjectList[obj->ObjectId] = bo;
}

void Render::drawGL(Object* obj) {
	//Seleccionar malla
	auto model = obj->computeModelMatrix();
	auto view = cam->computeViewMatrix();
	auto projection = cam->computeProjectionMatrix();

	//Matriz modelo vista proyección (MVP)
	Matrix4x4f MVP = projection * view * model;

	//Activar buffers
	auto bo = bufferObjectList[obj->ObjectId];
	glBindVertexArray(bo.idArray);
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	glPushMatrix();
	glLoadIdentity();
	glMultTransposeMatrixf(&MVP.matrix[0][0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));

	glDrawElements(GL_TRIANGLES, obj->indexVertexList.size(), GL_UNSIGNED_INT, nullptr);

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
