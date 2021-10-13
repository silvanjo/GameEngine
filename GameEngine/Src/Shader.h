#pragma once

#include <glm.hpp>

#include <string>
#include <unordered_map>

enum class ShaderType
{
	SHADER,
	BASE_SHADER,
	FRAMEBUFFER_SHADER,
	CUBEMAP_SHADER
};

struct ShaderProgramSource {
	std::string VertexSource, FragmentSource;
};

class Shader 
{
private:
	std::string filepath;
	unsigned int ID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	virtual ~Shader();

	void Bind() const;
	void UnBind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

	void BindUniformBlock(const std::string& block_name, unsigned int binding_point);

	ShaderType type;

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int GetUniformLocation(const std::string& name);
};

class BaseShader : public Shader 
{
public:
	BaseShader();
};

class FramebufferShader : public Shader
{
public:
	FramebufferShader();
};

class CubemapShader : public Shader
{
public:
	CubemapShader();
};