#pragma once
#include "CorePCH.h"

class VertexBuffer
{
private:
	unsigned int m_ID;
public:
	VertexBuffer(unsigned int size, const void* data);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

