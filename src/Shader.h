#pragma once
#include "CorePCH.h"


class Shader
{
private:
	mutable std::unordered_map<std::string, int> m_Locations;

	void readFile(const char* filePath, std::string& content) const;
public:
	unsigned int m_Id;
	Shader(const char* filepath);

	Shader(const char* vertexFilepath, const char* fragmentFilepath, const char* geometryFilepath = nullptr);

	Shader() = delete;

	void use();
	
	int GetLocation(const char* name) const;



	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMat4(const char* name, const glm::mat4& value) const;
	void SetMat3(const char* name, const glm::mat3& value) const;
	void SetVec3(const char* name, float v0, float v1, float v2) const;
	void SetVec3(const char* name, const glm::vec3& value) const;

	void SetUniform(const char* name, const int value) const
	{
		glUniform1i(GetLocation(name), value);
	}
	void SetUniform(const char* name, const float value) const
	{
		glUniform1f(GetLocation(name), value);
	}
	void SetUniform(const char* name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void SetUniform(const char* name, const glm::vec3& value) const
	{
		glUniform3f(GetLocation(name), value.x, value.y, value.z);
	}
	void SetUniform(const char* name, const glm::mat3& value) const
	{
		glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void SetUniform(const char* name, const float v0, const float v1, const float v2) const
	{
		glUniform3f(GetLocation(name), v0, v1, v2);
	}
	void SetUniform(const char* name, const glm::vec2& value) const
	{
		glUniform2f(GetLocation(name), value.x, value.y);
	}
};
