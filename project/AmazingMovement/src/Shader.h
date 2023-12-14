#pragma once
#include "header.h"

class CShader
{
private:
	// 파일 이름
	std::string vertex_file;
	std::string frag_file;

	GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
	GLuint vertexShader, fragmentShader; //--- 세이더 객체
	GLuint m_program; //--- 셰이더 프로그램
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

