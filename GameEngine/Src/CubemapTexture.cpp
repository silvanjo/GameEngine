#include "CubemapTexture.h"

#include <iostream>

#include "stb_image.h"

CubemapTexture::CubemapTexture() 
{

}

CubemapTexture::CubemapTexture(std::vector<std::string>& faces_filepath)
{
	LoadTexture(faces_filepath);
}

CubemapTexture::~CubemapTexture()
{
	
}

void CubemapTexture::LoadTexture(std::vector<std::string>& faces_filepath)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	int width, height, nrChannels;

	// May differ depending on the skybox
	stbi_set_flip_vertically_on_load(0);

	// Read all 6 faces of the cubemap texture
	for (unsigned int i = 0; i < faces_filepath.size(); i++)
	{
		unsigned char* data = stbi_load(faces_filepath.at(i).c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "ERROR::Failed to load Cubemap texture" << std::endl;
		}

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubemapTexture::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubemapTexture::UnBind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}