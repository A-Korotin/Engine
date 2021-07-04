#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	float vertices[]{
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	     -0.5f, 0.5f,  0.5f, 0.0f, 1.0f,
	     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	     -0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
	     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f

	};
#if(0)
	unsigned int indices[]{
		0, 1, 3,
		1, 2, 3
	};
#endif
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#if(0)
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader shader("res/shaders/shaders.shader");
	glClearColor(0.16f, 0.56f, 0.47f, 1.0f);
	Texture texture0("res/textures/poggers.png");
	Texture texture1("res/textures/chel.png");

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

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		shader.use();
		texture0.Bind();
		texture1.Bind(1);
		shader.SetInt("texture1", 0);
		shader.SetInt("texture2", 1);


		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 900.0f, 0.1f, 100.f);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		shader.SetFloat("alpha", abs(sin(glfwGetTime())));

#if(0)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
#endif
		glBindVertexArray(vao);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i + 1);
			model = glm::rotate(model, (float) glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}