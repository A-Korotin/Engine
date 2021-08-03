#include "CorePCH.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "BasicShapes.h"
#include <map>


static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;
static float lastX = 400.0f, lastY = 300.0f;
static bool firstInput = true;


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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	VertexArray vao;
	vao.Bind();

	VertexBuffer vbo(sizeof(CubeVertices), CubeVertices);
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


	VertexArray quadVAO;
	quadVAO.Bind();

	VertexBuffer quadVBO(sizeof(quadVertecies), quadVertecies);
	quadVBO.Bind();

	VertexBufferLayout quadLayout;
	quadLayout.Push<float>(3);
	quadLayout.Push<float>(2);
	quadVAO.AddBuffer(quadVBO, quadLayout);

	Shader mainShader("res/shaders/main_blending_vertex.glsl", "res/shaders/main_blending_fragment.glsl");
	Shader quadShader("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");
	
	tex::Texture redWindow("res/textures/blending_transparent_window.png");
	tex::Texture mainTexture("res/textures/gray_texture.jpg");
	tex::Texture grass("res/textures/grass.png");


	glm::vec3 CubePositions[] = {
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(2.0f, 0.0f, -1.0f)
	};


	std::vector<glm::vec3> vegetation{ glm::vec3(-1.5f, 0.0f, -0.48f), glm::vec3(1.5f, 0.0f, 0.51f), glm::vec3(0.0f, 0.0f, 0.7f),
									   glm::vec3(-0.3f, 0.0f, -2.3f), glm::vec3(0.5f, 0.0f, -0.6f)
	};

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.f, 0.f, abs(sin(glfwGetTime() / 4))/5, 1.0f);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		mainShader.use();
		mainTexture.Bind(0);
		redWindow.Bind(1);
		grass.Bind(2);

		glm::vec3 lightColor(1.0f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.4f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.1f);

		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 900.0f, 0.1f, 100.f);
		mainShader.SetMat4("view", view);
		mainShader.SetMat4("projection", projection);
		mainShader.SetInt("texture0", 0);
		mainShader.SetInt("texture1", 1);
		vao.Bind();

		for (unsigned int i = 0; i < 2; i++)
		{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, CubePositions[i]);
		mainShader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		}

	
		quadShader.use();
		quadVAO.Bind();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		quadShader.SetMat4("view", view);
		quadShader.SetMat4("projection", projection);
		quadShader.SetMat4("model", model);
		quadShader.SetInt("texture0", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		quadShader.SetInt("texture0", 1);
		quadShader.SetMat4("view", view);
		quadShader.SetMat4("projection", projection);

		std::map<float, glm::vec3> sorted;

		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			float distance = glm::length(camera.Position - vegetation[i]);
			sorted[distance] = vegetation[i];
		}

		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			quadShader.SetMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}