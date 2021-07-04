#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
private:
	unsigned int m_Id;
	mutable std::unordered_map<std::string, int> m_Locations;
public:
	Shader(const char* filepath);

	void use();
	
	int GetLocation(const char* name) const;
	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMat4(const char* name, glm::mat4 value) const;
};