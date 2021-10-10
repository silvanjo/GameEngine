#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

class CubemapTexture
{
public:
	CubemapTexture();
	CubemapTexture(std::vector<std::string>& faces_filepath);
	~CubemapTexture();

	void LoadTexture(std::vector<std::string>& faces_filepath);

	void Bind();
	void UnBind();

private:
	GLuint ID;
};