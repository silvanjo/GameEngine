#include "Cube.h"



Cube::Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures) :
	Mesh(position)
{

	Mesh::textures = textures;

	Cube::createMesh();

}

Cube::Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures) :
	Mesh(position)
{

	Mesh::textures = textures;

	Cube::createMesh();

}

void Cube::createMesh() {

	Mesh::createMesh();

}