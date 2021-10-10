#include "Camera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

bool Camera::firstMouse = true;
float Camera::lastX = 0.f;
float Camera::lastY = 0.f;
glm::vec3 Camera::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
float Camera::pitch = 0.f;
float Camera::yaw = -90.f;
float Camera::sensitivity = 0.1f;

Camera::Camera() :
	cameraPos(0.0f, 0.0f, 3.0f),
	cameraUp(0.0f, 1.0f, 0.0f),
	cameraSpeed(2.5f)
{
	proj = glm::perspective(glm::radians(45.f), (float)(1600 / 1600), 0.1f, 100.f);
}

Camera::~Camera() {

}

void Camera::Update(GLFWwindow* window, float deltaTime, std::vector<std::shared_ptr<Shader>>& shaders) {
	for (std::shared_ptr<Shader>& shader : shaders) {

		shader->Bind();

		if(shader->hasProjection)
			shader->SetUniformMat4f("proj", proj);
		
		if(shader->hasView && !(shader->type == ShaderType::CUBEMAP_SHADER))
			shader->SetUniformMat4f("view", view);
		
		// Get rid of the translation part of the view matrix for the CubemapShader
		if (shader->type == ShaderType::CUBEMAP_SHADER)
			shader->SetUniformMat4f("view", glm::mat4(glm::mat3(view)));

		shader->UnBind();
	
	}

	ProcessInput(window, deltaTime);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
}

void Camera::SetCameraPosition(const glm::vec3& position) {
	this->cameraPos = position;
}

glm::mat4& Camera::getView() {
	return this->view;
}

const glm::vec3& Camera::getDirection() const {
	return this->cameraFront;
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	yaw += xoffset * sensitivity;
	pitch += yoffset * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	if (yaw >= 360.f || yaw <= -360.f)
		yaw = 0.f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

const glm::vec3& Camera::getCameraPos() const {
	return this->cameraPos;
}