#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

#include "Shader.h"
#include "Mesh.h"

class Entity
{
public:
	Entity(glm::vec3 position);

	glm::vec3 position;
	std::vector<std::shared_ptr<Mesh>> meshes;

	unsigned int getEntityID();

private:
	unsigned int ID;
	static unsigned int nextID;
};

