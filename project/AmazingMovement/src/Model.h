#pragma once
#include "header.h"
#include "header_user.h"

// 텍스트 파일에 있는 버텍스를 읽는
class CModel
{
private:
	std::vector<CMesh*> m_meshes;
public:
	CModel();
	~CModel();
public:
	void Create(std::string_view name);
	bool Load(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::string_view name);	// 파일 로드 함수
	int GetMeshCount() const { return static_cast<int>(m_meshes.size()); };
	CMesh GetMesh(int index) const { return *m_meshes[index]; };
	void Draw(const CShader* program) const;
};