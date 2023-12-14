#pragma once
#include "header.h"
#include "header_user.h"

class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
};

class CMesh
{
private:
	unsigned int m_primitive_type;
	CVAO* m_vao{};
	CBuffer* m_vertexbuffer{};
	CBuffer* m_indexbuffer{};
public:
	CMesh();
	CMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int primitive_type);
	~CMesh();
public:
	void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int primitive_type);
	void Draw(const CShader* program) const;
	void CreateBox();
	void CreateSquarePy();
};

