#pragma once

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#include "Shader.h"
#include "Mesh.h"

#include <vector>

class Model : public Entity
{
public:
	Model(char *path, glm::vec3 position);
	~Model();

public:
	// model data
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<std::shared_ptr<Texture>> texturesLoaded;
	std::string directory;

	void loadModel(const std::string& path);
	void processNode(aiNode *node, const aiScene *scene);
	std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
};