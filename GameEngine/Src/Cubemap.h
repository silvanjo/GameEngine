#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

class Cubemap
{
public:
	Cubemap(std::vector<std::string>& faces_filepath);
	~Cubemap();

private:
	GLuint ID;

};