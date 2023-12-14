#include "Model.h"

CModel::CModel()
{
}

CModel::~CModel()
{
    for (auto& mesh : m_meshes) {
        delete mesh;
    }
    m_meshes.clear();
}

void CModel::Create(std::string_view name)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    if (!Load(vertices, indices, name)) {
        exit(1);
    }
    
    CMesh* mesh = new CMesh;
    mesh->Init(vertices, indices, GL_TRIANGLES);
    m_meshes.push_back(mesh);
}

bool CModel::Load(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::string_view name)
{
    std::ifstream file;
	file.open(name.data());

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    std::string line;
    bool read_v = false;
    bool read_vn = false;

    // 한 줄씩 읽기
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        
        Vertex vertex;
        unsigned int v_index_buff;
        if (prefix == "v") { // 정점 정보인 경우
            iss >> vertex.position.x >> vertex.position.y >> vertex.position.z;
            read_v = true;
        }
        else if (prefix == "vn") { // 법선 벡터인 경우
            iss >> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;
            read_vn = true;
        }
        else if (prefix == "f") { // 면 정보인 경우
            for (int i = 0; i < 3; ++i) {
                iss >> v_index_buff;
                indices.push_back(v_index_buff);
                iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');   // v만 저장
            }
        }
        if (read_v && read_vn) {
            vertices.push_back(vertex);
            read_v = false;
            read_vn = false;
        }
    }

    file.close();

    return true;
}

void CModel::Draw(const CShader* program) const
{
    for (auto& mesh : m_meshes) {
        mesh->Draw(program);
    }
}

