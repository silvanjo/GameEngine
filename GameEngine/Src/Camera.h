#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "Shader.h"

#include <vector>
#include <memory>


class Camera {
public:
	Camera();
	~Camera();

	void Update(GLFWwindow* window, float deltaTime);
	void ProcessInput(GLFWwindow* window, float deltaTime);

	void SetCameraPosition(const glm::vec3& position);

	glm::mat4& GetView();
	glm::mat4& GetProjection();
	const glm::vec3& GetCameraPos() const;
	const glm::vec3& GetDirection() const;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

private:
	static bool firstMouse;
	static float lastX, lastY;

	glm::mat4 view;
	glm::mat4 proj;

	glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float cameraSpeed;
	
	static float yaw, pitch;
	static float sensitivity;
};