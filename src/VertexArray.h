#pragma once
#include "CorePCH.h"
#include "VertexBuffer.h"

class API VertexBufferLayout;

class API VertexArray
{
private:
	unsigned int m_ID;

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

