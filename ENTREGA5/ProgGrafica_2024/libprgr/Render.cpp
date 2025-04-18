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
	//Seleccionar malla
	auto model = obj->computeModelMatrix();
	auto view = cam->lookat();
	auto projection = cam->projection();

	//Matriz modelo vista proyección (MVP)
	Matrix4x4f MVP = projection * view * model;

	//Activar buffers
	auto bo = bufferList[obj->ObjectId];
	glBindVertexArray(bo.idArray);
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	//activar programa 
	obj->prg->use();

	//copiar datos matriz mvp
	obj->prg->setUniformData(Program::matrix4, &MVP.matrix[0][0], "MVP");
	obj->prg->setUniformData(Program::matrix4, &model.matrix[0][0], "M");

	//set atributo
	obj->prg->setAttributeData("vPos", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
	obj->prg->setAttributeData("vColor", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));
	obj->prg->setAttributeData("vNorm", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vNormal));
	obj->prg->setAttributeData("vTextureCoord", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vTextureCoord));


	obj->prg->setUniformData(Program::vector4, &(light->position), "lightPos");
	obj->prg->setUniformData(Program::vector4, &(light->color), "lightColor");
	obj->prg->setUniformData(Program::floatpoint, &(light->ia), "Ik");
	obj->prg->setUniformData(Program::floatpoint, &(obj->mat->Ks), "Ks");
	obj->prg->setUniformData(Program::floatpoint, &(obj->mat->Kd), "Kd");
	obj->prg->setUniformData(Program::integer, &(obj->mat->Ka), "shinny");

	obj->prg->setUniformData(Program::vector4, &(cam->pos), "cameraPos");

	//activar textura
	int textureUnit = 0;
	glActiveTexture(GL_TEXTURE0 + textureUnit);	//activar unidad texturado 0
	glBindTexture(GL_TEXTURE_2D, obj->mat->textureId);	//cargar textura en unidad texturado 0
	//activar sampler2D en shader
	obj->prg->setUniformData(Program::integer, &(textureUnit), "textureColor");

	glDrawElements(GL_TRIANGLES, obj->indexVertexList.size(), GL_UNSIGNED_INT, nullptr);

	/*glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);*/
	//// Calcular matrices
	//auto model = obj->computeModelMatrix();
	//auto view = cam->lookat();
	//auto projection = cam->projection();
	//Matrix4x4f MVP = projection * view * model;

	//// Activar buffers
	//auto bo = bufferList[obj->ObjectId];
	//glBindVertexArray(bo.idArray);
	//glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	//// Activar shader
	//obj->prg->use();

	////Enviar datos matrices
	//obj->prg->setUniformData(Program::matrix4, &MVP.matrix[0][0], "MVP");
	//obj->prg->setUniformData(Program::matrix4, &model.matrix[0][0], "M");

	//// Enviar atributos
	//obj->prg->setAttributeData("vPos", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
	////obj->prg->setAttributeData("vColor", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));
	//obj->prg->setAttributeData("vNorm", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vNormal));
	//obj->prg->setAttributeData("vTextureCoord", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vTextureCoord));

	//// Enviar uniforms 
	////Luz:
	//obj->prg->setUniformData(Program::vector4, &this->light->position, "lightPos");
	//obj->prg->setUniformData(Program::vector4, &this->light->color, "lightColor");
	//obj->prg->setUniformData(Program::integer, &(this->light->type), "lightType");
	//obj->prg->setUniformData(Program::vector4, &(this->light->direction), "lightDirection");
	//obj->prg->setUniformData(Program::floatpoint, &this->light->ia, "Ik");
	////Material:
	//obj->prg->setUniformData(Program::floatpoint, &obj->mat->Kd, "Kd");
	//obj->prg->setUniformData(Program::floatpoint, &obj->mat->Ks, "Ks");
	//obj->prg->setUniformData(Program::floatpoint, &obj->mat->Ka, "shinny");

	////obj->prg->setUniformData(Program::vector4, &(this->cam->pos), "cameraPos");

	//obj->mat->bind(0); // Usa unidad de textura 0

	//int unidad = 0;
	//obj->prg->setUniformData(Program::integer, &unidad, "textureColor"); // Aseg�rate de que en el shader el sampler se llame igual

	//// Dibujar malla
	//glDrawElements(GL_TRIANGLES, obj->indexVertexList.size(), GL_UNSIGNED_INT, nullptr);
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
