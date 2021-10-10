#pragma once

#include "CubemapTexture.h"
#include "Model.h"

class Cubemap
{
public:
	Cubemap();
	Cubemap(std::vector<std::string>& faces_filepath);
	~Cubemap();

	void CreateCubemap(std::vector<std::string>& faces_filepath);

	CubemapTexture texture;
	Model cube;
};