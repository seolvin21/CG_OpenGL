#include "VAO.h"

CVAO::CVAO()
{
}

CVAO::~CVAO()
{
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}
}

void CVAO::Gen()
{
	if (!m_vao)
	{
		glGenVertexArrays(1, &m_vao); //vao »ý¼º
	}
	// bind
	Bind();
}

void CVAO::SetAttrib(unsigned int attribIndex, int count, unsigned int type, bool normalized, size_t stride, unsigned int offset) const
{
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, count, type, normalized, stride, (const void*)offset);
}

void CVAO::Bind() const
{
	glBindVertexArray(m_vao);
}
