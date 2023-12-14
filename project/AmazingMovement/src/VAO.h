#pragma once
#include "header.h"

class CVAO
{
private:
	unsigned int m_vao{};
public:
	// ���� �ÿ� VAO ���� �� ���ε�
	CVAO();
	// �迭 ����
	~CVAO();
public:
	void Gen();
	void SetAttrib(unsigned int attribIndex, int count, unsigned int type, bool normalized, size_t stride, unsigned int offset) const;
	void Bind() const;
};

