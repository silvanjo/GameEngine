#pragma once

#include "Model.h"

class Cube : public Model
{

public:
	Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures);
	Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures);

private:
	void createMesh();

};

