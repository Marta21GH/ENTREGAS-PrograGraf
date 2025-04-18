#include "Render.h"
#include "EventManager.h"

Render::Render()
{
}

GLFWwindow* Render::initGLFW() {
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "ERROR" << endl;
		return nullptr;
	}

	GLFWwindow* win = glfwCreateWindow(1080, 720, "Ventana1", nullptr, nullptr);
	glfwMakeContextCurrent(win);
	gladLoadGL(glfwGetProcAddress);

	EventManager::init(win);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->window = win;
	return win;
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
	bufferObjectList[obj->id] = bo;
}

void Render::drawGL(Object* obj) {
	//Seleccionar malla
	auto model = obj->computeModelMatrix();
	auto view = cam->computeViewMatrix();
	auto projection = cam->computeProjectionMatrix();

	//Matriz modelo vista proyección (MVP)
	Matrix4x4f MVP = projection * view * model;

	//Activar buffers
	auto bo = bufferObjectList[obj->id];
	glBindVertexArray(bo.idArray);
	glBindBuffer(GL_ARRAY_BUFFER, bo.idVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idIndexArray);

	//activar programa 
	obj->program->use();

	//copiar datos matriz mvp
	obj->program->setUniformData(GLProgram::matrix4, &MVP.matrix[0][0], "MVP");
	obj->program->setUniformData(GLProgram::matrix4, &model.matrix[0][0], "M");

	//set atributo
	obj->program->setAttributeData("vPos", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vPos));
	//obj->program->setAttributeData("vColor", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor));
	obj->program->setAttributeData("vNorm", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vNormal));
	obj->program->setAttributeData("vTextureCoord", 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, vTextureCoord));


	obj->program->setUniformData(GLProgram::vector4, &(light->pos), "lightPos");
	obj->program->setUniformData(GLProgram::vector4, &(light->color), "lightColor");
	//Elegir intensidad según tipo de luz
	switch (light->type) {
		case LightType::DIRECTIONAL: obj->program->setUniformData(GLProgram::floatpoint, &(light->Id), "Ik"); break;
		case LightType::POINT: obj->program->setUniformData(GLProgram::floatpoint, &(light->Is), "Ik"); break;
		default: obj->program->setUniformData(GLProgram::floatpoint, &(light->Ia), "Ik"); break;
	}
	obj->program->setUniformData(GLProgram::floatpoint, &(obj->mat->Ks), "Ks");
	obj->program->setUniformData(GLProgram::floatpoint, &(obj->mat->Kd), "Kd");
	obj->program->setUniformData(GLProgram::integer, &(obj->mat->Ka), "shinny");

	obj->program->setUniformData(GLProgram::vector4, &(cam->pos), "cameraPos");

	//activar textura
	int textureUnit = 0;
	glActiveTexture(GL_TEXTURE0 + textureUnit);	//activar unidad texturado 0
	glBindTexture(GL_TEXTURE_2D, obj->mat->textureID);	//cargar textura en unidad texturado 0
	//activar sampler2D en shader
	obj->program->setUniformData(GLProgram::integer, &(textureUnit), "textureColor");

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
	float timeStep = 0;
	float oldTime = glfwGetTime();
	float newTime = 0;

	while (!glfwWindowShouldClose(this->window)) {
		//actualizar tiempo
		newTime = glfwGetTime();
		timeStep = newTime - oldTime;
		oldTime = newTime;

		//Check eventos
		glfwPollEvents();
		for (auto obj : this->objectList) {
			obj->update(timeStep);
			this->cam->update();
		}
		//Dibujar
			//Limpiar buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Mandar figura a dibujar
		for (auto obj : this->objectList) {
			this->drawGL(obj);
		}
		//Cambiar buffers
		glfwSwapBuffers(window);
	}
}