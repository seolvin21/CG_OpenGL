#include "Buffer.h"

CBuffer::CBuffer()
{
}


CBuffer::CBuffer(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int stride, const unsigned int count) : m_bufferType{ bufferType }, m_usage{ usage }, m_stride{stride}, m_count{count}
{
	if (!m_buffer)
	{
		glGenBuffers(1, &m_buffer); //1. ���� ����
	}
	CBuffer::Bind();
	glBufferData(bufferType, stride * count, data, usage);  //3. �۾� ���� ���ۿ� ������ ����
}

CBuffer::~CBuffer()
{
	if (m_buffer) {
		glDeleteVertexArrays(1, &this->m_buffer);
	}
}


void CBuffer::Gen(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int stride, const unsigned int count)
{
	if (!m_bufferType || !m_usage) {
		m_bufferType = bufferType;
		m_usage = usage;
	}
	m_stride = stride;
	m_count = count;

	if (!m_buffer)
	{
		glGenBuffers(1, &m_buffer); //1. ���� ����
	}
	CBuffer::Bind();
	glBufferData(bufferType, stride * count, data, usage);  //3. �۾� ���� ���ۿ� ������ ����
}



void CBuffer::Bind() const
{
	glBindBuffer(m_bufferType, m_buffer);
}