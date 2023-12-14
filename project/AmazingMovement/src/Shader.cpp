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
	glDisableVertexAttribArray(glGetAttribLocation(m_program, name.data())); // Disable �ʼ�!
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
	MakeVertexShaders(); //--- ���ؽ� ���̴� �����
	MakeFragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(m_program);
}

void CShader::MakeVertexShaders()
{
	vertexSource = Filetobuf(vertex_file.data());
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void CShader::MakeFragmentShaders()
{
	fragmentSource = Filetobuf(frag_file.data());
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
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