#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;

void main()
{
	// Explantion
	TexCoords = aPos;
	vec4 pos = proj * view * vec4(aPos, 1.f);
	// Because z = w the value in the depth buffer will be 1 so the skybox 
	// has maximum depth value and thus will be rendered behind everything else
	gl_Position = pos.xyww;
}

#shader fragment
#version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, TexCoords);
}