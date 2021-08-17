#include "Mesh.h"

#include <iostream>

Mesh::Mesh(glm::vec3 position) :
	Entity(position)
{
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<std::shared_ptr<Texture>>& textures, glm::vec3 position) : 
	Entity(position)
{

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;
	
	createMesh();

}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<std::shared_ptr<Texture>>&& textures, glm::vec3 position) :
	Entity(position)
{

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	createMesh();

}

void Mesh::createMesh() {

	VAO.Bind();

	VBO VBO(vertices);

	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VAO.Unbind();

}