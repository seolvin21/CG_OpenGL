#pragma once
#include "header.h"

class CShader
{
private:
	// ���� �̸�
	std::string vertex_file;
	std::string frag_file;

	GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
	GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
	GLuint m_program; //--- ���̴� ���α׷�
public:
	CShader();
	CShader(std::string vertex, std::string frag);
	~CShader();
public:
	unsigned int GetID() const;
	// layout enable!
	void EnableLocation(const std::string_view name) const;
	void DisableLocation(const std::string_view name) const;
	void SetUniform(const std::string_view name, int value) const;
	void SetUniform(const std::string_view name, float value) const;
	void SetUniform(const std::string_view name, const glm::vec2& value) const;
	void SetUniform(const std::string_view name, const glm::vec3& value) const;
	void SetUniform(const std::string_view name, const glm::vec4& value) const;
	void SetUniform(const std::string_view name, const glm::mat4& value) const;
	void UseShader() const;
	void MakeShaderProgram();
	void MakeVertexShaders();
	void MakeFragmentShaders();
	char* Filetobuf(const char* file);
};

