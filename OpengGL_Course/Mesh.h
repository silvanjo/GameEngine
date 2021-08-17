#pragma once

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Entity.h"

#include <memory>

class Mesh : public Entity
{
public:
	Mesh(glm::vec3 position);
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<std::shared_ptr<Texture>>& textures, glm::vec3 position);
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<std::shared_ptr<Texture>>&& textures, glm::vec3 position);

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<std::shared_ptr<Texture>> textures;

	VAO VAO;

protected:
	void createMesh();
};