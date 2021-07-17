#pragma once

#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif 

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image/stb_image.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>


#define ASSERT(x) if(!(x)) __debugbreak();

#ifdef BUILD_DLL
	#define API __declspec(dllexport)
#else 
	#define API __declspec(dllimport)
#endif
