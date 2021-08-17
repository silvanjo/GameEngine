#include "Tile3D.h"

Tile3D::Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures) :
	Mesh(position)
{

	Mesh::textures = textures;

	Tile3D::createMesh();

}

Tile3D::Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures) :
	Mesh(position)
{

	Mesh::textures = textures;

	Tile3D::createMesh();

}

void Tile3D::createMesh() {

	Mesh::vertices =
	{ //               COORDINATES				 /           NORMALS			/       TEXCOORDS         //
		Vertex{glm::vec3(-1.0f, 0.0f,  1.0f),	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-1.0f, 0.0f, -1.0f),	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f, -1.0f)	,	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f,  1.0f)	,	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.0f, 0.0f)}
	};

	Mesh::indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	Mesh::createMesh();

}