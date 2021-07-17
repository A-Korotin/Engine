#include "Texture.h"

Texturee::Texturee(const char* filepath)
	:m_Id(0), m_Data(nullptr), m_Height(0), m_Width(0), m_Channels(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_Data = stbi_load(filepath, &m_Width, &m_Height, &m_Channels, 4);

	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (m_Data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(m_Data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
		std::cout << "ERROR::TEXTURE::LOAD::FAILED_TO_LOAD_A_TEXUTRE" << std::endl;


}

Texturee::~Texturee()
{
	glDeleteTextures(1, &m_Id);
}

void Texturee::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texturee::Unind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}