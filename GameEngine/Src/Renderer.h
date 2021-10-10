#pragma once

#include "Framebuffer.h"
#include "Cubemap.h"

class Renderer
{
public:
	static void DrawElements(Entity& model, Shader& shader);
	static void DrawArrays(Entity& model, Shader& shader);
	static void DrawCubemap(Cubemap& cubemap, Shader& shader);
};