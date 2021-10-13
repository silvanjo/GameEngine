#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

layout(std140) uniform Matrices
{
	uniform mat4 proj;
	uniform mat4 view;
};

uniform mat4 model;

void main() {

	gl_Position = proj * view * model * vec4(aPos, 1.f);

}


#shader fragment
#version 330 core

uniform vec4 lightColor;

out vec4 FragColor;

void main() {

	FragColor = lightColor;

}
