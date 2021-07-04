#include "Shader.h"

enum class ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

Shader::Shader(const char* filepath)
{
	std::string vertex;
	std::string fragment;
	std::ifstream input;
	std::string line;
	ShaderType type = ShaderType::NONE;
	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		input.open(filepath);
		while (!input.eof())
		{
			std::getline(input, line);
			if (line.find("#vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("#fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
			else
			{
				switch (type)
				{
				case ShaderType::VERTEX:
					vertex += line + '\n';
					break;
				case ShaderType::FRAGMENT:
					fragment += line + '\n';
					break;

				}
			}
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << e.what() << std::endl;
	}

	const char* vSource = vertex.c_str();
	const char* fSource = fragment.c_str();

	unsigned int vert, frag;
	int success;
	char infoLog[512];
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vSource, nullptr);
	glCompileShader(vert);

	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vert, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fSource, nullptr);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_Id = glCreateProgram();
	glAttachShader(m_Id, vert);
	glAttachShader(m_Id, frag);
	glLinkProgram(m_Id);
	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_Id, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::use()
{
	glUseProgram(m_Id);
}

int Shader::GetLocation(const char* name) const
{
	if (m_Locations.find(name) == m_Locations.end())
		m_Locations[name] = glGetUniformLocation(m_Id, name);
	return m_Locations[name];
}

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(GetLocation(name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(GetLocation(name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(GetLocation(name), value);
}

void Shader::SetMat4(const char* name, glm::mat4 value) const
{
	glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}