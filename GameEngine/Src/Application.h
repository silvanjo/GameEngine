#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "Mesh.h"
#include "Window.h"
#include "Tile3D.h"
#include "Application.h"
#include "Renderer.h"
#include "Model.h"
#include "Cubemap.h"

#include <map>

enum TEXTURE_TYPES {

	CONTAINER,
	CONTAINER_SPECULAR,
	DESERT,
	GRASS,
	WINDOW

};

class Application
{

public:
	Application();

	void InitScene();

	void DrawScene();

	void Start();

private:
	Window window;
	Camera camera;

	Framebuffer framebuffer;

	std::vector<std::shared_ptr<Shader>> shaders;
	std::vector<std::shared_ptr<Entity>> entities;
	std::map<TEXTURE_TYPES, std::shared_ptr<Texture>> textures;

};