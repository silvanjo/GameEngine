#include "Cubemap.h"

Cubemap::Cubemap()
{

}

Cubemap::Cubemap(std::vector<std::string>& faces_filepath)
{
	CreateCubemap(faces_filepath);
}

Cubemap::~Cubemap()
{

}

void Cubemap::CreateCubemap(std::vector<std::string>& faces_filepath)
{
	cube.LoadModel((char*) "Assets/Models/Cube/Cube.obj");
	texture.LoadTexture(faces_filepath);
}