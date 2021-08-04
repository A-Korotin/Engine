#include "CorePCH.h"

#include "Camera.h"
#include "Model.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "BasicShapes.h"

#define WIDTH 1600
#define HEIGHT 900

static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float lastX = WIDTH / 2.0f;
static float lastY = HEIGHT / 2.0f;
static bool firstInput = true;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

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
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return textureID;
}


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
	glfwWindowHint(GLFW_SAMPLES, 16);

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
	glEnable(GL_MULTISAMPLE);
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


	Shader planetShader("Application/res/shaders/asteroid_field/planet_vertex.glsl",
						"Application/res/shaders/asteroid_field/planet_fragment.glsl");

	Shader rockShader("Application/res/shaders/asteroid_field/rock_vertex.glsl",
					  "Application/res/shaders/asteroid_field/rock_fragment.glsl");

	unsigned int amount = 10000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); 
	float radius = 150.0;
	float offset = 25.0f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		modelMatrices[i] = model;
	}

	Model planet("Application/res/models/planet/planet.obj");
	Model rock("Application/res/models/rock/rock.obj");

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < rock.meshes.size(); i++)
	{
		unsigned int VAO = rock.meshes[i].VAO;
		glBindVertexArray(VAO);

		std::size_t v4s = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(1 * v4s));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(2 * v4s));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(3 * v4s));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glBindVertexArray(0);
	}

	std::vector<std::string> faces
	{

		"Application/res/textures/space/right.jpg",
		"Application/res/textures/space/left.jpg",
		"Application/res/textures/space/top.jpg",
		"Application/res/textures/space/down.jpg",
		"Application/res/textures/space/front.jpg",
		"Application/res/textures/space/back.jpg",
	};

	std::vector<std::string> faces1
	{
		"Application/res/textures/space/Nebula aklion/skybox_px.jpg",
		"Application/res/textures/space/Nebula aklion/skybox_nx.jpg",
		"Application/res/textures/space/Nebula aklion/skybox_py.jpg",
		"Application/res/textures/space/Nebula aklion/skybox_ny.jpg",
		"Application/res/textures/space/Nebula aklion/skybox_pz.jpg",
		"Application/res/textures/space/Nebula aklion/skybox_nz.jpg"
	};

	VertexArray cubemapVao;
	cubemapVao.Bind();

	VertexBuffer cubemapVbo(sizeof(CubeVertices), CubeVertices);
	cubemapVbo.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	cubemapVao.AddBuffer(cubemapVbo, layout);
	Shader cubemapShader("Application/res/shaders/cubemap/cubemap_vertex.glsl", "Application/res/shaders/cubemap/cubemap_fragment.glsl");
	unsigned int cubemap = loadCubeMap(faces1);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 900.0f, 0.1f, 800.0f);
		glDepthFunc(GL_LESS);
		planetShader.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		planetShader.SetUniform("model", model);
		planetShader.SetUniform("view", view);
		planetShader.SetUniform("projection", projection);
		planet.Draw(planetShader);
		rockShader.use();
		rockShader.SetUniform("view", view);
		rockShader.SetUniform("projection", projection);
		for (unsigned int i = 0; i < rock.meshes.size(); i++)
		{
			glBindVertexArray(rock.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		}
		glDepthFunc(GL_LEQUAL);
		cubemapVao.Bind();
		glm::mat4 cubemapView = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		cubemapShader.use();
		cubemapShader.SetUniform("view", cubemapView);
		cubemapShader.SetUniform("projection", projection);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}