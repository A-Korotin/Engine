#pragma once
#include "Scene.h"
#include "Model.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>


class ModelLoadingScene : public Scene
{
private:
	std::unique_ptr<Shader> lightShader;
	std::unique_ptr<Shader> BpShader;
	std::unique_ptr<Model> Backpack;
	std::unique_ptr<VertexBuffer> vbo;
	std::unique_ptr<VertexArray> lightVAO;
	std::unique_ptr<Camera> camera;
	float lastX, lastY, deltaTime, lastFrame;
	bool firstInput = 1;
	glm::vec3 lightPos = glm::vec3(1.0f, 5.0f, 3.0f);

public:
	void OnAttach() override;

	void OnRender(GLFWwindow* window) override;

	void ProcessKeyboard(GLFWwindow* window) override;

	void ProcessMouse(GLFWwindow* window, double xPos, double yPos) override;
	
	void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset) override;

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height) override;
};
