#pragma once

#include "Mesh.h"

class Cube : public Mesh
{

public:
	Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures);
	Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures);

private:
	void createMesh();

};

