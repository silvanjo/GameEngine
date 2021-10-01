#include "Texture.h"

#include "GL/glew.h"
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string& path, const std::string& type)
	: ID(0), filepath(path), data_image(nullptr), width(0), height(0), BPP(0), textureType(type) {

	stbi_set_flip_vertically_on_load(1);
	data_image = stbi_load(path.c_str(), &width, &height, &BPP, 0);

	if (data_image) {
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLenum format;
		if (BPP == 1)
			format = GL_RED;
		else if (BPP == 3)
			format = GL_RGB;
		else if (BPP == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data_image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		std::cout << "Texture failed to loadt at path: " << path << std::endl;
	}

	stbi_image_free(data_image);
 }

Texture::~Texture() {
	glDeleteTextures(1, &ID);
}

void Texture::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UnBind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

const std::string& Texture::getTextureType() const {
	return this->textureType;
}

const std::string& Texture::getFilePath() const {
	return this->filepath;
}