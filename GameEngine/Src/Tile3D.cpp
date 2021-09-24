#include "Tile3D.h"

Tile3D::Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>& textures) :
	Model(position)
{
	Tile3D::CreateMesh(textures);
}

Tile3D::Tile3D(glm::vec3 position, std::vector<std::shared_ptr<Texture>>&& textures) :
	Model(position)
{
	Tile3D::CreateMesh(textures);
}

void Tile3D::CreateMesh(std::vector<std::shared_ptr<Texture>>& textures) 
{

	std::shared_ptr<Mesh> mesh = std::make_unique<Mesh>();

	mesh->vertices =
	{ //               COORDINATES				 /           NORMALS			/       TEXCOORDS         //
		Vertex{glm::vec3(-1.0f, 1.0f,  0.0f),	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f, 0.0f),	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, 0.0f)	,	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(1.0f, 1.0f,  0.0f)	,	 glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.0f, 1.0f)}
	};

	mesh->indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	mesh->textures = textures;

	mesh->createMesh();

	Model::meshes.push_back(mesh);

}