#include "Application.h"

Application::Application() : 
	window(1600, 1600, "OpenGL")
{
	
}

void Application::Start() {

	Application::shaders.push_back(std::make_shared<BaseShader>());

	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::CONTAINER, std::make_shared<Texture>("Textures/container2.png", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::CONTAINER_SPECULAR, std::make_shared<Texture>("Textures/container2_specular.png", "texture_specular")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::DESERT, std::make_shared<Texture>("Textures/desert.jpg", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::GRASS, std::make_shared<Texture>("Textures/grass.png", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::WINDOW, std::make_shared<Texture>("Textures/blending_transparent_window.png", "texture_diffuse")));
	
	Tile3D desertTile(glm::vec3(0.f, 0.f, 0.f),

		std::vector<std::shared_ptr<Texture>>
		{
			Application::textures[TEXTURE_TYPES::DESERT]
		}

	);

	float now, deltaTime, timeSinceLastTick = 0.f;
	while (!window.windowShouldClose()) {

		now = glfwGetTime();
		deltaTime = now - timeSinceLastTick;
		timeSinceLastTick = now;

		camera.Update(window.getWindow(), deltaTime, shaders);

		window.clear(0.5f, 0.5f, 0.5f, 1.f);

		// Drawing

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {

				desertTile.SetPosition(glm::vec3((float) 2 * i, -2.f, (float) 2 * j));

				Renderer::DrawElements(desertTile, *Application::shaders.at(0));

			}
		}
		
		
		for (auto& entity : Application::entities)
		{

			Renderer::DrawElements(*entity, *Application::shaders.at(0));

		}

		// ---------------

		window.swapBuffers();
		window.pollEvents();

	}

}