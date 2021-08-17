#include "Renderer.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void Renderer::DrawElements(Mesh& mesh, Shader& shader) {
	
	for (int i = 0; i < mesh.textures.size(); i++)
		mesh.textures.at(i)->Bind(i);

	shader.Bind();

		glm::mat4 model = glm::translate(glm::mat4(1.f), mesh.position);
		shader.SetUniformMat4f("model", model);

		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;

		// Biding textures of th emodel
		for (unsigned int i = 0; i < mesh.textures.size(); i++) {
			std::string num;
			std::string type = mesh.textures[i]->getTextureType();

			if (type == "texture_diffuse") {
				num = std::to_string(numDiffuse++);
			}
			else if (type == "texture_specular") {
				num = std::to_string(numSpecular++);
			}

			shader.SetUniform1i("material." + type + num, i);
			mesh.textures[i]->Bind(i);

		}
		// --------------------------------

		mesh.VAO.Bind();

			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);

		mesh.VAO.Bind();

	shader.UnBind();

	// TODO: Unbinding textures

}

void Renderer::DrawElements(Model& model, Shader& shader) {

	std::vector<std::shared_ptr<Mesh>>* meshes = &model.meshes;
	for (auto& mesh : *meshes)
	{

		for (int i = 0; i < mesh->textures.size(); i++)
			mesh->textures.at(i)->Bind(i);

		shader.Bind();

			glm::mat4 model = glm::translate(glm::mat4(1.f), mesh->position);
			shader.SetUniformMat4f("model", model);

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

void Renderer::DrawArrays(Mesh& mesh, Shader& shader) {

}