#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Entity
{
public:
	Entity(glm::vec3 position);

	glm::vec3 position;

	unsigned int getEntityID();

private:
	unsigned int ID;
	static unsigned int nextID;
};

