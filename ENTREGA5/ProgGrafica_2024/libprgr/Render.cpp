#include "render.h"
#include "EventManager.h"

Render::Render()
{
}

void Render::initGLFW() {
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "ERROR" << endl;
	}
	else {
		std::cout << "TODO BIEN" << endl;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Ventana1", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	EventManager::init(window);
	glEnable(GL_DEPTH_TEST);

	this->window = window;
}

void Render::deinitGLFW() {
	glfwTerminate();
}

void Render::putObject(Object* obj) {
	objectList.push_back(obj);
	setUpObject(obj);
}

void Render::setUpObject(Object* obj) {
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
	bufferList[obj->ObjectId] = bo;
}

void Render::drawGL(Object* obj) {
	// Calcular matrices
	auto model = obj->computeModelMatrix();
	auto view = cam->lookat();
	auto projection = cam->projection();
	Matrix4x4f MVP = projection * view * model;

	// Activar buffers
	auto bo = bufferList[obj->ObjectId];
	glBindVertexArray(bo.idArray);
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	// Activar shader
	obj->prg->use();

	// Enviar uniforms al shader
	obj->prg->setUniformData(Program::matrix4, &MVP.matrix[0][0], "MVP");
	obj->prg->setUniformData(Program::matrix4, &model.matrix[0][0], "model");
	obj->prg->setUniformData(Program::vector4, &this->light->position, "lightPos");
	obj->prg->setUniformData(Program::vector4, &this->light->color, "lightColor");
	obj->prg->setUniformData(Program::floatpoint, &this->light->ia, "Ka");
	obj->prg->setUniformData(Program::floatpoint, &this->light->id, "Kd");

	// Enviar atributos por vértice
	obj->prg->setAttributeData("vPos", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
	obj->prg->setAttributeData("vColor", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));
	obj->prg->setAttributeData("vNormal", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vNormal));
	obj->prg->setAttributeData("vTextureCoord", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vTextureCoord));

	obj->mat->bind(0); // Usa unidad de textura 0

	int unidad = 0;
	obj->prg->setUniformData(Program::integer, &unidad, "myTexture"); // Asegúrate de que en el shader el sampler se llame igual

	// Dibujar malla
	glDrawElements(GL_TRIANGLES, obj->indexVertexList.size(), GL_UNSIGNED_INT, nullptr);
}

void Render::putCamera(Camera* camj)
{
	this->cam = camj;
}

void Render::putLight(Light* light)
{
	this->light = light;
}

void Render::mainLoop()
{
	while (!glfwWindowShouldClose(this->window)) {
		//Check eventos
		glfwPollEvents();
		for (auto obj : this->objectList) {
			obj->update();
			this->cam->move(0.1);
		}
		//Dibujar
			//Limpiar buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Mandar figura a dibujar
		for (auto obj : this->objectList) {
			this->drawGL(obj);
		}
		//Cambiar buffers
		glfwSwapBuffers(this->window);
	}
}
