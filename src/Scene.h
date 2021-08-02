#pragma once
#include "CorePCH.h"
#include "Camera.h"

class Scene
{
public:

	virtual void OnAttach() = 0;

	virtual void OnRender(GLFWwindow* window) = 0;

	virtual void ProcessKeyboard(GLFWwindow* window) = 0;

	virtual void ProcessMouse(GLFWwindow* window, double xPos, double yPos) = 0;

	virtual void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset) = 0;

	virtual void FramebufferSizeCallback(GLFWwindow* window, int width, int height) = 0;

};

