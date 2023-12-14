#pragma once
#include "header.h"

class CVAO
{
private:
	unsigned int m_vao{};
public:
	// 생성 시에 VAO 생성 및 바인딩
	CVAO();
	// 배열 삭제
	~CVAO();
public:
	void Gen();
	void SetAttrib(unsigned int attribIndex, int count, unsigned int type, bool normalized, size_t stride, unsigned int offset) const;
	void Bind() const;
};

