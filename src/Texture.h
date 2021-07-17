#pragma once
#include "CorePCH.h"


class Texturee
{
private:
	unsigned int m_Id;
	int m_Width, m_Height, m_Channels;
	unsigned char* m_Data;
public:
	Texturee(const char* filepath);
	~Texturee();
	void Bind(unsigned int slot = 0) const;
	void Unind() const;
};

