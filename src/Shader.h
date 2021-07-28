#pragma once
#include "CorePCH.h"


class Shader
{
private:
	unsigned int m_Id;
	mutable std::unordered_map<std::string, int> m_Locations;

	void readFile(const char* filePath, std::string& content) const;
public:
	Shader(const char* filepath);

	Shader(const char* vertexFilepath, const char* fragmentFilepath);

	void use();
	
	int GetLocation(const char* name) const;
	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMat4(const char* name, const glm::mat4& value) const;
	void SetMat3(const char* name, const glm::mat3& value) const;
	void SetVec3(const char* name, float v0, float v1, float v2) const;
	void SetVec3(const char* name, const glm::vec3& value) const;

};