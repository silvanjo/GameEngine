#pragma once

#include "Mesh.h"

class Tile3D : public Mesh
{
public:
	Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures);
	Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures);

	void createMesh();
};
