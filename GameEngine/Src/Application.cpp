#include "Application.h"
#include "Framebuffer.h"

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 1600

Application::Application() : 
	window(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL"),
	framebuffer(SCREEN_WIDTH, SCREEN_HEIGHT)
{
	
}

void Application::InitScene()
{
	Application::shaders.push_back(std::make_shared<BaseShader>());
	Application::shaders.push_back(std::make_shared<FramebufferShader>());

	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::CONTAINER, std::make_shared<Texture>("Textures/container2.png", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::CONTAINER_SPECULAR, std::make_shared<Texture>("Textures/container2_specular.png", "texture_specular")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::DESERT, std::make_shared<Texture>("Textures/desert.jpg", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::GRASS, std::make_shared<Texture>("Textures/grass.png", "texture_diffuse")));
	Application::textures.insert(std::pair<TEXTURE_TYPES, std::shared_ptr<Texture>>(TEXTURE_TYPES::WINDOW, std::make_shared<Texture>("Textures/blending_transparent_window.png", "texture_diffuse")));

	Application::entities.push_back(std::make_shared<Model>((char*) "Models/backpack/backpack.obj", glm::vec3(2.f, 3.f, -3.f)));
	Application::entities.push_back(std::make_shared<Tile3D>(glm::vec3(1.f, 1.f, 1.f), std::vector<std::shared_ptr<Texture>>{ textures[TEXTURE_TYPES::CONTAINER] }));
	Application::entities.push_back(std::make_shared<Tile3D>(glm::vec3(4.f, 0.f, 0.f), std::vector<std::shared_ptr<Texture>>{ textures[TEXTURE_TYPES::CONTAINER] }));
	Application::entities.push_back(std::make_shared<Tile3D>(glm::vec3(1.f, 0.f, 1.f), std::vector<std::shared_ptr<Texture>>{ textures[TEXTURE_TYPES::CONTAINER] }));
	Application::entities.push_back(std::make_shared<Tile3D>(glm::vec3(0.f, 1.f, 0.f), std::vector<std::shared_ptr<Texture>>{ textures[TEXTURE_TYPES::CONTAINER] }));

}

void Application::DrawScene()
{
	for (auto& entity : Application::entities)
	{
		Renderer::DrawElements(*entity, *Application::shaders.at(0));
	}
}

void Application::Start() {

	if (!framebuffer.IsComplete())
		std::cout << "ERROR::Framebuffer is not complete" << std::endl;
	Tile3D framebufferQuad(glm::vec3(0.f, 0.f, 0.f), { });

	InitScene();

	std::vector<std::string> cubemap_faces =
	{
		"Skybox/Sky/right.jpg",
		"Skybox/Sky/left.jpg",
		"Skybox/Sky/top.jpg",
		"Skybox/Sky/bottom.jpg",
		"Skybox/Sky/front.jpg",
		"Skybox/Sky/back.jpg",
	};

	Cubemap cubemap(cubemap_faces);

	float now, deltaTime = 0.f, timeSinceLastTick = 0.f;
	while (!window.windowShouldClose()) {
		camera.Update(window.getWindow(), deltaTime, shaders);
		
		now = glfwGetTime();
		deltaTime = now - timeSinceLastTick;
		timeSinceLastTick = now;
		
		window.clear(0.f, 0.f, 0.f, 1.f);

		DrawScene();						

		window.swapBuffers();
		window.pollEvents();

	}

}