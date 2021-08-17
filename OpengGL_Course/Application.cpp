#include "Application.h"

Application::Application() 
	: window(1600, 1600, "OpenGL"),
	backpack((char*) "Models/backpack/backpack.obj", glm::vec3(2.f, 2.f, 2.f))
{
	
}

void Application::Start() {

	Application::shaders.push_back(std::make_shared<BaseShader>());

	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::CONTAINER, std::make_shared<Texture>("Textures/container2.png", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::CONTAINER_SPECULAR, std::make_shared<Texture>("Textures/container2_specular.png", "texture_specular")));

	Application::entities.push_back(std::make_shared<Tile3D>(glm::vec3(0.f, -1.f, 0.f), 
		
		std::vector<std::shared_ptr<Texture>> {

			Application::textures[TEXTURE_TYPES::CONTAINER],
			Application::textures[TEXTURE_TYPES::CONTAINER_SPECULAR]

		}

	));


	Application::entities.push_back(std::make_shared<Tile3D>(glm::vec3(0.f, -1.5f, 0.f),

		std::vector<std::shared_ptr<Texture>> {

		Application::textures[TEXTURE_TYPES::CONTAINER],
			Application::textures[TEXTURE_TYPES::CONTAINER_SPECULAR]

	}

	));

	float now, deltaTime, timeSinceLastTick = 0.f;
	while (!window.windowShouldClose()) {

		now = glfwGetTime();
		deltaTime = now - timeSinceLastTick;
		timeSinceLastTick = now;

		camera.Update(window.getWindow(), deltaTime, shaders);

		window.clear(0.5f, 0.5f, 0.5f, 1.f);

		// Drawing

		for (auto& entity : Application::entities)
		{

			Renderer::DrawElements(*entity, *Application::shaders.at(0));

		}

		Renderer::DrawElements(Application::backpack, *Application::shaders.at(0));

		// ---------------

		window.swapBuffers();
		window.pollEvents();

	}

}