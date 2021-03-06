#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "Window.h"
#include "Tile3D.h"
#include "Renderer.h"
#include "CubemapTexture.h"
#include "UniformBuffer.h"

#include <map>

class Application
{
public:
	Application();

	void InitScene();

	void DrawScene();

	void UpdateShader();

	void Start();

private:
	Window window;
	Camera camera;

	Framebuffer framebuffer;

	UniformBuffer bufferProjView;

	std::vector<std::shared_ptr<Shader>> shaders;
	std::vector<std::shared_ptr<Entity>> entities;
};