#include "ModelLoadScene.h"

void ModelLoadingScene::OnAttach()
{
	float CubeVertices[] = {
		// positions          // normals          // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f,  -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
	};

	lastX = 1600 / 2.0f;
	lastY = 900 / 2.0f;
	deltaTime, lastFrame = 0.0f, 0.0f;
	VertexBuffer vbo(sizeof(CubeVertices), CubeVertices);
	vbo.Bind();
	VertexArray lightVAO;
	lightVAO.Bind();
	VertexBufferLayout lightLayout;
	lightLayout.Push<float>(3);
	lightLayout.Push<float>(3);
	lightLayout.Push<float>(2);
	lightVAO.AddBuffer(vbo, lightLayout);

	Shader lightShader("res/shaders/lighting.shader");

	Shader BpShader("res/shaders/test_vertex.glsl", "res/shaders/test_fragment.glsl");

	Model Backpack("res/models/backpack/backpack.obj");

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	this->lightShader = std::make_unique<Shader>(lightShader);
	this->BpShader = std::make_unique<Shader>(BpShader);
	this->Backpack = std::make_unique<Model>(Backpack);
	this->vbo = std::make_unique<VertexBuffer>(vbo);
	this->lightVAO = std::make_unique<VertexArray>(lightVAO);
	this->camera = std::make_unique<Camera>(camera);
}

void ModelLoadingScene::OnRender(GLFWwindow* window) 
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	ProcessKeyboard(window);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BpShader->use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), 1600.0f / 900.0f, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();

	BpShader->SetMat4("projection", projection);
	BpShader->SetMat4("view", view);
	BpShader->SetVec3("viewPos", camera->Position);
	BpShader->SetVec3("lightPos", lightPos);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	BpShader->SetMat4("model", model);

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(model));
	BpShader->SetMat3("normalMatrix", normalMatrix);
	Backpack->Draw(*BpShader);


	lightVAO->Bind();
	lightShader->use();

	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	lightShader->SetMat4("view", view);
	lightShader->SetMat4("projection", projection);
	lightShader->SetMat4("model", model);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void ModelLoadingScene::ProcessKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		lightPos.y += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		lightPos.y -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		lightPos.x -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		lightPos.x += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		lightPos.z -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		lightPos.z += 0.05f;
}

void ModelLoadingScene::ProcessMouse(GLFWwindow* window, double xPos, double yPos)
{
	if (firstInput)
	{
		lastX = xPos;
		lastY = yPos;
		firstInput = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

void ModelLoadingScene::ProcessScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);

}

void ModelLoadingScene::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

