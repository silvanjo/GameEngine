#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<std::shared_ptr<Texture>>& textures)
{

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	createMesh();

}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<std::shared_ptr<Texture>>&& textures)
{

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	createMesh();

}

void Mesh::createMesh() {

	VAO.Bind();

	VBO.CreateVBO(vertices);
	EBO.CreateEBO(indices);

	VBO.Bind();
	EBO.Bind();

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VAO.Unbind();

}