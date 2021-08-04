#include "CorePCH.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


void fbsc(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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
	glfwSetFramebufferSizeCallback(window, fbsc);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	float points[] = {
		//position		// color
		-0.5f,  0.5f,	1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,	0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,	0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,	1.0f, 1.0f, 0.0f
	};

	VertexArray vao;
	vao.Bind();
	VertexBuffer vbo(sizeof(points), points);
	vbo.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(vbo, layout);

	Shader shader("Application/res/shaders/Geometry_shader_test/vertex.glsl",
				  "Application/res/shaders/Geometry_shader_test/fragment.glsl",
				  "Application/res/shaders/Geometry_shader_test/geometry.glsl");


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		vao.Bind();
		shader.use();
		glDrawArrays(GL_POINTS, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}