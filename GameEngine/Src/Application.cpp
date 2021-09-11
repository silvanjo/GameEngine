#include "Application.h"
#include "Framebuffer.h"

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
	
	Tile3D grassTile(glm::vec3(0.f, -1.75f, 0.f),

		std::vector<std::shared_ptr<Texture>>
		{
			Application::textures[TEXTURE_TYPES::GRASS]
		}

	);
	grassTile.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	grassTile.Rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
	std::vector<glm::vec2> grassPosition;

	for (int i = 0; i < 10; i++) {

		grassPosition.push_back({ ((float)(rand() % 10) + (float)(rand() % 10) / 10), ((float)(rand() % 10) + (float)(rand() % 10) / 10) });

	}

	Tile3D windowTile(glm::vec3(0.f, 0.f, 0.f),

		std::vector<std::shared_ptr<Texture>>
		{
				Application::textures[TEXTURE_TYPES::WINDOW]
		}

	);
	windowTile.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	windowTile.Rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
	std::vector<glm::vec2> windowPosition;

	for (int i = 0; i < 10; i++) {

		windowPosition.push_back({ ((float)(rand() % 10) + (float)(rand() % 10) / 10), ((float)(rand() % 10) + (float)(rand() % 10) / 10) });

	}

	Framebuffer framebuffer(1600, 1600);
	framebuffer.Bind();
	if (!framebuffer.Complete())
		std::cout << "ERROR::Framebuffer not complete" << std::endl;
	framebuffer.Unbind();

	Application::entities.push_back(std::make_shared<Model>((char*) "Models/backpack/backpack.obj", glm::vec3(2.f, 3.f, -3.f)));

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

			grassTile.SetPosition(glm::vec3(grassPosition.at(i).x, -1.75f, grassPosition.at(i).y));
			Renderer::DrawElements(grassTile, *Application::shaders.at(0));

			windowTile.SetPosition(glm::vec3(windowPosition.at(i).x, -1.5f, windowPosition.at(i).y));
			Renderer::DrawElements(windowTile, *Application::shaders.at(0));

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