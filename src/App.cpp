#include "CorePCH.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;
static float lastX = 400.0f, lastY = 300.0f;
static bool firstInput = true;

static bool flash = 0;
static double lastFlash = 0.0f;


void fbsc(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		if (glfwGetTime() - lastFlash > 0.3)
		{
			flash = !flash;
			lastFlash = glfwGetTime();
		}
	}

}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffet, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

int main(int argc, const char* argv)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1600, 900, "Application", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, fbsc);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	float vertices[] = {
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

#if(0)
	unsigned int indices[]{
		0, 1, 3,
		1, 2, 3
	};
#endif

	VertexArray vao;
	vao.Bind();

	VertexBuffer vbo(sizeof(vertices), vertices);
	vbo.Bind();

	VertexBufferLayout layout;

	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	vao.AddBuffer(vbo, layout);
#if(0)
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif

	VertexArray lightVAO;
	lightVAO.Bind();
	VertexBufferLayout lightLayout;
	lightLayout.Push<float>(3);
	lightLayout.Push<float>(3);
	lightLayout.Push<float>(2);
	lightVAO.AddBuffer(vbo, lightLayout);


	Shader mainShader("res/shaders/shaders.shader");
	Shader lighingShader("res/shaders/lighting.shader");
	Texture texture("res/textures/container2.png");
	Texture border("res/textures/container2_specular.png");

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};



	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f,-3.3f,-4.0f),
		glm::vec3(-4.0f,2.0f,-12.0f),
		glm::vec3(0.0f, 0.0f,-3.0f)
	};
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.f, 0.f, abs(sin(glfwGetTime() / 4))/5, 1.0f);
		glm::vec3 lightPos(4*sin(glfwGetTime()), 4*cos(glfwGetTime()), 10*cos(glfwGetTime()));
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		mainShader.use();
		texture.Bind();
		border.Bind(1);

		glm::vec3 lightColor(1.0f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.4f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.1f);

		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 900.0f, 0.1f, 100.f);
		mainShader.SetMat4("view", view);
		mainShader.SetMat4("projection", projection);
		mainShader.SetVec3("viewPos", camera.Position);
		mainShader.SetInt("material.diffuse", 0);
		mainShader.SetInt("material.specular", 1);
		mainShader.SetFloat("material.shininess", 32.0f);

		mainShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		mainShader.SetVec3("dirLight.ambient", ambientColor);
		mainShader.SetVec3("dirLight.diffuse",diffuseColor);
		mainShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		for (int i = 0; i < 4; i++)
		{
			mainShader.SetVec3(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLightPositions[i]);
			mainShader.SetFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), 1.0f);
			mainShader.SetFloat(("pointLights[" + std::to_string(i) + "].linearr").c_str(), 0.09f);
			mainShader.SetFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), 0.032f);
			mainShader.SetVec3(("pointLights[" + std::to_string(i) + "].ambient").c_str(), ambientColor);
			mainShader.SetVec3(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), 0.8f, 0.8f, 0.8f);
			mainShader.SetVec3(("pointLights[" + std::to_string(i) + "].specular").c_str(), 1.0f, 1.0f, 1.0f);
		}

		mainShader.SetVec3("spotLight.position", camera.Position);
		mainShader.SetVec3("spotLight.direction", camera.Front);
		mainShader.SetFloat("spotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
		mainShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.f)));
		mainShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		mainShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		mainShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		mainShader.SetFloat("spotLight.constant", 1.0f);
		mainShader.SetFloat("spotLight.linearr", 0.09f);
		mainShader.SetFloat("spotLight.quadratic", 0.032f);

		mainShader.SetBool("flash", flash);

		/*
		//mainShader.SetVec3("light.position", lightPos);
		mainShader.SetVec3("light.ambient", ambientColor);
		mainShader.SetVec3("light.diffuse", diffuseColor);
		mainShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
		mainShader.SetFloat("light.constant", 1.0f);
		mainShader.SetFloat("light.linearr", 0.014f);
		mainShader.SetFloat("light.quadratic", 0.0007f);
		mainShader.SetVec3("light.position", camera.Position);
		mainShader.SetVec3("light.direction", camera.Front);
		mainShader.SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		mainShader.SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		*/

#if(0)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#endif
		vao.Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		mainShader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		}

	
		lighingShader.use();
		lightVAO.Bind();

		for (int i = 0; i < 4; i++)
		{
			glm::mat4 modelN(1.0f);
			modelN = glm::translate(modelN, pointLightPositions[i]);
			modelN = glm::scale(modelN, glm::vec3(0.2f));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			lighingShader.SetMat4("view", view);
			lighingShader.SetMat4("projection", projection);
			lighingShader.SetMat4("model", modelN);
		}

		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}