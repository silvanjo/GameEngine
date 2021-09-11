#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>
#include <memory>

#include "Shader.h"
#include "Mesh.h"

class Entity

{
public:
	Entity(glm::vec3 position);

	glm::mat4 model;

	std::vector<std::shared_ptr<Mesh>> meshes;

	unsigned int GetEntityID();

	glm::vec3 GetPosition();
	glm::vec3 GetScale();

	void SetPosition(glm::vec3 position);
	void SetScale(glm::vec3 scale);

	void Move(glm::vec3 dmove);
	void Rotate(float angle, glm::vec3 axis);

	void setModelMatrix(glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 rotAxis);

	virtual void Update(float deltaTime);

protected:
	glm::vec3 position;
	glm::vec3 scale;
	float rotAngle;
	glm::vec3 rotAxis;

private:
	unsigned int ID;
	static unsigned int nextID;

};

