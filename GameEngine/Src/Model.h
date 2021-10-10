#pragma once

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#include "Entity.h"

class Model : public Entity
{
public:
	Model();
	Model(glm::vec3 position);
	Model(char *path, glm::vec3 position);
	~Model();

public:

	void LoadModel(const std::string& path);

protected:
	std::vector<std::shared_ptr<Texture>> texturesLoaded;
	std::string directory;

	void processNode(aiNode *node, const aiScene *scene);
	std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
};