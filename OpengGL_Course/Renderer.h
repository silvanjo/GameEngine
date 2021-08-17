#pragma once

#include "Mesh.h"
#include "Model.h"

class Renderer
{
public:
	static void DrawElements(Entity& model, Shader& shader);
	static void DrawArrays(Entity& mesh, Shader& shader);
};