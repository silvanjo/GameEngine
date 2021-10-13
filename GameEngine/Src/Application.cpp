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
	shaders.push_back(std::make_shared<BaseShader>());
	shaders.push_back(std::make_shared<FramebufferShader>());
	shaders.push_back(std::make_shared<CubemapShader>());

	entities.push_back(std::make_shared<Model>((char*) "Assets/Models/Sphere/Sphere.obj", glm::vec3(2.f, 3.f, -3.f)));
	
	entities.push_back(std::make_shared<Tile3D>(glm::vec3(0.f, 0.f, 0.f), std::vector<std::shared_ptr<Texture>>{std::make_shared<Texture>("Assets/Models/Sphere/diffuse.png")}));

	for (std::shared_ptr<Shader> shader : shaders)
	{
		shader->BindUniformBlock("Matrices", 0);
	}

	bufferProjView.CreateUniformBuffer(2 * sizeof(glm::mat4));
	bufferProjView.BindBufferRange(0, 0, 2 * sizeof(glm::mat4));

	bufferProjView.BufferSubData(0, sizeof(glm::mat4), glm::value_ptr(camera.GetProjection()));
}

void Application::DrawScene()
{
	for (auto& entity : Application::entities)
	{
		Renderer::DrawElements(*entity, *Application::shaders.at(0));
	}
}

void Application::UpdateShader()
{
	bufferProjView.BufferSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera.GetView()));
}

void Application::Start() {

	if (!framebuffer.IsComplete())
		std::cout << "ERROR::Framebuffer is not complete" << std::endl;

	Tile3D framebufferQuad(glm::vec3(0.f, 0.f, 0.f), { });

	InitScene();

	std::vector<std::string> cubemap_faces =
	{
		"Assets/Skybox/Sky/right.jpg",
		"Assets/Skybox/Sky/left.jpg",
		"Assets/Skybox/Sky/top.jpg",
		"Assets/Skybox/Sky/bottom.jpg",
		"Assets/Skybox/Sky/front.jpg",
		"Assets/Skybox/Sky/back.jpg",
	};

	Cubemap cubemap(cubemap_faces);

	float now, deltaTime = 0.f, timeSinceLastTick = 0.f;
	while (!window.windowShouldClose()) {
		camera.Update(window.getWindow(), deltaTime);

		UpdateShader();
		
		now = glfwGetTime();
		deltaTime = now - timeSinceLastTick;
		timeSinceLastTick = now;
		
		window.clear(0.5f, 0.5f, 0.5f, 1.f);

		DrawScene();					
		Renderer::DrawCubemap(cubemap, *shaders.at(2));

		window.swapBuffers();
		window.pollEvents();

	}

}