#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

layout(std140) uniform Matrices
{
	uniform mat4 proj;
	uniform mat4 view;
};

void main()
{
	// When a cube is centered at position (0,0,0) the position vector of the vertices are also direction vectors from the origen.
	// The direction can be used to determine the texture value at that specific cube position
	TexCoords = aPos;

	// Remove translation part of view matrix
	// Note: Very inefficent to do thsi in the vertex shader!
	mat4 viewNoTranslate = mat4(mat3(view));

	vec4 pos = proj * viewNoTranslate * vec4(aPos, 1.f);

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