#include "Material.h"
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/stb_image.h>

Material::Material(std::string textureName, float Ka, float Kd, float Ks) : textureName(textureName), Ka(Ka), Kd(Kd), Ks(Ks)
{
	int channel = 4;
	// cargar datos fichero
	unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &channel, 4);
	//si no hay error
	if (data != nullptr) {
		// copiar datos pixel a vector
		pixels.resize(width * height);		// redimensionar a w*h
		memcpy(pixels.data(), data, width * height * sizeof(pixel_t)); // copiar datos fichero
		stbi_image_free(data);		// borrar datos imagen
	}
	else {
		cout << "ERROR: fichero " << __FILE__ << ":" << __LINE__ << " no encontrado" << endl;
	}
}

void Material::bind(int textureUnit)
{
	// crear identificador textura
	if (textureId == -1) {
		glGenTextures(1, &textureId);
	}

	// activar/bindear textura a unidad activa
	glBindTexture(GL_TEXTURE_2D, textureId);

	// set propiedades filtro imagen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// filtro bilinear default
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// set propiedades repeticion imagen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// repeticion eje x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// repeticion eje y

	// copiar datos a gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
}
