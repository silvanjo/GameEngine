#include "Texture.h"

#include "GL/glew.h"
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string& path, const std::string& type)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), textureType(type) {

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

	if (m_LocalBuffer) {
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLenum format;
		if (m_BPP == 1)
			format = GL_RED;
		else if (m_BPP == 3)
			format = GL_RGB;
		else if (m_BPP == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		std::cout << "Texture failed to loadt at path: " << path << std::endl;
	}

	stbi_image_free(m_LocalBuffer);
 }

Texture::~Texture() {
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::UnBind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

const std::string& Texture::getTextureType() const {
	return this->textureType;
}

const std::string& Texture::getFilePath() const {
	return this->m_FilePath;
}