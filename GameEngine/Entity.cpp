#include "Entity.h"

unsigned int Entity::nextID = 0;

Entity::Entity(glm::vec3 position)
{
	Entity::ID = Entity::nextID;
	Entity::nextID += 1;

	Entity::position = position;
	Entity::scale = glm::vec3(1.f);
	Entity::rotAngle = 0.f;
	Entity::rotAxis = glm::vec3(1.f);

	Entity::model = glm::translate(glm::mat4(1.f), position);

	Entity::setModelMatrix(Entity::position, Entity::scale, Entity::rotAngle, Entity::rotAxis);
}

unsigned int Entity::GetEntityID() {
	return Entity::ID;
}

glm::vec3 Entity::GetPosition() {
	return Entity::position;
}

glm::vec3 Entity::GetScale() {
	return Entity::scale;
}

void Entity::SetPosition(glm::vec3 position) {
	Entity::position = position;

	Entity::setModelMatrix(Entity::position, Entity::scale, Entity::rotAngle, Entity::rotAxis);
}

void Entity::SetScale(glm::vec3 scale) {
	Entity::scale = scale;

	Entity::setModelMatrix(Entity::position, Entity::scale, Entity::rotAngle, Entity::rotAxis);
}

void Entity::Move(glm::vec3 dmove) {
	Entity::position += dmove;

	Entity::setModelMatrix(Entity::position, Entity::scale, Entity::rotAngle, Entity::rotAxis);
}

void Entity::Rotate(float angle, glm::vec3 axis) {
	Entity::rotAngle = angle;
	Entity::rotAxis = axis;

	Entity::setModelMatrix(Entity::position, Entity::scale, Entity::rotAngle, Entity::rotAxis);
}

void Entity::setModelMatrix(glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 rotAxis) {
	Entity::model = glm::mat4(1.f);
	Entity::model = glm::translate(Entity::model, position);
	Entity::model = glm::rotate(Entity::model, glm::radians(angle), rotAxis);
	Entity::model = glm::scale(Entity::model, scale);
}

void Entity::Update(float deltaTime) {
	// TODO
}