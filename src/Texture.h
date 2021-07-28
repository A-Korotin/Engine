#pragma once
#include "CorePCH.h"

namespace tex
{
	class Texture
	{
	private:
		unsigned int m_Id;
		int m_Width, m_Height, m_Channels;
		unsigned char* m_Data;
	public:
		Texture(const char* filepath);
		~Texture();
		void Bind(unsigned int slot = 0) const;
		void Unind() const;
	};

}