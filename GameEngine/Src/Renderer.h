#pragma once

#include "Mesh.h"
#include "Model.h"
#include "Framebuffer.h"

class Renderer
{
public:
	static void DrawElements(Entity& model, Shader& shader);
	static void DrawArrays(Entity& model, Shader& shader);
};