#pragma once

#include "Model.h"

class Tile3D : public Model
{
public:
	Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures);
	Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures);

private:
	void CreateMesh(std::vector<std::shared_ptr<Texture>>& textures);
};
