#include "Cube.h"



Cube::Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures) :
	Model(position)
{

	Cube::createMesh();

}

Cube::Cube(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures) :
	Model(position)
{

	Cube::createMesh();

}

void Cube::createMesh() 
{

}