#pragma once
#include "CorePCH.h"


class API Shader
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
	void SetMat4(const char* name, const glm::mat4& value) const;
	void SetVec3(const char* name, float v0, float v1, float v2) const;
	void SetVec3(const char* name, const glm::vec3& value) const;

};