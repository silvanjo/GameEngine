#include "Shader.h"
#include <fstream>
#include <sstream>

#include <iostream>
#include <GL/glew.h>

Shader::Shader(const std::string& filepath)
	: m_Filepath(filepath), m_RendererID(0) {

	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader() {
	glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error handling

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int errLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errLength);
		char* message = (char*)alloca(errLength * sizeof(char));
		glGetShaderInfoLog(id, errLength, &errLength, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader" << std::endl;
		std::cout << message << std::endl;
	}

	// --------------

	return id;
}

void Shader::Bind() const {
	glUseProgram(m_RendererID);
}

void Shader::UnBind() const {
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string&name, const glm::mat4& matrix) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

unsigned int Shader::GetUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	else
		m_UniformLocationCache[name] = location;
	return location;
}

BaseShader::BaseShader() :
	Shader("Shaders/default.shader")
{

	Shader::Bind();

	// Set Pointlight arguments
	Shader::SetUniform3f("pointLight.position", 2.f, 1.f, 1.f);
	Shader::SetUniform3f("pointLight.color", 1.f, 1.f, 1.f);
	Shader::SetUniform1f("pointLight.a", 0.01f);
	Shader::SetUniform1f("pointLight.b", 0.01f);
	Shader::SetUniform1f("pointLight.ambient", 0.3f);
	Shader::SetUniform1f("pointLight.diffuse", 1.f);
	Shader::SetUniform1f("pointLight.specular", 1.f);

	// Set Direct light arguments
	Shader::SetUniform3f("dirLight.direction", 1.f, -1.f, 0.f);
	Shader::SetUniform1f("dirLight.ambient", 0.3f);
	Shader::SetUniform1f("dirLight.diffuse", 1.f);
	Shader::SetUniform1f("dirLight.specular", 1.f);

	// Set SpotLight arguments
	Shader::SetUniform3f("spotLight.position", 0.f, 1.f, 0.f);
	Shader::SetUniform3f("spotLight.direction", 0.f, -1.f, 0.f);
	Shader::SetUniform1f("spotLight.outerCone", 0.9);
	Shader::SetUniform1f("spotLight.innerCone", 0.95);
	Shader::SetUniform1f("spotLight.ambient", 0.3f);
	Shader::SetUniform1f("spotLight.diffuse", 1.f);
	Shader::SetUniform1f("spotLight.specular", 1.f);

	Shader::UnBind();

}