#include "CorePCH.h"

#include "Camera.h"
#include "Model.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#define WIDTH 1600
#define HEIGHT 900

static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float lastX = WIDTH / 2.0f;
static float lastY = HEIGHT / 2.0f;
static bool firstInput = true;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;



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

	window = glfwCreateWindow(WIDTH, HEIGHT, "Application", NULL, NULL);
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

	stbi_set_flip_vertically_on_load(1);


	float quadVertices[] = {
		//positions			colors
		-0.05f,  0.05f,		1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,		0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,		0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,		1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,		0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f,		0.0f, 1.0f, 1.0f
	};
	VertexArray vao;
	vao.Bind();
	VertexBuffer vbo(sizeof(quadVertices), quadVertices);
	vbo.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(vbo, layout);

	Shader shader("Application/res/shaders/instanced_rendering/vertex.glsl", "Application/res/shaders/instanced_rendering/fragment.glsl");

	glm::vec2 translations[100];
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}
	shader.use();
	for (uint32_t i = 0; i < 100; i++)
	{
		shader.SetUniform(("offsets[" + std::to_string(i) + "]").c_str(), translations[i]);
	}

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vao.Bind();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}