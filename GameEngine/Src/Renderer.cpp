#include "Renderer.h"


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>


void Renderer::DrawElements(Entity& entity, Shader& shader) {

	std::vector<std::shared_ptr<Mesh>>* meshes = &entity.meshes;

	for (auto& mesh : *meshes)
	{

		for (int i = 0; i < mesh->textures.size(); i++)
			mesh->textures.at(i)->Bind(i);

		shader.Bind();

			shader.SetUniformMat4f("model", entity.model);

			unsigned int numDiffuse = 0;
			unsigned int numSpecular = 0;

			// Biding textures of th emodel
			for (unsigned int i = 0; i < mesh->textures.size(); i++) {
				std::string num;
				std::string type = mesh->textures[i]->getTextureType();

				if (type == "texture_diffuse") {
					num = std::to_string(numDiffuse++);
				}
				else if (type == "texture_specular") {
					num = std::to_string(numSpecular++);
				}

				shader.SetUniform1i("material." + type + num, i);
				mesh->textures[i]->Bind(i);

			}
			// --------------------------------

			mesh->VAO.Bind();

				glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);

			mesh->VAO.Bind();

		shader.UnBind();

	}

	// TODO: Unbinding textures

}

void Renderer::DrawArrays(Entity& mesh, Shader& shader) {

}