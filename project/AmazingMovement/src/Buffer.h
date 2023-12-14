#pragma once
#include "header.h"

// VBO, IBO
class CBuffer
{
private:
	unsigned int m_buffer{};
	unsigned int m_bufferType{};
	unsigned int m_usage{};
	unsigned int m_stride{};
	unsigned int m_count{};
public:
	CBuffer();
	CBuffer(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int stride, const unsigned int count);
	~CBuffer();
public:
	unsigned int Get() { return m_buffer; };
	unsigned int GetStride() { return m_stride; };
	unsigned int GetCount() { return m_count; };
	void Gen(unsigned int bufferType, unsigned int usage, const void* data, const unsigned int stride, const unsigned int count);
	void Bind() const;
};