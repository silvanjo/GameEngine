#include "Entity.h"

unsigned int Entity::nextID = 0;

Entity::Entity(glm::vec3 position)
{
	Entity::ID = Entity::nextID;
	Entity::nextID += 1;

	Entity::position = position;
}

unsigned int Entity::getEntityID() {
	return Entity::ID;
}