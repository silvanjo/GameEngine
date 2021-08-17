#pragma once

#include "Mesh.h"
#include "Model.h"

class Renderer
{
public:
	static void DrawElements(Mesh& mesh, Shader& shader);
	static void DrawElements(Model& model, Shader& shader);
	static void DrawArrays(Mesh& mesh, Shader& shader);
};