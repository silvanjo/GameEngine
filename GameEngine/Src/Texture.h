#pragma once

#include <string>
#include <vector>

class Texture{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

	std::string textureType;

public:
	Texture(const std::string& filepath, const std::string& type = "texture_diffuse");
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	const std::string& getTextureType() const;
	const std::string& getFilePath() const;
};