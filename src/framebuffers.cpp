#include "CorePCH.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "BasicShapes.h"
#include "Model.h"
#include "vendor/ogre/Assimp.h"
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


unsigned int loadCubeMap(std::vector<std::string> faces)
{
	stbi_set_flip_vertically_on_load(0);
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,	GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,	GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,	GL_CLAMP_TO_EDGE);
	return textureID;
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	VertexArray cubemapVao;
	cubemapVao.Bind();

	VertexBuffer cubemapVbo(sizeof(CubeVertices), CubeVertices);
	cubemapVbo.Bind();

	VertexBufferLayout cubemapLayout;
	cubemapLayout.Push<float>(3);
	cubemapLayout.Push<float>(3);
	cubemapLayout.Push<float>(2);

	cubemapVao.AddBuffer(cubemapVbo, cubemapLayout);

	VertexArray quadVAO;
	quadVAO.Bind();

	VertexBuffer quadVBO(sizeof(quadVertecies), quadVertecies);
	quadVBO.Bind();

	VertexBufferLayout quadLayout;
	quadLayout.Push<float>(3);
	quadLayout.Push<float>(2);

	quadVAO.AddBuffer(quadVBO, quadLayout);



	Shader bpShader("res/shaders/test_vertex.glsl", "res/shaders/test_fragment.glsl");
	Shader cubemapShader("res/shaders/cubemap/cubemap_vertex.glsl", "res/shaders/cubemap/cubemap_fragment.glsl");
	Shader quadShader("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");

	tex::Texture mainTexture("res/textures/gray_texture.jpg");

	std::vector<std::string> faces
	{
		"res/textures/skybox/right.jpg",
		"res/textures/skybox/left.jpg",
		"res/textures/skybox/top.jpg",
		"res/textures/skybox/bottom.jpg",
		"res/textures/skybox/front.jpg",
		"res/textures/skybox/back.jpg",
	};

	unsigned int cubemapTexture = loadCubeMap(faces);

	Model bp("res/models/backpack/backpack.obj");
	glm::vec3 lightPos(-5.0f, 5.0f, -2.0f);


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 900.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		glDepthFunc(GL_LESS);

		bpShader.use();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

		bpShader.SetUniform("model", model);
		bpShader.SetUniform("view", view);
		bpShader.SetUniform("projection", projection);
		bpShader.SetUniform("lightPos", lightPos);
		bpShader.SetUniform("viewPos", camera.Position);
		bpShader.SetUniform("normalMatrix", normalMatrix);
		bp.Draw(bpShader);


		quadShader.use();
		quadVAO.Bind();
		mainTexture.Bind(32);
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -1.6f, 0.0f));
			model = glm::scale(model, glm::vec3(20.0f));
			quadShader.SetInt("texture0", 32);
			quadShader.SetMat4("model", model);
			quadShader.SetMat4("view", view);
			quadShader.SetMat4("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		
		glDepthFunc(GL_LEQUAL);
		cubemapVao.Bind();
		glm::mat4 cubemapView = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		cubemapShader.use();
		cubemapShader.SetUniform("view", cubemapView);
		cubemapShader.SetUniform("projection", projection);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}