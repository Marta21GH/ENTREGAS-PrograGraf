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
	auto model = obj->computeModelMatrix();
	auto view = cam->lookat();
	auto projection = cam->projection();
	Matrix4x4f MVP = projection * view * model;

	auto bo = bufferList[obj->ObjectId];
	glBindVertexArray(bo.idArray);
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	obj->prg->use();
	obj->prg->setUniformData(Program::matrix4, &MVP.matrix[0][0], "MVP");
	obj->prg->setUniformData(Program::matrix4, &model.matrix[0][0], "M");

	obj->prg->setAttributeData("vPos", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
	obj->prg->setAttributeData("vNorm", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vNormal));
	obj->prg->setAttributeData("vTextureCoord", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vTextureCoord));
	// obj->prg->setAttributeData("vColor", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));

	obj->prg->setUniformData(Program::vector4, &(light->position), "lightPos");
	obj->prg->setUniformData(Program::vector4, &(light->color), "lightColor");

	switch (light->type) {
	case LightType::DIRECTIONAL: obj->prg->setUniformData(Program::floatpoint, &(light->id), "Ik"); break;
	case LightType::POINT:       obj->prg->setUniformData(Program::floatpoint, &(light->is), "Ik"); break;
	default:                     obj->prg->setUniformData(Program::floatpoint, &(light->ia), "Ik"); break;
	}

	obj->prg->setUniformData(Program::floatpoint, &(obj->mat->Ks), "Ks");
	obj->prg->setUniformData(Program::floatpoint, &(obj->mat->Kd), "Kd");
	obj->prg->setUniformData(Program::integer, &(obj->mat->Ka), "shinny");
	obj->prg->setUniformData(Program::vector4, &(cam->pos), "cameraPos");

	int textureUnit = 0;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, obj->mat->textureId);
	obj->prg->setUniformData(Program::integer, &(textureUnit), "textureColor");

	std::cout << "Draw object ID " << obj->ObjectId << " | indices: " << obj->indexVertexList.size() << std::endl;

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

std::vector<Object*> Render::getAllObjects(Render* r) {
	std::vector<Object*> todos;
	for (auto& obj : r->objectList) {
		todos.push_back(obj);
	}
	return todos;
}
