#include "Shader.h"

CShader::CShader() : m_program{}
{

}

CShader::CShader(std::string vertex, std::string frag) : vertex_file{vertex}, frag_file{ frag }, m_program{}
{

}

CShader::~CShader()
{
	if (m_program) {
		glDeleteProgram(m_program);
	}
}

GLuint CShader::GetID() const
{
	return m_program;
}

void CShader::EnableLocation(const std::string_view name) const
{
	glEnableVertexAttribArray(glGetAttribLocation(m_program, name.data()));
}

void CShader::DisableLocation(const std::string_view name) const
{
	glDisableVertexAttribArray(glGetAttribLocation(m_program, name.data())); // Disable 필수!
}

void CShader::SetUniform(const std::string_view name, int value) const
{
	auto loc = glGetUniformLocation(m_program, name.data());
	glUniform1i(loc, value);
}

void CShader::SetUniform(const std::string_view name, float value) const
{
	auto loc = glGetUniformLocation(m_program, name.data());
	glUniform1f(loc, value);
}

void CShader::SetUniform(const std::string_view name, const glm::vec2& value) const
{
	auto loc = glGetUniformLocation(m_program, name.data());
	glUniform2fv(loc, 1, glm::value_ptr(value));
}

void CShader::SetUniform(const std::string_view name, const glm::vec3& value) const
{
	auto loc = glGetUniformLocation(m_program, name.data());
	glUniform3fv(loc, 1, glm::value_ptr(value));
}

void CShader::SetUniform(const std::string_view name, const glm::vec4& value) const
{
	auto loc = glGetUniformLocation(m_program, name.data());
	glUniform4fv(loc, 1, glm::value_ptr(value));
}

void CShader::SetUniform(const std::string_view name, const glm::mat4& value) const
{
	auto loc = glGetUniformLocation(m_program, name.data());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void CShader::UseShader() const
{
	glUseProgram(this->m_program);
}

void CShader::MakeShaderProgram()
{
	MakeVertexShaders(); //--- 버텍스 세이더 만들기
	MakeFragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(m_program);
}

void CShader::MakeVertexShaders()
{
	vertexSource = Filetobuf(vertex_file.data());
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void CShader::MakeFragmentShaders()
{
	fragmentSource = Filetobuf(frag_file.data());
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

char* CShader::Filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}