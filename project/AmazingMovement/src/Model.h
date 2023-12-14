#pragma once
#include "header.h"
#include "header_user.h"

// �ؽ�Ʈ ���Ͽ� �ִ� ���ؽ��� �д�
class CModel
{
private:
	std::vector<CMesh*> m_meshes;
public:
	CModel();
	~CModel();
public:
	void Create(std::string_view name);
	bool Load(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::string_view name);	// ���� �ε� �Լ�
	int GetMeshCount() const { return static_cast<int>(m_meshes.size()); };
	CMesh GetMesh(int index) const { return *m_meshes[index]; };
	void Draw(const CShader* program) const;
};