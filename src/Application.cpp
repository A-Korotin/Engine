#include "ModelLoadScene.h"

static ModelLoadingScene scene;

void fbsc(GLFWwindow* window, int width, int height)
{
	scene.FramebufferSizeCallback(window, width, height);
}

void mouse(GLFWwindow* window, double xPos, double yPos)
{
	scene.ProcessMouse(window, xPos, yPos);
}

void scroll(GLFWwindow* window, double xoffset, double yoffset)
{
	scene.ProcessScroll(window, xoffset, yoffset);
}


int main(int argc, char argv[])
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1600, 900, "Application", NULL, NULL);
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

	stbi_set_flip_vertically_on_load(true);


	scene.OnAttach();
	glfwSetFramebufferSizeCallback(window, fbsc);
	glfwSetCursorPosCallback(window, mouse);
	glfwSetScrollCallback(window, scroll);

	while (!glfwWindowShouldClose(window))
	{
		scene.OnRender(window);
	}
	return 0;
}